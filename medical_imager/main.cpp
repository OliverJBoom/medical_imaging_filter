#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"
#include "Convolution.h"
#include "Filter.h"
#include "UI.h"

#include "CImg.h"


using namespace cimg_library;



int main() {
	//cimg::imagemagick_path("C://Program Files//ImageMagick-7.0.8-Q16//convert.exe");
	class Filter Fil;
	class user ui;
	ui.welcome();
	ui.name_input();
	ui.filter_select();
	CImg<unsigned char> src_2 (ui.file_name.c_str());
	CImg<unsigned char> src = Fil.greyscale(src_2);

	Fil.set_dim(src.width(), src.height(), src.depth());
	CImg<unsigned char> out;

	class Kernel convolve;
	char effect = 'P'; // To look for the effect that each char represents look at Kernel::place
	convolve.vector_select(effect);
	convolve.place();
	convolve.set_dim(Fil.width, Fil.height, Fil.depth);

	int level;

	switch (ui.effect)
	{
	case 'a':								//Greyccale
		out = Fil.greyscale(src);
		break;
	case 'b':								//Brighten
		std::cin >> level;
		out = Fil.brighten(src, level);
		break;
	case 'c':								 //Low pass filter
		std::cin >> level;
		out = Fil.low_pass(src, level);
		break;
	case 'd':								 //High pass filter
		std::cin >> level;
		out = Fil.high_pass(src, level);
		break;
	case 'e':								 //Band pass filter
		int low_lim;
		int up_lim;
		std::cin >> low_lim;
		std::cin >> up_lim;
		out = Fil.band_pass(src, low_lim, up_lim);
		break;
	case 'f':								 //Sharpen low
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	case 'g':								 //Sharpen high
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	case 'h':								 //Gaussian Blur
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	case 'i':								 //Unsharp masking
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	case 'j':								 //Blur low
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		out.display();
		break;
	case 'k':								 //Blur high
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	case 'l':								 //Blur low
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	case 'm':								 //Edge detection
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	case 'n':								 //Psychadelic
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	default:								 //Identity
		convolve.vector_select(ui.effect);
		out = convolve.conv(src);
		break;
	}

	

	system("pause");
	return 0;
}