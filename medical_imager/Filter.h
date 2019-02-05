#ifndef FILTER
#define FILTER


#include <iostream>
#include <vector>


#include "CImg.h"


using namespace std;
using namespace cimg_library;



class Filter 
{
	public:

		CImg<unsigned char> greyscale(CImg<unsigned char> src);
		CImg<unsigned char> colour_swap(CImg<unsigned char> src);
		CImg<unsigned char> brighten(CImg<unsigned char> src, int level);

		void set_dim(int width, int height, int depth);
		int width;
		int height;
		int depth;

	private:

};


#endif