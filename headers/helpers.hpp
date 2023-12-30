#ifndef JSSP_HEADERS_HELPERS_HPP_
#define JSSP_HEADERS_HELPERS_HPP_

#include <fstream>
#include "better_datatypes.h"

namespace JSSP{
	void handle_args(i32 const argc, char const* const* const argv);
	void handle_file(char const* const filename);
	u64 get_choice(void);

	namespace file_parser{

		u64 get_job_number(std::ifstream& file_instance);
		u64 get_machine_number(std::ifstream& file_instance);
		u64** get_time_required(std::ifstream& file_instance); // [job][machine]
		u64** get_machine_order(std::ifstream& file_instance); // [job][machine]

	}

}

#endif // JSSP_HEADERS_HELPERS_HPP_
