#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"
#include "Convolution.h"
#include "Filter.h"

#include "CImg.h"

using namespace cimg_library;
using namespace std;


int main() {
	//cimg::imagemagick_path("C://Program Files//ImageMagick-7.0.8-Q16//convert.exe");
	class Filter Fil;

	CImg<unsigned char> src("Images//chestb.bmp");

	Fil.set_dim(src.width(), src.height(), src.depth());

	class Kernel Example;
	char effect = 'P'; // To look for the effect that each char represents look at Kernel::place
	Example.vector_select(effect);
	Example.place();
	Example.print();
	Example.set_dim(Fil.width, Fil.height, Fil.depth);

	CImg<unsigned char> col = Fil.colour_swap(src);
	CImg<unsigned char> grey = Fil.greyscale(src);
	CImg<unsigned char> bri = Fil.brighten(grey, 60);
	CImg<unsigned char> high_pass = Fil.low_pass(grey, 90);
	CImg<unsigned char> low_pass = Fil.high_pass(grey, 60);
	CImg<unsigned char> conv_out = Example.conv(grey);

	//col.display();
	//high_pass.display();
	//low_pass.display();
	//grey.display();
	//bri.display();
	conv_out.display();
	
	system("pause");
	return 0;
}