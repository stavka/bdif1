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
#include <ctime>
#include <climits>
#include <fstream>
#include <string>
#include <chrono>
#include <random>
#include <thread>
#include <functional>
#include "DataRecord.h"
#include "WorkChunk.h"
#include "Log.h"

#define START_TIMER std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now()
#define END_TIMER std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now()
#define ELAPSED_TIME std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()


using namespace std;

void ThreadFunction(vector<string> &linesToParse, vector<DataRecord> &signalData, vector<DataRecord> &noiseData){
    FILE_LOG(logDEBUG) << "Starting Program";
	for(auto line : linesToParse){

		try{
			DataRecord dr(line);
			signalData.push_back(dr);
		}
		catch(boost::exception &e){
			noiseData.push_back(line);
		}
	    catch(std::exception &e){
	    	noiseData.push_back(line);
		}
	}

}

int main(void) {

	std::ifstream in("data100k.txt");
	std::ofstream out("signal.txt");
	std::ofstream garbage("noise.txt");

	const int runVersion = 2;

	START_TIMER;

	FILELog::ReportingLevel() = FILELog::FromString("DEBUG1");
	FILE_LOG(logINFO) << "Starting Program";

	if(runVersion == 0){
    /// first version, the simplest line by line
		while (in)
		{
			string line;
			try{
				getline( in, line);
				if(!line.empty()){

					DataRecord dr(line);
					out << dr << endl;
				}
			}catch(boost::exception &e){
				FILE_LOG(logERROR) << "Boost Exception!";
				garbage << line;
			}catch(std::exception &e){
				FILE_LOG(logERROR) << e.what();
				garbage << line;
			}
		}
	}else if(runVersion == 1){
	/// test version creating one thread and passing data

		vector<string> allTheData;
		FILE_LOG(logINFO) << "Starting main loop";

		while (in)
		{
			string line;
	        getline( in, line);
			if(!line.empty()){
				allTheData.push_back(line);
			}
		}
		FILE_LOG(logINFO) << "Done loading";

		vector<DataRecord> signalData;
		vector<DataRecord> noiseData;

		std::thread threadOnly;
		threadOnly = std::thread(ThreadFunction, std::ref(allTheData), std::ref(signalData), std::ref(noiseData) );
		threadOnly.join();

		FILE_LOG(logINFO) << "Done with thread";

		for(auto x: signalData) out << x << endl;
		for(auto x: noiseData) garbage << x << endl;

		FILE_LOG(logINFO) << "Files Saved";

	}else if(runVersion == 2){
	// basic multithread version, read all data, copy into threads and run them.

		const int numberOfThreads = 4;

		FILE_LOG(logINFO) << "Starting main loop";

		int lineCounter = 0;
        std::thread allThreads[numberOfThreads];
        WorkChunk wcs[numberOfThreads];
        vector<string> allTheData;

		while (in)
		{
			string line;
			getline( in, line);
			if(!line.empty()){
				++lineCounter;
				allTheData.push_back(line);
			}
		}
		FILE_LOG(logINFO) << "Done loading";

        int linesPerThread;
        linesPerThread = lineCounter/numberOfThreads;
        FILE_LOG(logINFO) << "Lines per thread " << linesPerThread;

        for(int tn=0; tn < numberOfThreads; ++tn){
           // setup work
        	FILE_LOG(logINFO) << "Thread # " << tn << " preparing lines " << tn*linesPerThread << " to " << (tn+1)*linesPerThread-1;

        	// this copies data to the thread, need to change this in next version
            for(int lineNumber=tn*linesPerThread; lineNumber < (tn+1)*linesPerThread && lineNumber < lineCounter; ++lineNumber ){
            	wcs[tn].incomingData.push_back(allTheData[lineNumber]);
            }
            FILE_LOG(logINFO) << "Thread # " << tn << " starting" << endl;
            allThreads[tn] =  std::thread(std::ref(wcs[tn]));
        }

        for(int tn=0; tn < numberOfThreads; ++tn){
        	allThreads[tn].join();
        }

		FILE_LOG(logINFO) << "Done with work";

		for(auto wc: wcs){
			for(auto dr: wc.outgoingData) out << dr << endl;
			for(auto dr: wc.garbage) garbage << dr << endl;
		}
		FILE_LOG(logINFO) << "Files saved";

	}


	END_TIMER;

	cout << ELAPSED_TIME << endl;

	return 0;
}

