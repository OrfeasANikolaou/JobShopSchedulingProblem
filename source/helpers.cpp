#include "../headers/helpers.hpp"
#include "../headers/better_datatypes.h"
#include <iostream>
#include <string>
#include <cstring>
char const* const select_filename(void){
	std::cout << "Choose a file to use as a job stop scheduling problem \n" << 
							 "All of them are inside the data/ folder\n" << 
							 "Choose one of the following JSS problems to pick from:\n";
	char* ret = (char* )malloc(sizeof(char) * 14);
	u64 x;
	std::string files[8] = {"la01",
													"la02",
													"la03",
													"la04",
													"la05",
													"mt06",
													"mt10",
													"mt20", };
	for (u64 i = 0; i < 8; ++i){
		files[i] = "data/" + files[i] + ".txt";
	}
	do{
		std::cout << "1. la01.txt\n" <<
									 "2. la02.txt\n" << 
									 "3. la03.txt\n" <<
									 "4. la04.txt\n" <<
									 "5. la05.txt\n" <<
									 "6. mt06.txt\n" <<
									 "7. mt10.txt\n" <<
									 "8. mt20.txt\n";
		std::cin >> x;
	}while(x < 1 || x > 8);
	memcpy(ret, files[x-1].c_str(), 14);
	return ret;
}

