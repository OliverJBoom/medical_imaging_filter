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


	/*array<array<int, 3>, 3> kernel = { {
						 {0.5, 0.5, 0.5},
						 {0.5, 0.5, 0.5},
						 {0.5, 0.5, 0.5}} };*/

	/*double  kernel[3][3] =  {
					 {1.0/9.0, 1.0/9.0, 1.0/9.0},
					 {1.0/9.0, 1.0/9.0, 1.0/9.0},
					 {1.0/9.0, 1.0/9.0, 1.0/9.0}} ;*/

	double  kernel[3][3] = {
				 {0, 71, 0},
				 {1, -9, 1},
				 {0, 1, 67} };




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
	/*cimg_forXY(grey, x, y) {
		int val = (int)grey(x, y);
		int accum = 0;
		int x1 = 0;
		for (int im_row = 1 + x1; im_row < 2 + x1; im_row++) {
			cout << "imro2" << im_row;
			for (int im_col = 0 + y; im_col < 2 + y; im_col++) {


				for (int ke_row = 0; ke_row < 3; ke_row++) {
					for (int ke_col = 0; ke_col < 3; ke_col++) {
						if (im_row - x == ke_row) {
							if (im_col - y == ke_col) {

								accum = accum + val * kernel[ke_row][ke_col];
							}
						}
					}
				}
			}
			filtered21(x, y) = accum;

		}
		}


	
	*/

	cimg_forXY(grey, x, y) {
		if (x != 0 && x != grey.width()-1 && y != 0 && y != grey.height()-1) {
			//cout << "x" << x;
			//cout << "x: " << x << endl;
			//cout << "x+1: " << x + 1 << endl;
			//cout << "x-1: " << x - 1 << endl;
			//system("pause");

			int upp_x = x + 1;
			int low_x = x - 1;

			int upp_y = y + 1;
			int low_y = y - 1;

			//cout << "upp: " << upp << endl;
			//cout << "low: " << low << endl;
			//system("pause");
			int val = (int)grey(x, y);

			double accum = 0;
			//cout << "(x,y): " << "(" << x << "," << y << ")" << endl;
			for (int i = low_x; i < upp_x+1; i++) {
				for (int j = low_y; j < upp_y + 1; j++) {
					//cout << "(xi, yi)" << "(" << i - low_x << "," << j - low_y << ")" << endl;
					accum = accum + val * kernel[i - low_x][j - low_y];
					//cout << "(xi, yi) = " << "(" << i << "," << j - low_y << "), val = " << val << endl;

					//cout << kernel[i - low_x][j - low_y] << endl;
				}
			}
			filtered21(x-1, y-1) = accum;
			//system("pause");



			//for (int xi = x +1; xi < x + 3; ++x) {
			//	cout << "xi:    " << xi;
			//	system("pause");
		//	}
			//system("pause");

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