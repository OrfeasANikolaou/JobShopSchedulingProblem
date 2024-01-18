#include "../headers/better_datatypes.h"
#include "../headers/jssp.hpp"
i32 main(i32 argc, char* argv[]){ // main parameter types must be int and char**
	jssp job(argc, argv);	
	job.print();	
	return 0;
}
