#include <iostream>
#include <string>
#include <vector>

#include "Utils.h"


using namespace std;


void hello_world() {
	cout << "Hello World!" << endl;
	system("pause");
}


void vector_print(vector <int> vec)
{
	for (auto &i : vec)
		cout << i << endl;
}