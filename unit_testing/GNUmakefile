CC = g++
LINKING = 
CFLAGS = -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow -std=c++11
S = ../source/
SOURCE = $(S)/error_checkers.cpp ./unique_jssp.cpp $(S)/helpers.cpp ./unit_tests.cpp
main: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o tests 
