#ifndef UI
#define UI

#include <iostream>
#include <vector>
#include "Filter.h"
#include "Convolution.h"
#include "CImg.h"



class User {

	public:
		//Class attributes
		std::string file_name;
		char effect;
		char decision;
		bool in_dir = false;

		void welcome();
		void name_input();
		void valid_file();
		void filter_select();

		//Class methods
		CImg<unsigned char> wrapper_function(CImg<unsigned char> src, Filter Fil, Kernel convolve);
		CImg<unsigned char> extra_filter(CImg<unsigned char> src, CImg<unsigned char> , Filter Fil, Kernel convolve);
};

#endif
