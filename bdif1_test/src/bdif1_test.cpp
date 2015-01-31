/*
 ============================================================================
 Name        : bdif1_test.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Big Data in Finance Assigment 1
 ============================================================================
 */
#include <exception>
#include <iostream>
#include <climits>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <thread>
#include "DataRecord.h"

#define START_TIMER std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now()
#define END_TIMER std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now()
#define ELAPSED_TIME std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()


using namespace std;


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
	  DataRecord dr(line);
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

