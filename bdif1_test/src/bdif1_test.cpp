/*
 ============================================================================
 Name        : bdif1_test.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C++,
 ============================================================================
 */
#include <exception>
#include <iostream>
#include <climits>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <thread>
#include "bdif1_test.h"

#define START_TIMER std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now()
#define END_TIMER std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now()
#define ELAPSED_TIME std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()

#include <fstream>


using namespace std;

//posix_time::to_iso_extended_string(

int main(void) {

	std::ifstream in("data100k.txt");
	std::ofstream out("data_clean.txt");


	START_TIMER;

	while (in)
	{
		try{
      string line;
	  getline( in, line);
	  if(!line.empty()){
	  DataRecord2 dr(line);
	  out << dr << endl;
	  }
		}catch(boost::exception &e){
			cout << "Boost Exception!" << '\n';
		}catch(std::exception &e){
			cout << e.what() << '\n';
		}
	}


	END_TIMER;

	cout << ELAPSED_TIME << endl;

	return 0;
}

