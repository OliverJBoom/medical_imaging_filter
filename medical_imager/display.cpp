#include "display.h"
#include "CImg.h"



void display::before_after(CImg<unsigned char> original, CImg<unsigned char> filtered)
{
	original.display();
	filtered.display();	
	CImg<unsigned char> row;
	const char *const a = "text";
	int x_original = original.width();
	int x_filtered = filtered.width();

	row = original.append(filtered, 'x');
	unsigned char color = 0;
	row.draw_text(x_original/3, 0, "Original", &color, 0, 1, 70);
	row.draw_text(x_filtered/3 + x_original, 0, "Filtered", &color, 0, 1, 70);
	//row.resize(CImgDisplay::_fitscreen(original.width(), original.height(), 1, 0, -100, false),
		//CImgDisplay::_fitscreen(original.width(), original.height(), 1, 0, -100, true), 0);

	row.display();

}

void display::warhol(CImg<unsigned char> original, CImg<unsigned char> red, CImg<unsigned char> green, CImg<unsigned char> blue)
{
	CImg<unsigned char> row_1, row_2, grid;

	row_1 = original.append(red, 'x');
	row_2 = green.append(blue, 'x');
	grid = row_1.append(row_2, 'y');

	grid.display();

}

/*
display::~display()
{
}
*/