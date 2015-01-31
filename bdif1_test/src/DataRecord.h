/*
 * DataRecord.h
 *
 *  Created on: Jan 31, 2015
 *      Author: victor
 */

#ifndef DATARECORD_H_
#define DATARECORD_H_

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/algorithm/string.hpp"
#include <iostream>

using namespace std;

class DataRecord {

private:
	boost::posix_time::ptime timestamp;
	double price;
	int volume;


public:
	friend ostream& operator<<(ostream& os, const DataRecord& dt);
	DataRecord(const std::string &inputString);
	virtual ~DataRecord();
};



#endif /* DATARECORD_H_ */
