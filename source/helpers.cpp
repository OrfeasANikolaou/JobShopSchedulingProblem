#include "../headers/better_datatypes.h"
#include "../headers/error_checkers.hpp"
#include "../headers/helpers.hpp"

void JSSP::handle_args(i32 const argc, char const* const* const argv){
	
	if (JSSP::error_checkers::argument_checker(argc, argv) !=
			JSSP::error_checkers::status_code::SUCCESS) { exit(1); }
	JSSP::handle_file(argv[1]); // handle_choice inside handle_file because that's how it's asked to

}

void JSSP::handle_file(char const* const filename){

	std::ifstream f(filename);
	u64 job_number = JSSP::file_parser::get_job_number(f);
	u64 machine_number = JSSP::file_parser::get_machine_number(f);
	u64** time_req = JSSP::file_parser::get_time_required(f);
	u64** machine_order = JSSP::file_parser::get_machine_order(f);
	
	
	for (u64 i = 0; i < job_number; ++i){
		delete[] time_req[i];
		delete[] machine_order[i];
	}
	delete[] time_req;
	delete[] machine_order;

}

u64 JSSP::file_parser::get_job_number(std::ifstream& file_instance){
	u64 x;
	file_instance >> x;
	return x;
}

u64 JSSP::file_parser::get_machine_number(std::ifstream& file_instance){
	u64 x;
	file_instance >> x;
	return x;
}

