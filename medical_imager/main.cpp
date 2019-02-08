#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"
#include "Convolution.h"
#include "Filter.h"
#include "UI.h"
#include "display.h"


#include "CImg.h"


using namespace cimg_library;



int main() {
	cimg::imagemagick_path("C://Program Files//ImageMagick-7.0.8-Q16//magick.exe");
	class Filter Fil;
	//welcome();
	CImg<unsigned char> src("Images//ACSE.bmp");
	//src.display();

	
	Fil.set_dim(src.width(), src.height(), src.depth());

	class Kernel Example;
	char effect = 'P'; // To look for the effect that each char represents look at Kernel::place
	Example.vector_select(effect);
	Example.place();
	Example.print();
	Example.set_dim(Fil.width, Fil.height, Fil.depth);

	CImg<unsigned char> col = Fil.colour_swap(src);
	CImg<unsigned char> red = Fil.getRed(src);
	CImg<unsigned char> blue = Fil.getBlue(src);
	CImg<unsigned char> green = Fil.getGreen(src);

	CImg<unsigned char> grey = Fil.greyscale(src);
	CImg<unsigned char> bri = Fil.brighten(src, 100);
	CImg<unsigned char> high_pass = Fil.low_pass(src, 90);
	CImg<unsigned char> low_pass = Fil.high_pass(src, 60);
	CImg<unsigned char> conv_out = Example.conv(src);

	//class display Grid;
	//Grid.before_after(src,  blue);
	//Grid.warhol(src, red, green, blue);

	high_pass.display();

	system("pause");
	return 0;
}