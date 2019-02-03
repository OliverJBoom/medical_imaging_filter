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
	//src.display();

	cimg_forXYC(src, x, y, c) {  // Does 3 nested loops
		// c = 0, 1, 2 for R G B respectively
		int val = (int)src(x, y, 0, c);
		cout << "(" << x << "," << y << "," << c << ") = "
		 << val << endl;
	}

	// pokemon.bmp		parrot_mask.pgm
	

	system("pause");
	return 0;
}