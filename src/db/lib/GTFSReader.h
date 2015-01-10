/*
 * GTFSReader.h
 *
 *  Created on: 9 Oct 2014
 *      Author: David Godfrey
 */

#ifndef SRC_DB_GTFSREADER_H_
#define SRC_DB_GTFSREADER_H_

#include <zip.h>
#include <zlib.h>

#include <iostream> //debug
#include <vector>
#include <map>

#include <string>
#include <sstream>

#include <exception>


#include "./StopData.h"
#include "./RouteData.h"
#include "./TripData.h"
#include "StopTimeData.h"
#include "ServiceData.h"

/**
 * GTFSReader reads data from GTFS format zip archive. It is compatible with
 * DataReader class.
 */
class GTFSReader {
public:

	/**
	 * Unpacks gtfs archive, creates network, deletes created in progress files.
	 * @param filename Path to gtfs file.
	 */
	void readGTFS(std::string filename);

	/**
	 * @return vector containing RouteData.
	 */
	std::vector<RouteData>    getRoutes();

	/**
	 * @return vector containing StopData.
	 */
	std::vector<StopData>     getStops();

	/**
	 * @return vector containing TripData.
	 */
	std::vector<TripData>     getTrips();

	/**
	 * @return vector containing StopTimeData.
	 */
	std::vector<StopTimeData> getStopTimes();

	/**
	 * @return vector containing ServiceData.
	 */
	std::vector<ServiceData>  getServices();

	/**
	 * Helper output function.
	 * @param stream Stream
	 * @param reader Outputed object.
	 * @return Reference to given stream.
	 */
	friend std::ostream & operator << (std::ostream & stream, const GTFSReader & reader);
private:
	void loadStops(struct zip * z);
	void loadRoutes(struct zip * z);
	void loadTrips(struct zip * z);
	void loadServices(struct zip * z);
	void loadStopTimes(struct zip * z);


	static std::vector<std::string> splitStrings(const std::string &s, char delim);

	std::vector<StopData> stops;
	std::vector<RouteData> routes;
	std::vector<TripData> trips;
	std::vector<StopTimeData> stopTimes;
	std::vector<ServiceData> services;

	std::map<std::string, unsigned int> stopIDsTranslate;//in gtfs ids are std::string, in database - unsigned int;
	std::map<std::string, unsigned int> tripIDsTranslate;//in gtfs ids are std::string, in database - unsigned int;
	std::map<std::string, unsigned int> serviceIDsTranslate;

};

#endif /* SRC_DB_GTFSREADER_H_ */
