/*
 * DataReader.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_LIB_DATAREADER_H_
#define DB_LIB_DATAREADER_H_

#include <string>
#include <vector>

#include "RouteData.h"
#include "StopData.h"
#include "TripData.h"
#include "StopTimeData.h"
#include "ServiceData.h"

class DataReader{
	public:
		static std::vector<RouteData>    readRoutes(std::string filename, bool oneFile = true); // if oneFile is set, functions assume that whole
		static std::vector<StopData>     readStops(std::string filename, bool oneFile = true);	// database is contained in given file.
		static std::vector<TripData>     readTrips(std::string filename, bool oneFile = true);	// otherwise, assume given file contains only neccesary data
		static std::vector<StopTimeData> readStopTimes(std::string filename, bool oneFile = true);	// and so std::vector sth = root; (no root['sth'] is needed.)
		static std::vector<ServiceData>  readServices(std::string filename, bool oneFile = true);
};


#endif /* DB_LIB_DATAREADER_H_ */
