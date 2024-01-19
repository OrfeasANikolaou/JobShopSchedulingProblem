#include "../headers/better_datatypes.h"
#include "../headers/jssp.hpp"
#include "../headers/helpers.hpp"
#include <cstdlib>
i32 main(void){ 
	char const* selection = select_filename(); 
	jssp job(selection);
	job.askhsh1();	
 	job.askhsh2();
	// job.print(); for testing

	// this is so stupid wtf?
	free((void*)selection);
	return 0;
}
