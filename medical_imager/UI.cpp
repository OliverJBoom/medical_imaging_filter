#include <iostream>
#include <string>
#include "UI.h"
#include <filesystem>

namespace fs = std::filesystem;

void welcome() {
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

	std::string path = "\Images";
	//std::string f;

	for (const auto & entry : fs::directory_iterator(path))
		//std::string f = entry.path().string();
		//std::cout << f << std::endl;
		std::cout << entry.path() << std::endl;
}