#include "../headers/error_checkers.hpp"
#include "../headers/jssp.hpp"
#include <iostream>
#include <fstream>

jssp::jssp(i32 const argc, char const* const* const argv){
	this->execution_time = NULL;
	this->execution_order = NULL;
	this->desired_time = NULL;
	if (argument_checker(argc, argv) != 
			status_code::SUCCESS) { exit(1); }
	this->read_file(argv[1]);	
}
jssp::jssp(u64 const& jn, u64 const& mn, 
					 u64** const& et, u64** const& eo){
	this->job_number = jn; this->machine_number = mn;
	this->allocate();
		for (u64 i = 0; i < this->job_number; ++i){
			for (u64 j = 0; j < this->job_number; ++j){
				this->execution_time = et;
				this->execution_order = eo;		
			}
		}
	this->calc_desired_time();
}
jssp::~jssp(){
	for (u64 i = 0; i < this->job_number; ++i){
		free(this->execution_time[i]);
		free(this->execution_order[i]);
	}
	free(this->execution_time);
	free(this->execution_order);
	free(this->desired_time);
}
void jssp::print(void) const{
	std::cout << "Job number: " << this->job_number << std::endl <<
							 "Machine number: " << this->machine_number << std::endl;
	std::cout << "------DESIRED TIME------\n";
	for (u64 i = 0; i < job_number; ++i){
		std::cout << "Desired time for job[" << i << "]: " << this->desired_time[i] << std::endl;
	}
	std::cout << "------------------------\n";
	for (u64 i = 0; i < job_number; ++i){
		for (u64 j = 0; j < machine_number; ++j){
			std::cout << this->execution_time[i][j] << ' ';		
		}
		std::cout << std::endl;
	}
	for (u64 i = 0; i < job_number; ++i){
		for (u64 j = 0; j < machine_number; ++j){
			std::cout << this->execution_order[i][j] << ' ';
		}
		std::cout << std::endl;
	}

}
void jssp::calc_desired_time(double param){
	
	for (u64 i = 0; i < this->job_number; ++i){
		this->desired_time[i] = 0;
		for (u64 j = 0; j < this->machine_number; ++j){
			this->desired_time[i] += this->execution_time[i][j];
		}
		this->desired_time[i] *= param;
	}
}
void jssp::read_file(char const* const filename){
	std::ifstream f(filename);
	f >> this->job_number;
	f >> this->machine_number;
	
	u64 const max_count = (job_number * machine_number) << 1;	
	u64 cnt = 0;
	u64 temp;	
	while (f.good()){
		f >> temp;
		++cnt;	
	}
	f.clear();
	f.seekg(0, f.beg);
	f >> temp; f >> temp;
	if (cnt != max_count) { f >> temp; } 
	
	this->allocate();	
	auto fun	= [&](u64** arr)->void {
		for (u64 i = 0; i < this->job_number; ++i){
			for (u64 j = 0; j < this->machine_number; ++j){
				f >> arr[i][j];
			}
		}	
	};

	// gets execution_time for problem
	fun(execution_time);
	// gets execution_order for problem
	fun(execution_order);
	// get desired time default parameter is 1.3
	this->calc_desired_time();
}
void jssp::allocate(void){
	// ξέρω ότι κανονικά πρέπει να κάνω NULL checks κτλ και αν είναι κάποιος δείκτης NULL
	// τότε κάνω free όλα τα προηγούμενα και κάνω exit(1)/exit(error_code) το πρόγραμμα
	this->execution_time = 
		(u64**)malloc(sizeof(u64*) * this->job_number);
	this->execution_order =
		(u64**)malloc(sizeof(u64*) * this->job_number);
	for (u64 i = 0; i < this->job_number; ++i){
		this->execution_time[i] = 
			(u64*)malloc(sizeof(u64) * this->machine_number);
		this->execution_order[i] =
			(u64*)malloc(sizeof(u64) * this->machine_number);
	}
	this->desired_time = (u64*)malloc(sizeof(u64) * this->job_number);
}

