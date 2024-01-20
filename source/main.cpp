#include "../headers/better_datatypes.h"
#include "../headers/jssp.hpp"
#include "../headers/helpers.hpp"
#include <cstdlib>
i32 main(void){ 
	char const* filename= select_filename(); 
	jssp* job = new jssp(filename); // new because i want to call constructor
	// this is so stupid wtf?
	free((void*)filename);
	
//	job->askhsh1();	
// 	job->askhsh2();
	job->askhsh3();
	 
	// for testing only, works perfectly with mt10.txt and mt20.txt
	//job->print();  	
	
	delete job;
	
	return 0;
}
