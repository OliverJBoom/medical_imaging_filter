/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * filename: medcon.c                                                      *
 *                                                                         *
 * UTIL C-source: Medical Image Conversion Utility                         *
 *                                                                         *
 * purpose      : main routines                                            *
 *                                                                         *
 * project      : (X)MedCon by Erik Nolf                                   *
 *                                                                         *
 * Functions    : main()             -  The hart of the project            *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* $Id$
 */

/*
   Copyright (C) 1997-2018 by Erik Nolf

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any later
   version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
   Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   59 Place - Suite 330, Boston, MA 02111-1307, USA.  */

/****************************************************************************
                              H E A D E R S
****************************************************************************/

#include <stdio.h>

#include "medcon.h"

/****************************************************************************
                                M A I N
****************************************************************************/

int main(int argc, char *argv[])
{
  FILEINFO fi;
  int   *total = mdc_arg_total;    /* total arguments of files & conversions */
  int   *convs = mdc_arg_convs;    /* counter for each conversion format     */
  char **files = mdc_arg_files;    /* array of pointers to input filenames   */
  int   f, c;                      /* some counters                          */
  int   t=0;                       /* counter for the output name prefix     */
  int   convert, error;            /* some variables                         */
  char *msg=NULL;

  XMDC_GUI = MDC_NO;               /* program is CLI, command-line interface */

  /* init library */
  MdcInit();

  if (argc == 1) { MdcPrintShortInfo(); return(MDC_BAD_CODE); }

  /* parse the command line arguments */
  if (MdcHandleArgs(&fi,argc,argv,MDC_MAX_FILES) != MDC_OK)
    MdcPrintUsage(NULL);

  /* initialize raw read input */
  if (MDC_INTERACTIVE) MdcInitRawPrevInput();

  /* stack slices or frames */
  if (MDC_FILE_STACK != MDC_NO) {
    msg = MdcStackFiles(MDC_FILE_STACK);
    if (msg != NULL) MdcPrntErr(MDC_BAD_CODE,msg);
    return(MDC_OK); /* leave program */
  }


  /* do the stuff for each input file */
  for (f=0; f<total[MDC_FILES]; f++) {

     /* open the file, initialize FILEINFO structure */
     if ((error = MdcOpenFile(&fi, files[f])) != MDC_OK) return(error);

#if MDC_INCLUDE_ACR
     /* hack file for Acr/Nema tags */
     if (MDC_HACK_ACR) {
       if ((msg = MdcHackACR(&fi)) != NULL)
         /* tolerate errors */
         MdcPrntWarn("Failed ACR Hack - %s",msg);
       if (MDC_DEBUG) MdcPrintFI(&fi);
       MdcCleanUpFI(&fi);
       continue;
     }
#endif

     /* read the file */
     if ((error = MdcReadFile(&fi,f+1,NULL)) != MDC_OK) return(error);

     /* echo alias name on one file at a time; nothing else allowed */
     if (MDC_ECHO_ALIAS) { MdcCleanUpFI(&fi); return(MDC_OK); }

     /* just print legady database info */
     if (MDC_INFO_DB) continue;

     /* apply some read options */
     msg = MdcApplyReadOptions(&fi);
     if (msg != NULL) {
       MdcCleanUpFI(&fi);
       MdcPrntErr(MDC_BAD_CODE,msg);
     }

     /* when conversions selected */
     if ( total[MDC_CONVS] > 0 ) {

       /* go through all the formats */
       for (c=1; c<MDC_MAX_FRMTS; c++) {
          convert = convs[c];
          /* write output format when selected */
          while (convert-- > 0) {
               switch (MDC_FILE_SPLIT) {
                 case MDC_SPLIT_PER_SLICE:
                     msg = MdcSplitSlices(&fi,c,MdcGetPrefixNr(&fi,t++));
                     if (msg != NULL) {
                       MdcCleanUpFI(&fi);
                       MdcPrntErr(MDC_BAD_CODE,"Failed Split - %s",msg);
                     }
                     break;
                 case MDC_SPLIT_PER_FRAME:
                     msg = MdcSplitFrames(&fi,c,MdcGetPrefixNr(&fi,t++));
                     if (msg != NULL) {
                       MdcCleanUpFI(&fi);
                       MdcPrntErr(MDC_BAD_CODE,"Failed Split - %s",msg);
                     }
                     break;
                 default:
                     error = MdcWriteFile(&fi,c,MdcGetPrefixNr(&fi,t++),NULL);
                     if (error != MDC_OK) {
                       MdcCleanUpFI(&fi);
                       return(error);
                     }
               }
          }
       }

     }

     /* clean up FILEINFO struct */
     MdcCleanUpFI(&fi);

  }

  /* finish library */
  MdcFinish();

  /* bye */
  return(MDC_OK);
}
