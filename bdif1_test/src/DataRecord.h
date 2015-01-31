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

class DataRecord {
public:
	boost::posix_time::ptime timestamp;
	double price;
	int volume;
	DataRecord(const std::string &inputString);
	virtual ~DataRecord();
};

#endif /* DATARECORD_H_ */
