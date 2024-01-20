#include "../headers/better_datatypes.h"
#include "../headers/jssp.hpp"
#include "../headers/helpers.hpp"
#include <cstdlib>
i32 main(void){ 
	char const* filename= select_filename(); 
	jssp job(filename);
	job.askhsh1();	
 	job.askhsh2();
	// job.print(); 
		
	// this is so stupid wtf?
	free((void*)filename);
	return 0;
}
