#ifndef FILTER
#define FILTER


#include <iostream>
#include <vector>


#include "CImg.h"


using namespace cimg_library;



class Filter 
{
	public:

		CImg<unsigned char> greyscale(CImg<unsigned char> src);
		CImg<unsigned char> colour_swap(CImg<unsigned char> src);
		CImg<unsigned char> brighten(CImg<unsigned char> src, int level);
		CImg<unsigned char> high_pass(CImg<unsigned char> src, int level);
		CImg<unsigned char> low_pass(CImg<unsigned char> src, int level);
		CImg<unsigned char> band_pass(CImg<unsigned char> src, int low_lim, int up_lim);
		CImg<unsigned char> getRed(CImg<unsigned char> src);
		CImg<unsigned char> getGreen(CImg<unsigned char> src);
		CImg<unsigned char> getBlue(CImg<unsigned char> src);

		void set_dim(int width, int height, int depth);

		int width;
		int height;
		int depth;
};


#endif