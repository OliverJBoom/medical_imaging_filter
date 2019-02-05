#ifndef CONVOLUTION
#define CONVOLUTION
#include <iostream>
#include <array>
#include <vector>
#include <string>

#include "Convolution.h"
#include "Filter.h"
#include "CImg.h"
#include "Utils.h"


using namespace cimg_library;
using namespace std;



class Kernel: public Filter{
	public: 

		// Class attributes
		vector<vector<int>> kernel_array;
		int kernel_dim;
		int norm;

		// Class Methods
		void vector_select(char effect);
		void place();
		void print();
		void set_norm(int value);

		CImg<unsigned char> conv(CImg<unsigned char> src);

	private:

		vector<int> conv_vec;
};


#endif
