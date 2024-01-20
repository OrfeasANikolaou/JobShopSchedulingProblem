#include "../headers/better_datatypes.h"
#include "../headers/jssp.hpp"
#include "../headers/helpers.hpp"
#include <cstdlib>
i32 main(void){ 
	char const* filename= select_filename(); 
	jssp* job = new jssp(filename); // new because i want to call constructor
	free((void*)filename);
		job->askhsh1();
		job->askhsh2();
		// doesn't work as intended :(
		job->askhsh3(); 
	 
	// for testing only
//	job->print();  	
	delete job;
	return 0;
}
