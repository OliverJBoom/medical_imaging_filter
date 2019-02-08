#include <iostream>
#include <string>
#include "UI.h"
#include "Filter.h"
#include "Convolution.h"

#include <filesystem>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;


void user::welcome() {
	/*
	std::string dir = __FILE__;
	const auto pos = dir.find_last_of("\\");
	std::cout << "Pos:" << pos << std::endl;
	std::string s;
	dir = dir.substr(0, pos);
	std::cout << dir;
	*/

	std::cout << "Welcome to Apollo Medical Imagine Corporation\n" << std::endl;
	std::cout << std::endl << "World leaders in medical imaging technology\n" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	std::cout << "These are the names of your files:\n" << std::endl;
	std::string path = "\Images";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	for (const auto & entry : fs::directory_iterator(path)){
		std::string f;
		f = entry.path().string();
		//std::cout << f << std::endl;

		const auto pos = f.find_last_of("\\");
		//std::cout << "Pos:" << pos << std::endl;
		f = f.substr(pos);
		//std::cout << f;

		std::cout << f << std::endl;
		//std::cout << entry.path() << std::endl;
	}

}

void user::name_input(){
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "Please type the name of your file into the terminal including its extention\n" << std::endl;
	std::cin >> file_name;
	this->valid_file();
}


void user::valid_file() {
	
	if (file_name.at(0) == '\\') {
		file_name = file_name.erase(0, 1);
	}

	std::string path = "\Images";

	for (const auto & entry : fs::directory_iterator(path)) {
		std::string f;
		f = entry.path().string();
		if (("Images\\" + file_name) == f) {
			in_dir = true;
		}
	}

	if (in_dir != true) {
		std::cout << "You have entered an incorrect name. Please try again!" << std::endl;
		this->name_input();
	}
	else {
		file_name = "Images//" + file_name;
	}
}



void user::filter_select() {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << std::endl << "\nPerfect! Time to select your filter." << std::endl;
	std::cout << "Your options are:" << std::endl;

	std::cout << "Greyscale:        Code 'a'" << std::endl;
	std::cout << "Brighten:         Code 'b'" << std::endl;
	std::cout << "Low pass filter:  Code 'c'" << std::endl;
	std::cout << "High pass filter: Code 'd'" << std::endl;
	std::cout << "Band pass:        Code 'e'" << std::endl;

	std::cout << "Sharpen (Low):    Code 'f'" << std::endl;
	std::cout << "Sharpen (High):   Code 'g' " << std::endl;
	std::cout << "Gaussian blur :   Code 'h'" << std::endl;
	std::cout << "Unsharp masking:  Code 'i'" << std::endl;
	std::cout << "Blur (Low):       Code 'j'" << std::endl;
	std::cout << "Blue (High):      Code 'k'" << std::endl;
	std::cout << "Edge detection:   Code 'l'" << std::endl;
	std::cout << "Psychadelic:      Code 'm' \t" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "\nFailure to enter a correct code will result in your original image being return unfiltered." << std::endl;
	std::cout << "And you wouldnt want that would you!" << std::endl;

	std::cout << "So what'll it be?" << std::endl;

	std::cin >> effect;
}



CImg<unsigned char> user::wrapper_function(CImg<unsigned char> src, Filter Fil, Kernel convolve){
	CImg<unsigned char> out;
	int level;

	if (effect == 'a') {				 //Greyccale
		out = Fil.greyscale(src);
	}
	else if (effect == 'b') {			 //Brighten
		std::cout << "What level brightening would you like to input (between 0-256)\n";
		std::cin >> level;
		out = Fil.brighten(src, level);
	}
	else if (effect == 'c') {			 //Low pass filter
		std::cout << "Below what level brightness would you like to pass (between 0-256)\n";
		std::cin >> level;
		out = Fil.low_pass(src, level);
	}
	else if (effect == 'd') {			 //High pass filter
		std::cout << "Over what level brightness would you like to pass (between 0-256)\n";
		std::cin >> level;
		out = Fil.high_pass(src, level);
	}
	else if (effect == 'e') {			 //Band pass filter
		std::cout << "Between what level brightnesses would you like to pass (between 0-256)\n";
		int low_lim;
		int up_lim;
		std::cin >> low_lim;
		std::cin >> up_lim;
		out = Fil.band_pass(src, low_lim, up_lim);
	}
	else {								 //All convolve effects	
		std::cout << "Running convolution\n";
		convolve.set_dim(Fil.width, Fil.height, Fil.depth);
		convolve.vector_select(effect);
		convolve.place();
		out = convolve.conv(src);
	}
return out;
}
