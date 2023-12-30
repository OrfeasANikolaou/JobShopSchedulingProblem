#include <iostream>
#include <fstream>
#include <cstring>
#include "../headers/error_checkers.hpp"
namespace jsspec = JSSP::error_checkers; 
jsspec::status_code jsspec::argument_checker(i32 const argc, char const* const  argv[]){
	
	// BAD ARGC
	if (argc != 2){
		std::cout << "Usage: [PROGRAM] [RELATIVE_FILE_PATH]\n";
		return jsspec::status_code::BAD_ARGC;
	}

	// NO FILE FOUND
	{
		std::ifstream f(argv[1]);
		if (!f.good() || strlen(argv[1]) == 2) { 
			std::cout << "No file found\n";
			return jsspec::status_code::NO_FILE; }
	}

	// FILE NO TXT
	{
		u64 sz = strlen(argv[1]);
		if (strcmp(&argv[1][sz-4], ".txt") != 0){
			std::cout << "File extension must be .txt\n";
			return jsspec::status_code::NO_TXT;
		}
	}

	return jsspec::status_code::SUCCESS;
}
