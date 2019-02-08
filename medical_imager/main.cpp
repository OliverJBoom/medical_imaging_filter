#include <iostream>
#include <string>
#include <vector>

#include "Convolution.h"
#include "Filter.h"
#include "UI.h"
#include "display.h"
#include "CImg.h"

using namespace cimg_library;



int main() {
	//Optional imagemagick path for those who have it installed
	//cimg::imagemagick_path("C://Program Files//ImageMagick-7.0.8-Q16//convert.exe");

	class Filter Fil;
	class User ui;

	//Welcoming the user, letting them input the file they want to filter and select the filter
	ui.welcome();
	ui.name_input();
	ui.filter_select();

	//Loading the image into a CImg instance
	CImg<unsigned char> src (ui.file_name.c_str());
	//Loading in the dimensions of the image for the filters to work with
	Fil.set_dim(src.width(), src.height(), src.depth());

	//Constructing the CImg instance for output
	CImg<unsigned char> out;

	//Conducting the filtering
	class Kernel convolve;
	out = ui.wrapper_function(src, Fil, convolve);

	//Displaying the output
	class display Grid;
	Grid.before_after(src, out);

	std::cout << "\nThank you for your custom!\n\n";
	system("pause");
	return 0;
}