#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"



void hello_world() {
	std::cout << "Hello World!" << std::endl;
	system("pause");
}


void vector_print(std::vector <int> vec)
{
	for (auto &i : vec)
		std::cout << i << std::endl;
}