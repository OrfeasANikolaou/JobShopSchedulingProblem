#include "../headers/error_checkers.hpp"
#include "../headers/jssp.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
jssp::jssp(char const* const filename){
	this->execution_time = NULL;
	this->execution_time = NULL;
	this->desired_time = NULL;
	if (argument_checker(filename) !=
			status_code::SUCCESS) { exit(1); }
	this->read_file(filename);
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

void jssp::print(void){
	std::cout << "Job number: " << this->job_number << std::endl <<
							 "Machine number: " << this->machine_number << std::endl;
	std::cout << "------DESIRED TIME------\n";
	for (u64 i = 0; i < job_number; ++i){
		std::cout << "Desired time for job[" << i+1 << "]: " << this->desired_time[i] << std::endl;
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

void jssp::askhsh1(void){
	std::cout << "-------------" << std::endl 
						<< "|EXERCISE A1|" << std::endl 
						<< "-------------"<< std::endl;
	std::cout << "Select what job you want to see times and machine order: " << std::endl;
	for (u64 i = 0; i < this->job_number; ++i){
		std::cout << i + 1 << ' ';
	}
	std::cout << std::endl;
	u64 x;
	do{
		std::cin >> x;
	}while(x < 1 || x > this->job_number);
	this->print_times(x);
	this->print_machine_order(x);
}

void jssp::askhsh2(void){
	std::cout << "-------------" << std::endl 
						<< "|EXERCISE A2|" << std::endl 
						<< "-------------"<< std::endl;
	u64 sel = this->select();
	switch (sel){
		case 0:
			this->print_sorted_due();
			break;
		case 1:
			this->print_sorted_total();
			break;
		case 2:
			this->print_sorted_machine_total_work_time();
			break;
	}
}

void jssp::askhsh3(void){
	std::cout << "------------" << std::endl 
						<< "|EXERCISE B|" << std::endl 
						<< "------------"<< std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;
	std::cout << "Each column on the terminal are 10 time units." << std::endl 
						<< "Each number is a job, in the case it takes more than 10 units," << std::endl
						<< "it will be followed by a dot. Time will be rounded up. " 				<< std::endl
					 	<< "which will be rounded to the upper limit." << std::endl
						<< "(i.e. a job which takes 31 time units will be displayed as 40)." << std::endl;
	std::cout << "---------------------------------------------------------------" << std::endl;	

	/* my version */
	//for (u64 i = 0; i < this->machine_number; ++i){
	//	std::cout << "Machine " << i+1 << ": ";
	//	for (u64 j = 0; j < this->job_number; ++j){
	//		if (this->execution_order[j][i] == i+1) { std::cout << j+1; }
	//	}
	//	std::cout << std::endl;
	//}	
	
	/* chatgpt version https://chat.openai.com/share/2114430c-868a-4363-853e-091c09bfdd24 */
	//for (u64 i = 0; i < this->machine_number; ++i) {
	//	std::cout << "Machine " << i + 1 << "-->";
	//	for (u64 j = 0; j < this->job_number; ++j) {
	//		u64 currentJob = this->execution_order[j][i];
	//		u64 time = this->execution_time[currentJob - 1][i];
	//		for (u64 k = 0; k < time; ++k) {
	//			std::cout << currentJob;
	//		}
	//	}
	//	std::cout << std::endl;
	//	}	

	std::stringstream* ss = new std::stringstream[this->machine_number];
	for (u64 j = 0; j < this->job_number; ++j){
		for (u64 a = 0 ; a < this->job_number; ++a){
			for (u64 i = 0; i < this->machine_number; ++i){
				if (this->execution_order[a][i]-1 == j-i) {
					u64 time_required = this->execution_time[a][i];
					ss[i] << a+1; for (u64 k = 1; k < time_required; k+=10) {ss[i] << '.';}
				}
			}
		}
	}
	for (u64 i = 0; i < this->machine_number; ++i){
		std::cout << "Machine " << i+1 << ": ";
		std::cout << ss[i].str() << std::endl;
	}
	delete[] ss;				

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
	// for some reason cnt was one more than expected
	// 3 ΏΡΕΣ ΚΑΙ Η ΜΌΝΗ ΑΛΛΑΓΉ ΠΟΥ ΈΠΡΕΠΕ ΝΑ ΚΆΝΩ ΉΤΑΝ ΝΑ ΒΆΛΩ ΈΝΑ --cnt
	--cnt; 
	std::cout << "cnt: " << cnt << std::endl 
						<< "max: " << max_count << std::endl;
	f.clear();
	f.seekg(0, f.beg);
	f >> temp; f >> temp;
	if (cnt != max_count) { std::cout << (cnt != max_count); f >> temp; } 
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

void jssp::print_times(u64 const job) const{
	std::cout << "Due time for job " << job << ": " << this->desired_time[job-1] << std::endl;
	for (u64 i = 0; i < this->machine_number; ++i){
		std::cout << "Time for machine " << i + 1 << " for this job: " << this->execution_time[job-1][i]
			<< std::endl;
	}
}

void jssp::print_machine_order(u64 const job) const{
	std::cout << "Execution order: ";
	for (u64 i = 0; i < this->machine_number; ++i){
		std::cout << this->execution_order[job-1][i] << ' ';
	}
	std::cout << std::endl;
}

u64 jssp::select(void) const{
	std::cout << "Choose sorting order: " << std::endl;
	std::cout << "1. Sort by job due date.\n" 
						<< "2. Sort by job total work time.\n"
						<< "3. Sort by machine totaling work time\n";
	u64 ret;
	do{
		std::cin >> ret;
	}while(ret < 1 || ret > 3);
	return ret - 1; // for array [0..2]
}

void jssp::print_sorted_due(void){
	u64* t = (u64*)malloc(sizeof(u64) * this->job_number);
	u64* pos = (u64*)malloc(sizeof(u64) * this->job_number); 
	for (u64 i = 0; i < this->job_number; ++i){
			t[i] = this->desired_time[i];
			pos[i] = i;
	}
	std::sort(&pos[0], &pos[this->job_number], [&t](u64 a, u64 b){ return t[a] < t[b]; });
	std::sort(&t[0], &t[this->job_number]); 
	for (u64 i = 0; i < this->job_number; ++i){ 
		std::cout << "Due time for job n." << pos[i]+1 << ": " << t[i] << std::endl; 
	} 
	free(t);
	free(pos);
}

void jssp::print_sorted_total(void){
	u64* t = (u64*)malloc(sizeof(u64) * this->job_number);
	u64* pos = (u64*)malloc(sizeof(u64) * this->job_number);
	for (u64 i = 0; i < this->job_number; ++i){
		t[i] = 0;
		pos[i] = i;
		for (u64 j = 0; j < this->machine_number; ++j){
			t[i] += this->execution_time[i][j];
		}
	}
	std::sort(&pos[0], &pos[this->job_number], [&t](u64 a, u64 b){ return t[a] < t[b]; });
	std::sort(&t[0], &t[this->job_number]);
	for (u64 i = 0; i < this->job_number; ++i) { 
		std::cout << "Total work time for job n." << pos[i]+1 << ": " <<  t[i] << std::endl; 
	}
	
	free(t);
	free(pos);
}

void jssp::print_sorted_machine_total_work_time(void){
	u64* t = (u64*)malloc(sizeof(u64) * this->machine_number);
	u64* pos = (u64*)malloc(sizeof(u64) * this->machine_number);
	for (u64 i = 0; i < this->machine_number; ++i){
		t[i] = 0;
		pos[i] = i;
		for (u64 j = 0; j < this->job_number; ++j){
			t[i] += this->execution_time[j][i];
		}
	}
	std::sort(&pos[0], &pos[this->machine_number], [&t](u64 a, u64 b){ return t[a] < t[b]; });
	std::sort(&t[0], &t[this->machine_number]);
	for (u64 i = 0; i < this->machine_number; ++i){
		std::cout << "Total work time for machine n." << pos[i]+1 << ": " << t[i] << std::endl;
	}
	free(t);
	free(pos);
}


