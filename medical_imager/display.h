#ifndef DISPLAY
#define DISPLAY


#include "CImg.h"


using namespace cimg_library; 

class display
{
public:
	void before_after(CImg<unsigned char> original, CImg<unsigned char> filtered);
	void warhol(CImg<unsigned char> original, CImg<unsigned char> red, CImg<unsigned char> green, CImg<unsigned char> blue);

	//~display();
};

#endif
