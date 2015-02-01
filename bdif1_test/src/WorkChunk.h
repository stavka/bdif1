/*
 * WorkChunk.h
 *
 *  Created on: Feb 1, 2015
 *      Author: victor
 */

#ifndef WORKCHUNK_H_
#define WORKCHUNK_H_



#include <string>
#include <thread>
#include "DataRecord.h"

using namespace std;

class WorkChunk {
public:

	vector<string> incomingData;
	vector<DataRecord> outgoingData;
	vector<string> garbage;

	WorkChunk();
	virtual ~WorkChunk();

	void operator()();


};

#endif /* WORKCHUNK_H_ */
