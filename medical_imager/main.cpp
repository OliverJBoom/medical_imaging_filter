#include <iostream>
#include <string>
#include <array>
#include "utils.h"
#include "CImg.h"
#include "medcon.h"

using namespace cimg_library;
using namespace std;


int main() {
	//hello_world();
	//cimg::imagemagick_path("C:\\Program Files\\ImageMagick-7.0.8-Q16\\magick.exe");

	CImg<unsigned char> src("mountain.bmp");
	//CImg<unsigned char> src;
	
	//src.get_load_medcon_external("000004.dcm");

	//src.display();
	int height = src.height();
	int width = src.width();
	int depth = src.depth();

	CImg<unsigned char> out(width, height, depth, 3);
	CImg<unsigned char> grey(width, height, depth, 1);
	CImg<unsigned char> grey_bright(width, height, depth, 1);
	CImg<unsigned char> filtered21(width - 4, height - 4, depth, 1);


	//CImg<unsigned char> load_medcon_external("DICOM/000004.dcm");
	array<array<double, 5>, 5> kernel6 = { {
				 {5, 10, 20, 10, 5},
				 {10, 100, 200, 200, 10},
				 {20, 200, -1500, 200, 20},
				 {10, 100, 200, 100, 10},
				 {5, 10, 20, 10, 5}} };

	// custom sharpening 1
	array<array<double, 5>, 5> kernel5 = { {
					 {1, 4, 6, 4, 1},
					 {4, 26, 54, 26, 4},
					 {6, 54, -876, 54, 6},
					 {4, 26, 54, 26, 4},
					 {1, 4, 6, 4, 1}} };

	array<array<double, 5>, 5> kernel = { {
						 {1, 4, 6, 4, 1},
						 {4, 16, 24, 16, 4},
						 {6, 24, 36, 24, 6},
						 {4, 16, 24, 16, 4},
						 {1, 4, 6, 4, 1}} };

	array<array<double, 3>, 3> kernel2 = { {
					 {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},  
					 {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
					 {1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0} } };

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

		switch (c) {
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

		if (val < 255 - bright) {
			grey_bright(x, y) = val + bright;
		}
		else {
			grey_bright(x, y) = 255;
		}
	}


	// convolution using kernel array

	cimg_forXY(grey, x, y) {
		int dim_kernel = 5;
		int padding = (dim_kernel  -1 )/ 2;

		
		if ((x >= padding) && (x < grey.width() - padding) && (y >= padding) && (y < grey.height() - padding)) {
			int upp_x = x + padding;
			int low_x = x - padding;


			int upp_y = y + padding;
			int low_y = y - padding;

			int val = (int)grey(x, y);

			double accum = 0;
			int count = 0;

			for (int i = low_x; i < upp_x + 1; i++) {
				for (int j = low_y; j < upp_y + 1; j++) {
					count += 1;
					accum = accum + (int)grey(i,j) * kernel[i - low_x][j - low_y];
				}
			}

			filtered21(x - padding, y - padding) = accum/256;



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

