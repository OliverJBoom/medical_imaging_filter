  #include <cstddef> 
#include <iostream>
#include <array>
#include <vector>
#include <string>

#include "Convolution.h"
#include "Filter.h"
#include "CImg.h"


using namespace cimg_library;


//Sets the kernel vector based on a desired image filter effect
void Kernel::vector_select(char effect) {

	conv_vec.clear();

	if (effect == 'B') {
		std::vector<int> vec = { 1, 1, 1 , 1, 1, 1, 1, 1, 1 }; // Blur
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3;
		norm = 9;
	}

	else if (effect == 'A') {
		std::vector<int> vec = { 5,5,5,5,5,
								 5,5,5,5,5,
								 5,5,5,5,5,
								 5,5,5,5,5,
								 5,5,5,5,5}; // Blur
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 125;
	}


	else if (effect == 'S') {
		std::vector<int> vec = { 0, -1, 0, -1, 5, -1, 0, -1, 0 }; // Sharpen
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3; 
		norm = 1;
	}

	else if (effect == 'E') {
		std::vector<int> vec = { 0, 1, 0, 1, -4, 1, 0, 1, 0 }; // Edge Detection
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3; 
		norm = 1;
	}

	else if (effect == 'P') {
		std::vector<int> vec =
				 {5, 10, 20, 10, 5, 
				 10, 100, 200, 200, 10,
				 20, 200, -1500, 200, 20, 
			     10, 100, 200, 100, 10,
				 5, 10, 20, 10, 5}; // Custom

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 1;
	}

	else if (effect == 'Q') {
		std::vector<int> vec =
		{1, 4, 6, 4, 1,
		4, 16, 24, 16, 4,
		6, 24, -476, 24, 6,
		4, 16, 24, 16, 4,
		1, 4, 6, 4, 1 }; // UNSHARP MASKING

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = -256;
	}

	else if (effect == 'G') {
		std::vector<int> vec =
		{ 1, 4, 6, 4, 1,
		4, 16, 24, 16, 4,
		6, 24, 36, 24, 6,
		4, 16, 24, 16, 4,
		1, 4, 6, 4, 1 }; // Gaussian Blur

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 256;
	}

	else if (effect == 'S') {
		std::vector<int> vec =
		{ -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1,
		-1, -1, 25, -1, -1,
		-1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1 }; // Sharpening 5x5

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 1;
	}


	else {
		std::vector<int> vec = {0, 0, 0, 
			                    0, 1, 0, 
			                    0, 0, 0 }; // Identity
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3;
		norm = 1;
	}
}



//Loads the desired vector kernel into the kernel
void Kernel::place(){

	std::vector <int> row;
	int i = 0;
	int j = 1;

	while (i < (kernel_dim * kernel_dim)) {
		row.push_back(conv_vec[i]);

		if (j == kernel_dim){
			j = 0;
			kernel_array.push_back(row);
			row.clear();
		}
	i++;
	j++;
	}
}



//Prints the kernel and normalisation factor
void Kernel::print() {
	std::cout << std::endl << std::endl << "Kernel:" << std::endl;
	for (int j = 0; j < kernel_array.size(); j++)
	{
		for (int i = 0; i < kernel_array.size(); i++)
		{
			std::cout << kernel_array[j][i] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << "Norm: " << norm;
}



//Explicitly sets the normalization factor for a kernel
void Kernel::set_norm(int value) {
	norm = value;
}



//Performs convolution on an image using an input kernel
CImg<unsigned char> Kernel::conv(CImg<unsigned char> src) {
	int padding = (kernel_dim - 1) / 2;

	CImg<unsigned char> im_out(width - (2 * padding), height - (2 * padding), depth, 3);

	for (int c = 0; c < 3; c++) {
		 std::cout << "c" << c << std::endl;
		cimg_forXY(src, x, y) {
			if ((x >= padding) && (x < width - padding) && (y >= padding) && (y < height - padding)) {

				int upp_x = x + padding;
				int low_x = x - padding;

				int upp_y = y + padding;
				int low_y = y - padding;

				double accum = 0;
				int count = 0;

				for (int i = low_x; i < upp_x + 1; i++) {
					for (int j = low_y; j < upp_y + 1; j++) {
						accum = accum + (int)src(i, j, 0, c) * kernel_array[i - low_x][j - low_y];
					}
				}

				accum = accum / norm;

				if (accum > 255) {
					im_out(x - padding, y - padding, 0, c) = 255;
				}
				else if (accum < 0) {
					im_out(x - padding, y - padding, 0, c) = 0;
				}
				else {
					im_out(x - padding, y - padding, 0, c) = accum;
				}
			}
		}
	}
	return im_out;
}
