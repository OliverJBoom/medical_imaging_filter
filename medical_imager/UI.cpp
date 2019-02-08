#include <iostream>
#include <string>

#include "UI.h"
#include "Filter.h"
#include "Convolution.h"

#include <filesystem>
#include <chrono>
#include <thread>

namespace fs = std::filesystem;



// Lists the image options in the directory
void User::welcome() {
	std::cout << "Welcome to Apollo Medical Imagine Corporation\n" << std::endl;
	std::cout << std::endl << "World leaders in medical imaging technology\n" << std::endl;

	//These statements add a delay between terminal prints
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "These are the names of your files:\n" << std::endl;
	std::string path = "\Images";
	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	//Iterates through the directory
	for (const auto & entry : fs::directory_iterator(path)){
		std::string f;
		f = entry.path().string();

		//Only prints the string after the final slash
		const auto pos = f.find_last_of("\\");
		f = f.substr(pos);
		std::cout << f << std::endl;
	}
}



// Allows the user to select the file name
void User::name_input(){
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "Please type the name of your file into the terminal including its extention\n" << std::endl;
	std::cin >> file_name;
	valid_file();
}



// Checks to see if the file is in the directory
void User::valid_file() {

	if (file_name.at(0) == '\\') {
		file_name = file_name.erase(0, 1);
	}

	std::string path = "\Images";

	//Iterates through the directory to see if there is a match
	for (const auto & entry : fs::directory_iterator(path)) {
		std::string f;
		//Finds the path of each file
		f = entry.path().string();
		if (("Images\\" + file_name) == f) {
			in_dir = true;
		}
	}

	//If no match then repeats prompt
	if (in_dir != true) {
		std::cout << "You have entered an incorrect name. Please try again!" << std::endl;
		this->name_input();
	}
	else {
		file_name = "Images//" + file_name;
	}
}


//Allows the user to select the filter
void User::filter_select() {
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << std::endl << "\nPerfect! Time to select your filter." << std::endl;
	std::cout << "Your options are:\n" << std::endl;

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
	std::cout << "Blur (High):      Code 'k'" << std::endl;
	std::cout << "Edge detection:   Code 'l'" << std::endl;
	std::cout << "Psychadelic:      Code 'm'" << std::endl;
	std::cout << "Colour Swap:      Code 'n'" << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::cout << "\nFailure to enter a correct code will result in your original image being return unfiltered." << std::endl;
	std::cout << "And you wouldnt want that would you!" << std::endl;

	std::cout << "So what'll it be?" << std::endl;

	std::cin >> effect;
}



//Allows the user to additional filters on top of greyscale
CImg<unsigned char> User::extra_filter(CImg<unsigned char> src, CImg<unsigned char> out, Filter Fil, Kernel convolve) {
	//Adds extra filter if selected
	if (decision == 'y') {
		std::cout << "What other filter would you like? \nCode:";
		std::cin >> effect;
		if (effect == 'a') {
			std::cout << "\nEnter a new filter!";
			extra_filter(src, out, Fil, convolve);
		}
		return out;
	}
	//Returns greyscale image for not selected
	else if (decision == 'n') {
		return out;
	}
	else {
		std::cout << "\nI'm sorry but you haven't entered a valid y/n option, please try again.\n";
		std::cin >> decision;
		extra_filter(src, out, Fil, convolve);
		return out;
	}
}



//The primary wrapper function for the filters
CImg<unsigned char> User::wrapper_function(CImg<unsigned char> src, Filter Fil, Kernel convolve){

	CImg<unsigned char> out;
	int level;

	//Selects the filter according to the users inputs
	if (effect == 'a') {									//Greyscale
		std::cout << "\nEffect: Greyscale";
		out = Fil.greyscale(src);
		std::cout << "\nWould you also like to apply further filters (y/n)?\n";
		std::cin >> decision;
		extra_filter(src, out, Fil, convolve);

		if (decision == 'n'){
			return out;
		}
	}

	if (effect == 'b') {									//Brighten
		std::cout << "What level brightening would you like to input (between 0-256)\n";
		std::cin >> level;
		out = Fil.brighten(src, level);
	}
	else if (effect == 'c') {								//Low pass filter
		std::cout << "\nEffect: Low pass filter\n";

		std::cout << "Below what level brightness would you like to pass (between 0-256)\n";
		std::cin >> level;
		out = Fil.low_pass(src, level);
	}
	else if (effect == 'd') {								//High pass filter
		std::cout << "\nEffect: High pass filter\n";

		std::cout << "Over what level brightness would you like to pass (between 0-256)\n";
		std::cin >> level;
		out = Fil.high_pass(src, level);
	}
	else if (effect == 'e') {								//Band pass filter
		std::cout << "\nEffect: Band pass filter\n";

		std::cout << "Between what level brightnesses would you like to pass (between 0-256)\n";
		int low_lim;
		int up_lim;
		std::cin >> low_lim;
		std::cin >> up_lim;
		out = Fil.band_pass(src, low_lim, up_lim);
	}
	else if (effect == 'n') {								 //Band pass filter
		std::cout << "\nEffect: Colour Swap\n";
		out = Fil.colour_swap(src);
	}
	else {													//All convolve effects	
		std::cout << "Running convolution\n";
		convolve.set_dim(Fil.width, Fil.height, Fil.depth);
		convolve.vector_select(effect);
		convolve.place();
		out = convolve.conv(src);
	}
return out;
}
