#include "display.h"
#include "CImg.h"



void display::before_after(CImg<unsigned char> original, CImg<unsigned char> filtered)
{
	//original.display();
	//filtered.display();	
	CImg<unsigned char> row;

	// Append horizontally into a row, you could append many - you are not restricted to 2
	row = original.append(filtered, 'x');
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