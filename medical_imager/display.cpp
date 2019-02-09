#include "display.h"
#include "CImg.h"



//Diplays both the filtered and unfiltered image together
void display::before_after(CImg<unsigned char> original, CImg<unsigned char> filtered)
{
	cimg_library::CImgDisplay before(original, "Before");
	cimg_library::CImgDisplay after(filtered, "After");

	while (!before.is_closed())
		before.wait();

	while (!after.is_closed())
		after.wait();
}



//Displays an artistic ensemble of the images
void display::warhol(CImg<unsigned char> original, CImg<unsigned char> red, CImg<unsigned char> green, CImg<unsigned char> blue)
{
	CImg<unsigned char> row_1, row_2, grid;

	row_1 = original.append(red, 'x');
	row_2 = green.append(blue, 'x');
	grid = row_1.append(row_2, 'y');
	grid.display();
}
