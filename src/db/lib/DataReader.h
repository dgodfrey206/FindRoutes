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

/**
 * DataReader reads data from one or multiple json files.
 * If oneFile is set, functions assume that whole database is contained in given file,
 * otherwise, assume given file contains only neccesary data
 * and so std::vector sth = root; (no root['sth'] is needed.)
 */
class DataReader{
public:

	/**
	 * Function loading routes from given file.
	 * @param filename path to file.
	 * @param oneFile Defines if all data is being loaded from oneFile.
	 * @return vector containing RouteData.
	 */
	static std::vector<RouteData>    readRoutes(std::string filename, bool oneFile = true);

	/**
	 * Function loading stops from given file.
	 * @param filename path to file.
	 * @param oneFile Defines if all data is being loaded from oneFile.
	 * @return vector containing StopData.
	 */
	static std::vector<StopData>     readStops(std::string filename, bool oneFile = true);

	/**
	 * Function loading trips from given file.
	 * @param filename path to file.
	 * @param oneFile Defines if all data is being loaded from oneFile.
	 * @return vector containing TripData.
	 */
	static std::vector<TripData>     readTrips(std::string filename, bool oneFile = true);

	/**
	 * Function loading stop times from given file.
	 * @param filename path to file.
	 * @param oneFile Defines if all data is being loaded from oneFile.
	 * @return vector containing StopTimeData.
	 */
	static std::vector<StopTimeData> readStopTimes(std::string filename, bool oneFile = true);

	/**
	 * Function loading services from given file.
	 * @param filename path to file.
	 * @param oneFile Defines if all data is being loaded from oneFile.
	 * @return vector containing ServiceData.
	 */
	static std::vector<ServiceData>  readServices(std::string filename, bool oneFile = true);
};


#endif /* DB_LIB_DATAREADER_H_ */
