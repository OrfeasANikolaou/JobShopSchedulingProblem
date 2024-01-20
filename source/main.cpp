#include "../headers/better_datatypes.h"
#include "../headers/jssp.hpp"
#include "../headers/helpers.hpp"
#include <cstdlib>
#include <cstring>
#include <iostream>
i32 main(void){ 
	char const* filename= select_filename(); 
	jssp* job = new jssp(filename); // new because i want to call constructor
	// για κάποιο λόγο κάνει λάθος read ΜΌΝΟ αυτά τα δύο αρχεία
	if ( !(strcmp(filename, "data/mt10.txt") == 0 ||
		strcmp(filename, "data/mt20.txt") == 0)){ 
		job->askhsh1();
		job->askhsh2();
		job->askhsh3(); 
	}
	else{
		std::cout << "mt10 and mt20 don't work at the moment, please enter other file" << std::endl;
	}
	free((void*)filename);
	 
	// for testing only, works perfectly with mt10.txt and mt20.txt
//	job->print();  	
	delete job;
	return 0;
}
