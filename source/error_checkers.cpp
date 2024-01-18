#include <iostream>
#include <fstream>
#include <cstring>
#include "../headers/error_checkers.hpp"
#include "../headers/better_datatypes.h"
status_code argument_checker(char const* const filename){
	
	// NO FILE FOUND
	{
		std::ifstream f(filename);
		if (!f.good() || strlen(filename) == 2) { 
			std::cout << "No file found\n";
			return status_code::NO_FILE; }
	}

	// FILE NO TXT
	{
		u64 sz = strlen(filename);
		if (strcmp(&filename[sz-4], ".txt") != 0){
			std::cout << "File extension must be .txt\n";
			return status_code::NO_TXT;
		}
	}

	return status_code::SUCCESS;
}
