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

//		//copies the string parts, can be improved
	vector<string> tokens(3);
	split(tokens, inputString, is_any_of(","));
//		tokens[0]="20140804:10:00:13.491268";
//		tokens[1]="10.5";
//		tokens[2]="1234";


//		timestamp = posix_time::ptime();
//		price = 0;
//		volume = 0;

    timestamp = posix_time::ptime(  gregorian::date(gregorian::from_undelimited_string("20140804"))
    		                       ,posix_time::time_duration( posix_time::duration_from_string("10:00:13.491268") )
    		                    );

//        timestamp = posix_time::ptime(  gregorian::date(gregorian::from_undelimited_string(tokens[0].substr(0,8)))
//        		                       ,posix_time::time_duration( posix_time::duration_from_string(tokens[0].substr(9,15)) )
//        		                    );
    price = stod(tokens[1]);
    volume = std::stoi(tokens[2]);

}

DataRecord::~DataRecord() {
	// TODO Auto-generated destructor stub
}

ostream& operator<<(ostream& out, const DataRecord& x) {
  //string test3 = boost::posix_time::to_iso_extended_string(x.timestamp);
  out << x .timestamp << " X " << x.price << " X " << x.volume ;
  return out;
}

