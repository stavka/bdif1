/*
 * DataRecord.cpp
 *
 *  Created on: Jan 31, 2015
 *      Author: victor
 */

#include "DataRecord.h"

using namespace std;
using namespace boost;

DataRecord::DataRecord(const string &inputString){
    //parse and check
	vector<string> tokens(3);
	split(tokens, inputString, is_any_of(","));

    timestamp = posix_time::ptime(  gregorian::date(gregorian::from_undelimited_string(tokens[0].substr(0,8)))
        		                       ,posix_time::time_duration( posix_time::duration_from_string(tokens[0].substr(9,15)) )
        		                    );
    price = stod(tokens[1]);
    if(price < 0) throw std::range_error("negative price");

    volume = std::stoi(tokens[2]);
    if(volume < 0) throw std::range_error("negative volume");

}

DataRecord::~DataRecord() {
	// TODO Auto-generated destructor stub
}

bool DataRecord::operator< (const DataRecord& other) const {
        return timestamp < other.timestamp;
}

ostream& operator<<(ostream& out, const DataRecord& x) {
  out << posix_time::to_iso_extended_string(x.timestamp) << "," << x.price << "," << x.volume ;
  return out;
}




