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

#define START_TIMER std::chrono::system_clock::time_point t0 = std::chrono::system_clock::now()
#define END_TIMER std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now()
#define ELAPSED_TIME std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count()


using namespace std;

void ThreadFunction(vector<string> &linesToParse, vector<DataRecord> &signalData, vector<DataRecord> &noiseData){
    cout << "Starting thread" << endl;
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

void do_join(std::thread& t)
{
    t.join();
}

int main(void) {

	std::ifstream in("data10k.txt");
	std::ofstream out("signal.txt");
	std::ofstream garbage("noise.txt");

	const int runVersion = 3;

	START_TIMER;

	if(runVersion == 0){
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
			cout << "Boost Exception!" << endl;
			garbage << line;
		}catch(std::exception &e){
			cout << e.what() << '\n';
			garbage << line;
		}
	}
	}else if(runVersion == 1){

		vector<string> allTheData;
        cout << "starting main loop" << endl;


		while (in)
		{
			string line;
	        getline( in, line);
			if(!line.empty()){
				allTheData.push_back(line);
			}
		}
		cout << "Done loading" << endl;

		vector<DataRecord> signalData;
		vector<DataRecord> noiseData;

		std::thread threadOnly;

		threadOnly = std::thread(ThreadFunction, std::ref(allTheData), std::ref(signalData), std::ref(noiseData) );

		threadOnly.join();

		cout << "Done with thread" << endl;

		const time_t ctt = time(0);
		out << "signal generated " << asctime(std::localtime(&ctt)) << endl;
		for(auto x: signalData) out << x << endl;
		for(auto x: noiseData) garbage << x << endl;

	}else if(runVersion == 2){

		const int linesPerChunk = 20000;

		cout << "starting main loop" << endl;

		int lineCounter = 0;
        vector<std::thread> allThreads;
        vector<WorkChunk> wcs;
		while (in)
		{
			string line;
			getline( in, line);
			if(!line.empty()){
				++lineCounter;
				if(lineCounter==1){
					wcs.push_back(WorkChunk());
				}
				wcs.back().incomingData.push_back(line);
				cout << "Line loaded "<< lineCounter << endl;
				if(lineCounter==linesPerChunk){
					cout << "Resetting counter" << endl;
					lineCounter = 0;
					allThreads.push_back(std::thread(std::ref(wcs.back())));
				}

			}
		}
		cout << "Done loading and starting threads" << endl;

		//for(auto t: allThreads) t.join();
		std::for_each(allThreads.begin(),allThreads.end(),do_join);

		cout << "Done with work" << endl;

		const time_t ctt = time(0);
		out << "signal generated " << asctime(std::localtime(&ctt)) << endl;
		for(auto wc: wcs){
			for(auto dr: wc.outgoingData) out << dr << endl;
			for(auto dr: wc.garbage) garbage << dr << endl;
		}

	}else if(runVersion == 3){

		const int numberOfThreads = 4;

		cout << "starting main loop" << endl;

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
		cout << "Done loading" << endl;

        int linesPerThread;
        linesPerThread = lineCounter/numberOfThreads;
        cout << "Lines per thread " << linesPerThread << endl;

        for(int tn=0; tn < numberOfThreads; ++tn){
           // setup work
        	cout << "Thread # " << tn << " preparing" << endl;
        	cout << "Lines " << tn*linesPerThread << " to " << (tn+1)*linesPerThread-1 << endl;
            for(int lineNumber=tn*linesPerThread; lineNumber < (tn+1)*linesPerThread && lineNumber < lineCounter; ++lineNumber ){
            	wcs[tn].incomingData.push_back(allTheData[lineNumber]);
            }
            cout << "Thread # " << tn << " starting" << endl;
            allThreads[tn] =  std::thread(std::ref(wcs[tn]));
        }

        for(int tn=0; tn < numberOfThreads; ++tn){
        	allThreads[tn].join();
            // process results
        }

		cout << "Done with work" << endl;

		const time_t ctt = time(0);
		out << "signal generated " << asctime(std::localtime(&ctt)) << endl;
		for(auto wc: wcs){
			for(auto dr: wc.outgoingData) out << dr << endl;
			for(auto dr: wc.garbage) garbage << dr << endl;
		}

	}


	END_TIMER;

	cout << ELAPSED_TIME << endl;

	return 0;
}

