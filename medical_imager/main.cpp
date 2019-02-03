#include <iostream>
#include <string>

#include "utils.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;


int main() {
	//hello_world();
	//cimg::imagemagick_path("C:\\Program Files\\ImageMagick-7.0.8-Q16\\magick.exe");

	CImg<unsigned char> src("pokemon.bmp");
	//src.display();
	int height = src.height();
	int width = src.width();
	int depth = src.depth();

	CImg<unsigned char> out(width, height, depth, 3);
	CImg<unsigned char> grey(width, height, depth, 1);
	CImg<unsigned char> grey_bright(width, height, depth, 1);


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

	grey.display();
	grey_bright.display();
	out.display();

	system("pause");
	return 0;
}