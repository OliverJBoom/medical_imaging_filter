#ifndef UI
#define UI

#include <iostream>
#include <vector>



class user {

	public:

		std::string file_name;
		char effect;

		void welcome();
		void name_input();
		void valid_file();
		bool in_dir = false;
		void filter_select();
};

#endif
