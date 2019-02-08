# -*- coding: utf-8 -*-
"""
Created on Sun Jan 27 21:00:12 2019

@author: Hamed
"""
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

im = Image.open("chestb.bmp")
#p = np.array(im)[:,:,0]


man = np.array((
        (1,0,1,3,1,4),
        (2,4,1,4,1,9),
        (2,4,5,6,1,9),
        (5,3,8,8,4,1),
        (1,4,9,5,2,9),
        (1,5,9,1,4,1)))

#kernel = np.array((
#				 (0, 1, 0),
#				 (1, 1, 1),
#				 (0, 1, 0)))

kernel = np.array((
				 (0, 0, 0, 0, 0),
				 (0, 0, 0, 0, 0),
				 (0, 0, 1, 0, 0),
              (0, 0, 0, 0, 0),
              (0, 0, 0, 0, 0)))

#plt.imshow(p)


def conv(p):
    dim_kernel = 5
    padding = dim_kernel -2
    print(padding)
    out = np.empty((np.shape(p)[0]-2,np.shape(p)[1]-2))

    for x in range((np.shape(p)[1])):
        for y in range((np.shape(p)[0])):
            
            if (padding<= x <np.shape(p)[1] - padding) and (padding<= y <np.shape(p)[1] - padding):
#            if ((x!= 0) and (x!= np.shape(p)[1]-1) and (y!=0) and (y!= np.shape(p)[0]-1)):
                print("x", x)
                upp_x = x +1
                low_x = x -1
                
                upp_y = y+1
                low_y = y-1

#                print("x,y", x,y, "->", val)
                #                print("p", p[y,x])
                accum = 0
#                print("x,y", x,y)
                
#                ROI = np.empty((3,3))

                for i in range(low_x, upp_x+1, 1):
                    for j in range(low_y, upp_y+1, 1):
#                        ROI[i-low_x,j-low_y] = pval
#                        print("i,j", i,j)
#                        print("mult", p[i][j],kernel[i - low_x][j - low_y] )
                        accum = accum + p[j][i] * kernel[i - low_x][j - low_y]
                        
#                print("ROI", ROI)
                out[y-1, x-1] = accum
                
        
    fig = plt.figure()
    ax1 = fig.add_subplot(121)
    ax1.set_title("original")
    ax1.imshow(p)

    ax2 = fig.add_subplot(122)
    ax2.set_title("convolved")
    ax2.imshow(out)
    return out
o = conv(man)

from pprint import pprint

pprint(o)