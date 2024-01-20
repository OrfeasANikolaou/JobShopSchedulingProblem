#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "jssp.hpp"
u64** et = NULL; u64** eo = NULL;
void fn(void){
	et = (u64**)malloc(sizeof(u64*)*3);
	eo = (u64**)malloc(sizeof(u64*)*3);
	for(u64 i = 0; i < 3; ++i){
		et[i] = (u64*)malloc(sizeof(u64)*3);
		eo[i] = (u64*)malloc(sizeof(u64)*3);
		for (u64 j = 0; j < 3; ++j){
			et[i][j] = (j*i+1)<<3;
			eo[i][j] = i + 1;
		}
	}
		
}
TEST_CASE("desired_time"){
	fn();
	jssp* job = new jssp(3, 2,et,eo);	
	job->calc_desired_time(); // a little bit of cheating with header file ;)
	REQUIRE(job->desired_time[0]==20);
	REQUIRE(job->desired_time[1]==31);
	REQUIRE(job->desired_time[2]==41);
}
