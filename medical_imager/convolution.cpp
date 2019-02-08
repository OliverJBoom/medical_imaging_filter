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

	if (effect == 'f') {									//Sharpen	
		std::vector<int> vec = { 0, -1, 0, 
					             -1, 5, -1, 
			                     0, -1, 0 }; 
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3;
		norm = 1;
		std::cout << "\nSharpen (Low)\n";
	}
	else if (effect == 'g') {								//Sharpening 5x5
		std::vector<int> vec =
								{ -1, -1, -1, -1, -1,
								  -1, -1, -1, -1, -1,
								  -1, -1, 25, -1, -1,
							   	  -1, -1, -1, -1, -1,
								  -1, -1, -1, -1, -1 }; 

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 1;
		std::cout << "\nSharpen (High)\n";

	}
	else if (effect == 'h') {								//Gaussian Blur
		std::vector<int> vec =
								{ 1, 4, 6, 4, 1,
								  4, 16, 24, 16, 4,
							      6, 24, 36, 24, 6,
								  4, 16, 24, 16, 4,
								  1, 4, 6, 4, 1 }; 

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 256;
		std::cout << "\nGaussian Blur\n";

	}
	else if (effect == 'i') {								//UNSHARP MASKING	
		std::vector<int> vec =
								{ 1, 4, 6, 4, 1,
								  4, 16, 24, 16, 4,
								  6, 24, -476, 24, 6,
								  4, 16, 24, 16, 4,
								  1, 4, 6, 4, 1 }; 

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = -256;
		std::cout << "\nUnsharp Masking\n";

	}
	else if (effect == 'j') {								// Blur (Low)

		std::vector<int> vec = 
								{ 1, 1, 1, 
								  1, 1, 1, 
								  1, 1, 1 }; 
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3;
		norm = 9;
		std::cout << "\nBlur (Low)\n";
	}
	else if (effect == 'k') {								// Blur (High)
		std::vector<int> vec = { 5,5,5,5,5,
								 5,5,5,5,5,
								 5,5,5,5,5,
								 5,5,5,5,5,
								 5,5,5,5,5 }; 
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 125;
		std::cout << "\nBlur High\n";

	}
	else if (effect == 'l') {								//Edge Detection
		std::vector<int> vec = 
								{ -1, -1, -1, 
								  -1, 8, -1, 
								  -1, -1, -1 };
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3;
		norm = 1;
		std::cout << "\nEdge Detection\n";

	}
	else if (effect == 'm') {								//Psychadeli
		std::vector<int> vec =
								{ 5, 10, 20, 10, 5,
								 10, 100, 200, 200, 10,
							     20, 200, -1500, 200, 20,
								 10, 100, 200, 100, 10,
								  5, 10, 20, 10, 5 }; 

		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 5;
		norm = 1;
	}
	else {													//Identity
		std::vector<int> vec = { 0, 0, 0 , 0, 1, 0, 0, 0, 0 }; 
		for (auto &i : vec) {
			conv_vec.push_back(i);
		}
		kernel_dim = 3;
		norm = 1;
		std::cout << "\nThe identity\n";
	}
}



//Loads the desired vector kernel into the kernel
void Kernel::place(){

	std::vector <int> row;
	int i = 0;
	int j = 1;

	//Loads the array into an vector of vectors 
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
	int channels = src.spectrum();

	CImg<unsigned char> im_out(width - (2 * padding), height - (2 * padding), depth, channels);

	cimg_forXYC(src, x, y, c) {
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
	return im_out;
}
