/*
 * GTFSReader.cpp
 *
 *  Created on: 9 Oct 2014
 *      Author: David Godfrey
 */

#include "GTFSReader.h"

void GTFSReader::readGTFS(std::string filename) {

	std::cerr << "readGTFS called. Filename " << filename << std::endl;
	//open zip archive
	int error = 0;
	char errorBuffer[100];
	struct zip * z = zip_open(filename.c_str(), 0, &error); //-lzip for g++ linked is needed!

	if(error != ZIP_ER_OK)
	{
		std::cerr << "Err value: " << error << std::endl;
		zip_error_to_str(errorBuffer, 100, 0, error);
		std::cerr << "Err msg: " << errorBuffer << std::endl;
		return;
	}

	//load stops:
	this->loadStops(z);
	this->loadRoutes(z);
	this->loadTrips(z);
	this->loadServices(z);
	this->loadStopTimes(z);

	return;
}

void GTFSReader::loadStops(struct zip* z) {
	std::cerr << "loadStops called." << std::endl;
	if(z == NULL)
	{
		std::cerr << "Got empty pointer as argument, return." << std::endl;
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

	unsigned int id = 0;
	for(std::string s: stops)
	{

		std::vector<std::string> stopData = GTFSReader::splitStrings(s, ',');

		//create RouteData object and populate it
		try
		{
			this->stops.push_back(StopData(stopData[2], id, std::stod(stopData[4]), std::stod(stopData[5])));
			this->stopIDsTranslate.insert(std::pair<std::string, unsigned int>(stopData[0], id++));
		}
		catch(std::invalid_argument & e)
		{
			std::cerr << "exception catched: " << e.what() << std::endl;
			continue;//first line, skip
		}
	}
}

void GTFSReader::loadRoutes(struct zip* z) {
	std::cerr << "loadRoutes called." << std::endl;
	if(z == NULL)
	{
		std::cerr << "Got empty pointer as argument, return." << std::endl;
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

		//create RouteData object and populate it
		try
		{
			this->routes.push_back(RouteData(routeData[3], std::stoi(routeData[0])));
		}
		catch(std::invalid_argument & e)
		{
			continue;//first line, skip
		}
	}
}

void GTFSReader::loadTrips(struct zip* z) {
	std::cerr << "loadTrips called." << std::endl;
	if(z == NULL)
	{
		std::cerr << "Got empty pointer as argument, return." << std::endl;
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

		//create TripData object and populate it
		try
		{
			this->trips.push_back(TripData(id, stoi(tripData[0]), tripData[2], std::vector<int>()));
			this->tripIDsTranslate.insert(std::pair<std::string, unsigned int>(tripData[2], id++));
		}
		catch(std::invalid_argument & e)
		{
			continue;//first line, skip
		}
	}
}

void GTFSReader::loadServices(struct zip* z) {
	std::cerr << "loadServices called." << std::endl;
	if(z == NULL)
	{
		std::cerr << "Got empty pointer as argument, return." << std::endl;
		return;
	}

	zip_file * f;
	struct zip_stat st;

	zip_stat_init(&st);
	zip_stat(z, "calendar.txt", 0, &st);

	char * c = new char[st.size];

	f = zip_fopen(z, "calendar.txt", 0);
	zip_fread(f, c, st.size);
	zip_fclose(f);

	std::string contents(c, st.size);
	std::vector<std::string> services = GTFSReader::splitStrings(contents, '\n');

	unsigned int id = 0;
	for(std::string s: services)
	{
		std::vector<std::string> params = GTFSReader::splitStrings(s, ',');
		//create ServiceData object and populate it
		try
		{
			unsigned operationalDays = 0;
			for(int i = 0; i < 7; i++)
			{
				operationalDays += stoi(params[i + 1]) << i;
			}

			if(operationalDays == 0)
			{
				std::cerr << "Service with no working days, passing.";
				continue;
			}

			this->services.push_back(ServiceData(id, params[0], operationalDays));
			this->serviceIDsTranslate.insert(std::pair<std::string, unsigned>(params[0], id++));
		}
		catch(std::invalid_argument & e)
		{
			continue;//first line, skip
		}
	}
}

void GTFSReader::loadStopTimes(struct zip* z) {
	std::cerr << "loadStopTimes called." << std::endl;
	if(z == NULL)
	{
		std::cerr << "Got empty pointer as argument, return." << std::endl;
		return;
	}

	zip_file * f;
	struct zip_stat st;

	zip_stat_init(&st);
	zip_stat(z, "stop_times.txt", 0, &st);

	char * c = new char[st.size];

	f = zip_fopen(z, "stop_times.txt", 0);
	zip_fread(f, c, st.size);
	zip_fclose(f);

	std::string contents(c, st.size);
	std::vector<std::string> times = GTFSReader::splitStrings(contents, '\n');

	unsigned int id = 0;
	for(std::string s: times)
	{

		std::vector<std::string> timesData = GTFSReader::splitStrings(s, ',');

		//create RouteData object and populate it
		std::cerr << s << std::endl;
		unsigned tripID = this->tripIDsTranslate[timesData[0]];

		/*try
		{
			this->stops.push_back(StopData(stopData[2], id, std::stod(stopData[4]), std::stod(stopData[5])));
			this->stopIDsTranslate.insert(std::pair<std::string, unsigned int>(stopData[0], id++));
		}
		catch(std::invalid_argument & e)
		{
			std::cerr << e.what() << std::endl;
			continue;//first line, skip
		}*/
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
	for(StopData s: reader.stops)
	{
		stream << s << std::endl;
	}
	for(RouteData s: reader.routes)
	{
		stream << s << std::endl;
	}
	for(TripData s: reader.trips)
	{
		stream << s << std::endl;
	}

	return stream;
}

std::vector<RouteData> GTFSReader::getRoutes() {
	return this->routes;
}

std::vector<StopData> GTFSReader::getStops() {
	return this->stops;
}

std::vector<TripData> GTFSReader::getTrips() {
	return this->trips;
}

std::vector<StopTimeData> GTFSReader::getStopTimes() {
	return this->stopTimes;
}

std::vector<ServiceData> GTFSReader::getServices() {
	return this->services;
}
