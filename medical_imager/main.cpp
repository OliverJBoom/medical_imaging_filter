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

	out = ui.wrapper_function(src, Fil, convolve);
	out.display();

	std::cout << "\n\nThank you for your custom!";

	system("pause");
	return 0;
}