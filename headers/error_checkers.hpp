#ifndef JSSP_HEADERS_ERROR_CHECKERS_HPP_
#define JSSP_HEADERS_ERROR_CHECKERS_HPP_

#include "better_datatypes.h"
		// enums for return status code
		enum class status_code{ SUCCESS = 0, 
														BAD_ARGC, 
														NO_FILE, 
														NO_TXT, };	

		// checks if there is a problem with args returns status_code::SUCCESS if no errors
		status_code	argument_checker(i32 const , char const* const []);					
#endif // JSSP_HEADERS_ERROR_CHECKERS_HPP_
