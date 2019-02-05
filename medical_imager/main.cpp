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
	//hello_world();
	//cimg::imagemagick_path("C://Program Files//ImageMagick-7.0.8-Q16//convert.exe");
	class Filter Fil;

	CImg<unsigned char> src("Images//dunc.bmp");

	Fil.set_dim(src.width(), src.height(), src.depth());
	CImg<unsigned char> col = Fil.colour_swap(src);
	//col.display();

	class Kernel Example;
	char effect = 'P'; // To look for the effect that each char represents look at Kernel::place
	Example.vector_select(effect);
	Example.place();
	Example.print();


	CImg<unsigned char> grey = Fil.greyscale(src);
	//grey.display();
	CImg<unsigned char> bri = Fil.brighten(grey, 60);
	//bri.display();

	//Get a greyscale out, want to put it through convolution algorithm
	CImg<unsigned char> conv_out = Example.conv(grey, Fil.width, Fil.height, Fil.depth);//Initialising empty object
	conv_out.display();
	
	system("pause");
	return 0;
}