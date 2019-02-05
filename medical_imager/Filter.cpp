#include <iostream>
#include <string>
#include <vector>


#include "Filter.h"
#include "CImg.h"


using namespace cimg_library;
using namespace std;



//Greyscales the image
CImg<unsigned char> Filter::greyscale(CImg<unsigned char> src) {

	CImg<unsigned char> grey(src.width(), src.height(), src.depth(), 1);

	cimg_forXY(src, x, y) { 
	// Recipe for grayscale weighting from RGB : 0.2989, 0.5870, 0.1140
	// Need to deal with the rounding errors
	int val = 0.2989 * (int)src(x, y, 0) + 0.5870 * (int)src(x, y, 1) + 0.1140 * (int)src(x, y, 2);
	grey(x, y, 0, 0) = val;
	}
	return grey;
}



//Greyscales the image
CImg<unsigned char> Filter::colour_swap(CImg<unsigned char> src) {

	CImg<unsigned char> col(width, height, depth, 3);

	cimg_forXYC(src, x, y, c) {  // Does 3 nested loops
		// c = 0, 1, 2 for R G B respectively
		int val = (int)src(x, y, c);

		switch (c) {
		case 0:
			col(x, y, 0, 2) = val;
			break;
		case 1:
			col(x, y, 0, 0) = val;
			break;
		case 2:
			col(x, y, 0, 1) = val;
			break;
		}
	}
	return col;
}



// Sets the image dimensions
void Filter::set_dim(int im_width, int im_height, int im_depth) {
	width = im_width;
	height = im_height;
	depth = im_depth;
}



// Brightens the image by an input value. 
CImg<unsigned char> Filter::brighten(CImg<unsigned char> src, int level) {

	CImg<unsigned char> bright(width, height, depth, 1);

	cimg_forXY(src, x, y) {
		// Recipe for grayscale weighting from RGB : 0.2989, 0.5870, 0.1140
		int val = (int)src(x, y);
	
		if (val < 255 - level){
		bright(x, y) = val + level;
		}
		else {
			bright(x, y) = 255;
		}
	}
	return bright;
}



// Brightens the image by an input value. 
CImg<unsigned char> Filter::high_pass(CImg<unsigned char> src, int level) {

	CImg<unsigned char> pass(width, height, depth, 1);

	cimg_forXY(src, x, y) {
		int val = (int)src(x, y);

		if (val < level) {
			pass(x, y) = val;
		}
		else {
			pass(x, y) = 0;
		}
	}
	return pass;
}



CImg<unsigned char> Filter::low_pass(CImg<unsigned char> src, int level) {

	CImg<unsigned char> pass(width, height, depth, 1);

	cimg_forXY(src, x, y) {
		int val = (int)src(x, y);

		if (val > level) {
			pass(x, y) = val;
		}
		else {
			pass(x, y) = 0;
		}
	}
	return pass;
}



CImg<unsigned char> Filter::band_pass(CImg<unsigned char> src, int low_lim, int up_lim) {

	CImg<unsigned char> pass(width, height, depth, 1);

	cimg_forXY(src, x, y) {
		int val = (int)src(x, y);

		if ((val > low_lim) && (val < up_lim)) {
			pass(x, y) = val;
		}
		else {
			pass(x, y) = 0;
		}
	}
	return pass;
}
