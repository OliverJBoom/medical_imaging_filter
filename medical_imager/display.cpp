#include "display.h"
#include "CImg.h"



//Diplays both the filtered and unfiltered image together
void display::before_after(CImg<unsigned char> original, CImg<unsigned char> filtered)
{
	original.display();
	filtered.display();	
	CImg<unsigned char> row;
	const char *const a = "text";
	int x_original = original.width();
	int x_filtered = filtered.width();
	row = original.append(filtered, 'x');
	row.display();
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
