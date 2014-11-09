/*
 * GTFSReader.h
 *
 *  Created on: 9 lis 2014
 *      Author: Wojtek Gumuła
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

#include "../graph/Network.h"

#include "StopData.h"
#include "RouteData.h"
#include "TripData.h"

class GTFSReader {
public:

	/**
	 * Unpacks gtfs archive, creates network, deletes created in progress files.
	 * @param filename Path to gtfs file.
	 * @return Pointer to created Network.
	 */
	Network * readGTFS(std::string filename);

	friend std::ostream & operator << (std::ostream & stream, const GTFSReader & reader);
private:
	void loadStops(struct zip * z);
	void loadRoutes(struct zip * z);
	void loadTrips(struct zip * z);

	static std::vector<std::string> splitStrings(const std::string &s, char delim);

	std::vector<StopData *> stops;
	std::vector<RouteData *> routes;
	std::vector<TripData *> trips;

	std::map<std::string, unsigned int> stopIDsTranslate;//in gtfs ids are std::string, in database - unsigned int;
	std::map<std::string, unsigned int> tripIDsTranslate;//in gtfs ids are std::string, in database - unsigned int;
};

#endif /* SRC_DB_GTFSREADER_H_ */
