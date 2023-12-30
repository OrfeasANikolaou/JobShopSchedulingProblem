#ifndef JSSP_HEADERS_ERROR_CHECKERS_HPP_
#define JSSP_HEADERS_ERROR_CHECKERS_HPP_

#include <iostream>
#include "better_datatypes.h"
namespace JSSP{
	namespace error_checkers{ 	
		enum class status_code{ SUCCESS = 0, 
														BAD_ARGC, 
														NO_FILE, 
														NO_TXT, };		// enums for return status code
		status_code	argument_checker(i32 const , char const* const []);					// checks if there is a problem with args returns status_code::SUCCESS if no errors
	}
}
#endif // JSSP_HEADERS_ERROR_CHECKERS_HPP_
