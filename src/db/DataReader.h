/*
 * DataReader.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#ifndef DB_DATAREADER_H_
#define DB_DATAREADER_H_

#include <string>
#include <vector>

#include "RouteData.h"
#include "StopData.h"
#include "TripData.h"

class DataReader{
	public:
		static std::vector<RouteData> readRoutes(std::string filename);
		static std::vector<StopData>  readStops(std::string filename);
		static std::vector<TripData>  readTrips(std::string filename);
};


#endif /* DB_DATAREADER_H_ */
