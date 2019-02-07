#include <iostream>
#include <string>
#include "UI.h"
#include <filesystem>

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

	std::cout << "Welcome to Apollo Medical Imagine Corporation" << std::endl;
	std::cout << std::endl << "World leaders in medical imaging technology" << std::endl;

	std::cout << "These are the names of your files:" << std::endl;
	std::string path = "\Images";
	
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
	std::cout << "Please type the name of your file into the terminal including its extention" << std::endl;
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
	std::cout << std::endl << "Perfect! Time to select your filter." << std::endl;
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


	std::cout << "Failure to enter a correct code will result in your original image being return unfiltered." << std::endl;
	std::cout << "And you wouldnt want that would you!" << std::endl;

	std::cout << "So what'll it be?" << std::endl;

	std::cin >> effect;

}

