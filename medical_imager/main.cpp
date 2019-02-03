#include <iostream>
#include <string>

#include "utils.h"
#include "CImg.h"

using namespace cimg_library;
using namespace std;


int main() {
	//hello_world();
	//cimg::imagemagick_path("C:\\Program Files\\ImageMagick-7.0.8-Q16\\magick.exe");
	CImg<unsigned char> src("logo.bmp");
	/*
	int width = src.width();
	int height = src.height();
	unsigned char* ptr = src.data(10, 10);
	unsigned char r = ptr[0];
	unsigned char g = ptr[0 + width * height];
	unsigned char b = ptr[0 + 2 * width*height];

	//img.display();
	//unsigned char r = ptr[0];
	//unsigned char r = img(0, 0, 0, 0);
	*/
	cimg_forXYC(src, x, y, c) {  // Do 3 nested loops
		//cout << "c: " << c;
		int width = src.width();
		int height = src.height();
		//unsigned char* ptr = src.data(x, y, c);

		unsigned char r = src(x, y, 0, c);
		//unsigned char r = ptr[0];
		//unsigned char g = ptr[0 + width * height];
		//unsigned char b = ptr[0 + 2 * width*height];
		cout << r << r;
	}
	// pokemon.bmp		parrot_mask.pgm
	

	system("pause");
	return 0;
}