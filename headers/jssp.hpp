#ifndef JSSP_HEADERS_HELPERS_HPP_
#define JSSP_HEADERS_HELPERS_HPP_
#include "better_datatypes.h"
struct jssp{
	public:
		// constructor to be called if any other input for filename is desired
		jssp(char const* const filename);
		// constructor given raw data to create problem
		jssp(u64 const& jn,
				 u64 const& mn,
				 u64** const& et,
				 u64** const& eo);
		// frees all malloc'd() memory from constructors
		~jssp();
		// prints job number, machine number, desired times, and raw array data
		void print(void);
		void askhsh1(void);
		void askhsh2(void);
		void askhsh3(void);
	private:
		u64 job_number;
		u64 machine_number;
		// [job_number][machine_number]
		u64** execution_time;
		u64** execution_order;
		u64* desired_time;	
		// parses file
		void read_file(char const* const filename);
		// allocates memory for execution_time, execution_order and desired_time
		void allocate(void);
		// calculates desired time based on summation of execution time per job
		void calc_desired_time(double const param = 1.3);
		// prints time required of a job in each machine
		void print_times(u64 const job) const;
		// prints execution order of a job
		void print_machine_order(u64 const job) const;
		// gives user choice between print_sorted_due(), print_sorted_total and
		// print_sorted_machien_total_work_time()
		u64 select(void) const;
		// prints due time of jobs
		void print_sorted_due(void);
		// prints total time of jobs
		void print_sorted_total(void);
		void print_sorted_machine_total_work_time(void);
};

#endif // JSSP_HEADERS_HELPERS_HPP_
