#include <iostream>
#include <array>
#include <vector>
using namespace std;


array<array<int, 6>, 6> image = {{
						 {11, 12, 13, 14, 15, 16},
						 {21, 22, 23, 24, 25, 26},
						 {31, 32, 33, 34, 35, 36},
						 {41, 42, 43, 44, 45, 46},
						 {51, 52, 53, 54, 55, 56},
						 {61, 62, 63, 64, 65, 66}
}};

array<array<int, 3>, 3> kernel = { {
						 {11, 12, 13},
						 {21, 22, 23},
						 {31, 32, 33}
} };

array<array<int, 4>, 4> output = { {} };





int main(){
	cout << "array size: " << kernel[0].size();
	system("pause");

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			int accum = 0;

			for (int im_row = 0 + x; im_row < 3 + x; im_row++) {
				for (int im_col = 0 + y; im_col < 3 + y; im_col++) {


					for (int ke_row = 0; ke_row < 3; ke_row++) {
						for (int ke_col = 0; ke_col < 3; ke_col++) {
							if (im_row - x == ke_row) {
								if (im_col - y == ke_col) {
									accum = accum + image[im_row][im_col] * kernel[ke_row][ke_col];
									//	cout << accum;
										//system("pause");

								}
							}

						}

					}
					output[x][y] = accum;

				}
			}

		}
	}
	cout << "output[0][0]" << output[0][0] << ", ";
	cout << "output[0][1]" << output[0][1] << ", ";
	cout << "output[0][2]" << output[0][2] << ", ";
	cout << "output[0][3]" << output[0][3] << ", ";
	cout << endl;

	cout << "output[1][0]" << output[1][0] << ", ";
	cout << "output[1][1]" << output[1][1] << ", ";
	cout << "output[1][2]" << output[1][2] << ", ";
	cout << "output[1][3]" << output[1][3] << ", ";
	cout << endl;

	cout << "output[2][0]" << output[2][0] << ", ";
	cout << "output[2][1]" << output[2][1] << ", ";
	cout << "output[2][2]" << output[2][2] << ", ";
	cout << "output[2][3]" << output[2][3] << ", ";
	cout << endl;

	cout << "output[3][0]" << output[3][0] << ", ";
	cout << "output[3][1]" << output[3][1] << ", ";
	cout << "output[3][2]" << output[3][2] << ", ";
	cout << "output[3][3]" << output[3][3] << ", ";
	cout << endl;




	system("pause");

	
	return 0;
}


///

