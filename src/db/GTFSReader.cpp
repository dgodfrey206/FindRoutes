/*
 * GTFSReader.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Wojtek Gumuła
 */

#include "GTFSReader.h"

Network* GTFSReader::readGTFS(std::string filename) {

	std::cout << "readGTFS called. Filename " << filename << std::endl;
	//open zip archive
	int error = 0;
	char errorBuffer[100];
	struct zip * z = zip_open(filename.c_str(), 0, &error); //-lzip for g++ linked is needed!

	if(error != ZIP_ER_OK)
	{
		std::cout << "Err value: " << error << std::endl;
		zip_error_to_str(errorBuffer, 100, 0, error);
		std::cout << "Err msg: " << errorBuffer << std::endl;
		return NULL;
	}

	//load stops:
	this->loadStops(z);
	this->loadRoutes(z);
	this->loadTrips(z);

	return NULL;
}

void GTFSReader::loadStops(struct zip* z) {
	std::cout << "loadStops called." << std::endl;
	if(z == NULL)
	{
		std::cout << "Got empty pointer as argument, return." << std::endl;
		return;
	}

	zip_file * f;
	struct zip_stat st;

	zip_stat_init(&st);
	zip_stat(z, "stops.txt", 0, &st);

	char * c = new char[st.size];

	f = zip_fopen(z, "stops.txt", 0);
	zip_fread(f, c, st.size);
	zip_fclose(f);

	std::string contents(c, st.size);
	std::vector<std::string> stops = GTFSReader::splitStrings(contents, '\n');

	for(std::string s: stops)
	{
		unsigned int id =0;
		std::vector<std::string> stopData = GTFSReader::splitStrings(s, ',');
//		for(std::string d: stopData) std::cout << id++ << ". " << d << std::endl; //todo debug

		//create RouteData object and populate it
		try
		{
			this->stops.push_back(new StopData(stopData[2], id, std::stod(stopData[4]), std::stod(stopData[5])));
			this->stopIDsTranslate.insert(std::pair<std::string, unsigned int>(stopData[0], id++));
		}
		catch(std::invalid_argument & e)
		{
			continue;//first line, skip
		}
	}
}

void GTFSReader::loadRoutes(struct zip* z) {
	std::cout << "loadRoutes called." << std::endl;
	if(z == NULL)
	{
		std::cout << "Got empty pointer as argument, return." << std::endl;
		return;
	}

	zip_file * f;
	struct zip_stat st;

	zip_stat_init(&st);
	zip_stat(z, "routes.txt", 0, &st);

	char * c = new char[st.size];

	f = zip_fopen(z, "routes.txt", 0);
	zip_fread(f, c, st.size);
	zip_fclose(f);

	std::string contents(c, st.size);
	std::vector<std::string> routes = GTFSReader::splitStrings(contents, '\n');

	for(std::string r: routes)
	{
		std::vector<std::string> routeData = GTFSReader::splitStrings(r, ',');

//		int id = 0;
//		for(std::string d: routeData) std::cout << id++ << ". " << d << std::endl; //todo debug
		//create RouteData object and populate it
		try
		{
			this->routes.push_back(new RouteData(routeData[3], std::stoi(routeData[0])));
		}
		catch(std::invalid_argument & e)
		{
			continue;//first line, skip
		}
	}
}

void GTFSReader::loadTrips(struct zip* z) {
	std::cout << "loadTrips called." << std::endl;
	if(z == NULL)
	{
		std::cout << "Got empty pointer as argument, return." << std::endl;
		return;
	}

	zip_file * f;
	struct zip_stat st;

	zip_stat_init(&st);
	zip_stat(z, "trips.txt", 0, &st);

	char * c = new char[st.size];

	f = zip_fopen(z, "trips.txt", 0);
	zip_fread(f, c, st.size);
	zip_fclose(f);

	std::string contents(c, st.size);
	std::vector<std::string> trips = GTFSReader::splitStrings(contents, '\n');

	unsigned int id = 0;

	for(std::string t: trips)
	{
		std::vector<std::string> tripData = GTFSReader::splitStrings(t, ',');
		int i = 0;
		for(std::string d: tripData) std::cout << i++ << ". " << d << std::endl; //todo debug
		//create TripData object and populate it
		try
		{
			this->trips.push_back(new TripData(id, stoi(tripData[0]), tripData[2], std::vector<int>()));
			this->tripIDsTranslate.insert(std::pair<std::string, unsigned int>(tripData[2], id++));
		}
		catch(std::invalid_argument & e)
		{
			continue;//first line, skip
		}
	}
}

std::vector<std::string> GTFSReader::splitStrings(const std::string &s, char delim) {
	/*
	 * source: https://stackoverflow.com/questions/236129/split-a-string-in-c/236803#236803
	 */

    std::vector<std::string> elems;
    std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
    return elems;
}

std::ostream & operator << (std::ostream & stream, const GTFSReader & reader)
{
	for(StopData * s: reader.stops)
	{
		stream << *s << std::endl;
	}
	for(RouteData * s: reader.routes)
	{
		stream << *s << std::endl;
	}
	for(TripData * s: reader.trips)
	{
		stream << *s << std::endl;
	}

	return stream;
}

