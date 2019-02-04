#include <iostream>
#include <string>
#include <array>
#include "utils.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;


int main() {
	//hello_world();
	//cimg::imagemagick_path("C:\\Program Files\\ImageMagick-7.0.8-Q16\\magick.exe");

	CImg<unsigned char> src("chestb.bmp");
	//src.display();
	int height = src.height();
	int width = src.width();
	int depth = src.depth();

	CImg<unsigned char> out(width, height, depth, 3);
	CImg<unsigned char> grey(width, height, depth, 1);
	CImg<unsigned char> grey_bright(width, height, depth, 1);
	CImg<unsigned char> filtered21(width-2, height-2, depth, 1);


	array<array<int, 3>, 3> kernel = { {
						 {0, -1, 0},
						 {-1, 10, -1},
						 {0, -1, 0}} };

	/*double  kernel[3][3] =  {
					 {1.0/9.0, 1.0/9.0, 1.0/9.0},
					 {1.0/9.0, 1.0/9.0, 1.0/9.0},
					 {1.0/9.0, 1.0/9.0, 1.0/9.0}} ;*/

//	double  kernel[3][3] = {
	//			 {0, 1, 0},
		//		 {1, 1, 1},
			//	 {0, 1, 67} };




	//array<array<int, 1931 -2>, 365-2> output = { {} };

	// Performs colour switch between rbg channels
	cimg_forXYC(src, x, y, c) {  // Does 3 nested loops
		// c = 0, 1, 2 for R G B respectively
		int val = (int)src(x, y, c);
		
		switch(c){
		case 0:
			out(x, y, 0, 2) = val;
			break;
		case 1: 
			out(x, y, 0, 0) = val;
			break;
		case 2:
			out(x, y, 0, 1) = val;
			break;
		}
	}


	//Greyscales the image
	cimg_forXY(src, x, y) { 
		// Recipe for grayscale weighting from RGB : 0.2989, 0.5870, 0.1140
		int val = 0.2989 * (int)src(x, y, 0) + 0.5870 * (int)src(x, y, 1) + 0.1140 * (int)src(x, y, 2);
		grey(x, y, 0, 0) = val;
	}


	// Brightens the image by quantity shown
	int bright = 100;
	cimg_forXY(grey, x, y) {
		// Recipe for grayscale weighting from RGB : 0.2989, 0.5870, 0.1140
		int val = (int)grey(x, y);
		
		if (val < 255 - bright){
		grey_bright(x, y) = val + bright;
		}
		else {
			grey_bright(x, y) = 255;
		}
	}


	// convolution using kernel array

	cimg_forXY(grey, x, y) {
		if (x != 0 && x != grey.width()-1 && y != 0 && y != grey.height()-1) {

			int upp_x = x + 1;
			int low_x = x - 1;

			int upp_y = y + 1;
			int low_y = y - 1;

			int val = (int)grey(x, y);

			double accum = 0;

			for (int i = low_x; i < upp_x+1; i++) {
				for (int j = low_y; j < upp_y + 1; j++) {
					accum = accum + (int)grey(i, j) * kernel[i - low_x][j - low_y];
				}
			}
			filtered21(x-1, y-1) = accum;


		}
	}

	
		

	
	grey.display();
	//grey_bright.display();
	grey.save("gr27.bmp");
	//out.display();
	filtered21.display();
	filtered21.save("sharp.bmp");

	return 0;
}