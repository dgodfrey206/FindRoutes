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

#include "../graph/Network.h"

#include "StopData.h"

class GTFSReader {
public:
	GTFSReader();
	~GTFSReader();

	/**
	 * Unpacks gtfs archive, creates network, deletes created in progress files.
	 * @param filename Path to gtfs file.
	 * @return Pointer to created Network.
	 */
	Network * readGTFS(std::string filename);

private:
	static std::vector<std::string> splitStrings(const std::string &s, char delim);

	void loadStops(struct zip * z, Network * n);

	std::vector<StopData *> stops;

	std::map<std::string, unsigned int> stopIDsTranslate;//in gtfs ids are std::string, in database - unsigned int;
};

#endif /* SRC_DB_GTFSREADER_H_ */
