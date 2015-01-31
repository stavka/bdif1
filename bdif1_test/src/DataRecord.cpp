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
    volume = std::stoi(tokens[2]);

}

DataRecord::~DataRecord() {
	// TODO Auto-generated destructor stub
}

ostream& operator<<(ostream& out, const DataRecord& x) {
  //string test3 = boost::posix_time::to_iso_extended_string(x.timestamp);
  out << posix_time::to_iso_extended_string(x.timestamp) << " X " << x.price << " X " << x.volume ;
  return out;
}

