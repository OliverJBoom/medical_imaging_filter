#include <iostream>
#include <string>
#include <vector>

#include "Filter.h"
#include "CImg.h"

using namespace cimg_library;


//Greyscales the image
CImg<unsigned char> Filter::greyscale(CImg<unsigned char> src) {

	CImg<unsigned char> grey(src.width(), src.height(), src.depth(), 1);

	//This function loops over the images dimensions
	cimg_forXY(src, x, y) {
		// Recipe for grayscale weighting from RGB : 0.2989, 0.5870, 0.1140
		int val = 0.2989 * (int)src(x, y, 0) + 0.5870 * (int)src(x, y, 1) + 0.1140 * (int)src(x, y, 2);
		grey(x, y, 0, 0) = val;
	}
	return grey;
}



//Returns the red spectrum of a image
CImg<unsigned char> Filter::getRed(CImg<unsigned char> src) {

	CImg<unsigned char> Red(src.width(), src.height(), src.depth(), 3);
	Red.CMYtoRGB();

	cimg_forXY(src, x, y) {
		Red(x, y, 0) = (int)src(x, y, 0, 0);
	};
	return Red;
}



//Returns the green spectrum of a image
CImg<unsigned char> Filter::getGreen(CImg<unsigned char> src) {

	CImg<unsigned char> Green(src.width(), src.height(), src.depth(), 3);
	Green.CMYtoRGB();

	cimg_forXY(src, x, y) {
		Green(x, y, 1) = (int)src(x, y, 0, 1);
	};
	return Green;
}



//Returns the blue spectrum of a image
CImg<unsigned char> Filter::getBlue(CImg<unsigned char> src) {

	CImg<unsigned char> Blue(src.width(), src.height(), src.depth(), 3);
	Blue.CMYtoRGB();

	cimg_forXY(src, x, y) {
		Blue(x, y, 2) = (int)src(x, y, 0, 2);
	};
	return Blue;
}



//Swap RGB colours
CImg<unsigned char> Filter::colour_swap(CImg<unsigned char> src) {

	CImg<unsigned char> col(width, height, depth, 3);

	cimg_forXYC(src, x, y, c) {  
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



//Stores the image dimensions
void Filter::set_dim(int im_width, int im_height, int im_depth) {
	width = im_width;
	height = im_height;
	depth = im_depth;
}



// Brightens the image by an input value. 
CImg<unsigned char> Filter::brighten(CImg<unsigned char> src, int level) {
	int channels = src.spectrum();

	CImg<unsigned char> bright(width, height, depth, channels);

	cimg_forXYC(src, x, y, c) {
		// Recipe for grayscale weighting from RGB : 0.2989, 0.5870, 0.1140
		int val = (int)src(x, y, c);

		if (val < 255 - level) {
			bright(x, y, 0, c) = val + level;
		}
		else {
			bright(x, y, 0, c) = 255;
		}
	}
	return bright;
}



//Allows values under a certain value to pass. 
CImg<unsigned char> Filter::low_pass(CImg<unsigned char> src, int level) {
	int channels = src.spectrum();

	CImg<unsigned char> pass(width, height, depth, channels);

	cimg_forXYC(src, x, y, c) {
		int val = (int)src(x, y, c);

		if (val < level) {
			pass(x, y, 0, c) = val;
		}
		//If the value is not below the input level it is set to the level
		else {
			pass(x, y, 0, c) = level;
		}
	}
	return pass;
}


//Allows values over a certain value to pass. 
CImg<unsigned char> Filter::high_pass(CImg<unsigned char> src, int level) {
	int channels = src.spectrum();

	CImg<unsigned char> pass(width, height, depth, channels);

	cimg_forXYC(src, x, y, c) {
		int val = (int)src(x, y, c);

		if (val > level) {
			pass(x, y, 0, c) = val;
		}
		//If the value is not above the input level it is set to the level
		else {
			pass(x, y, 0, c) = level;
		}
	}
	return pass;
}


//Allows values with a certain band to pass
CImg<unsigned char> Filter::band_pass(CImg<unsigned char> src, int low_lim, int up_lim) {
	int channels = src.spectrum();

	CImg<unsigned char> pass(width, height, depth, channels);

	cimg_forXYC(src, x, y, c) {
		int val = (int)src(x, y, c);

		if ((val > low_lim) && (val < up_lim)) {
			pass(x, y, 0, c) = val;
		}
		//If the value is not within the range it is set to the lower limit
		else {
			pass(x, y, 0, c) = low_lim;
		}
	}
	return pass;
}
