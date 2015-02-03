/*
 * WorkChunk.cpp
 *
 *  Created on: Feb 1, 2015
 *      Author: victor
 */

#include "WorkChunk.h"
#include "Log.h"


WorkChunk::WorkChunk() {
	// TODO Auto-generated constructor stub

}

WorkChunk::~WorkChunk() {
	// TODO Auto-generated destructor stub
}

void WorkChunk::operator()(){

	    FILE_LOG(logINFO) << "Starting work " << std::this_thread::get_id();

		int lineCounter = 0;
		for(auto line : incomingData){
            ++ lineCounter;
            if(lineCounter%100==0){
            	FILE_LOG(logDEBUG) << std::this_thread::get_id() << " Line processed: " << lineCounter;
            }
			try{
				DataRecord dr(line);
				outgoingData.push_back(dr);
			}
			catch(boost::exception &e){
				garbage.push_back(line);
			}
			catch(std::exception &e){
				garbage.push_back(line);
			}
		}
	}

