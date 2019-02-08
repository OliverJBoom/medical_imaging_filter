#ifndef UI
#define UI

#include <iostream>
#include <vector>
#include "Filter.h"
#include "Convolution.h"
#include "CImg.h"


class user {

	public:

		std::string file_name;
		char effect;
		CImg<unsigned char> wrapper_function(CImg<unsigned char> src, Filter Fil, Kernel convolve);

		void welcome();
		void name_input();
		void valid_file();
		bool in_dir = false;
		void filter_select();

};

#endif
