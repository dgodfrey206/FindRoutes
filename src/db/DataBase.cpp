/*
 * DataBase.cpp
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa� Prusak
 */


#include "DataBase.h"
#include "lib/DataReader.h"
#include "lib/GTFSReader.h"

DataBase::DataBase() {};

DataBase::DataBase(DataBase::LoadMethod method, std::string p)
{

	if((method == DataBase::LoadMethod::MULTJSON)
			&& p[p.size()-1] != '/')
	{
		this->path = p + "/";
	}
	else
	{
		this->path = p;
	}

	if(method == DataBase::LoadMethod::MULTJSON) this->loadJSON();
	else if(method == DataBase::LoadMethod::GTFS) this->loadGTFS();
	else if(method == DataBase::LoadMethod::JSON) this->loadOneJSON();
	else if(method == DataBase::LoadMethod::SAVEDDB) this->loadSavedDB(p);
	else return;

	if(method != DataBase::LoadMethod::SAVEDDB) this->createTimeTable();

	this->validate();
}

void DataBase::loadGTFS() {

	GTFSReader reader;
	reader.readGTFS(this->path);

	this->routes = reader.getRoutes();
	this->stops = reader.getStops();
	this->trips = reader.getTrips();
	this->stopTimes = reader.getStopTimes();
	this->services = reader.getServices();

}

void DataBase::loadJSON() {

	const std::string routesFile = this->path + "routes.json";
	const std::string tripsFile = this->path + "trips.json";
	const std::string stopsFile = this->path + "stops.json";
	const std::string stopTimesFile = this->path + "stop_times.json";
	const std::string servicesFile = this->path + "services.json";

	this->routes = DataReader::readRoutes(routesFile, false);
	this->trips = DataReader::readTrips(tripsFile, false);
	this->stops = DataReader::readStops(stopsFile, false);
	this->stopTimes = DataReader::readStopTimes(stopTimesFile, false);
	this->services = DataReader::readServices(servicesFile, false);
}

void DataBase::loadOneJSON() {

	std::string file = this->path;

	this->routes = DataReader::readRoutes(file, true);
	this->trips = DataReader::readTrips(file, true);
	this->stops = DataReader::readStops(file, true);
	this->stopTimes = DataReader::readStopTimes(file, true);
	this->services = DataReader::readServices(file, true);
}

void DataBase::createTimeTable() {

	std::cerr << "DB: creating time table" << std::endl;
	unsigned totalTrips = this->trips.size();
	unsigned tripID;


	for(TripData trip: this->trips)
	{

		tripID = trip.getId();
		std::cerr << "DB:  Trip\t" << (tripID + 1) << " out of " << totalTrips;
		std::cerr << " (" << 100 * double(tripID + 1) / totalTrips << "%)" << std::endl;

		std::vector<std::vector<Time>> _stops_in_sec;

		for(unsigned stopID: trip.getStopSec())
		{
			std::vector<Time> _times;

			for(StopTimeData stopTime: this->stopTimes)
			{
				if(stopTime.getStopId() == stopID && stopTime.getTripId() == tripID)
				{
					_times.push_back(stopTime.getStopTime());
				}
			}

			_stops_in_sec.push_back(_times);
		}
		timeTable.push_back(_stops_in_sec);
	}
}

void DataBase::saveToFile(const std::string p) const {
	std::ofstream ofs(p);
	boost::archive::text_oarchive ar(ofs);
	ar & (*this);
}

void DataBase::loadSavedDB(const std::string p) {
	std::ifstream ifs(p);
	boost::archive::text_iarchive ar(ifs);
	// Load data
	ar & (*this);
}

void DataBase::validate() {

	if(routes.empty()){
		std::cerr<<"routes vector is empty!"<<std::endl;
	}else{
		std::cerr<<"Routes vector is ready, contains " << this->routes.size() << " entries."<<std::endl;
	}

	if(trips.empty()){
		std::cerr<<"trips vector is empty!"<<std::endl;
	}else{
		std::cerr<<"Trips vector is ready, contains " << this->trips.size() << " entries."<<std::endl;
	}

	if(stops.empty()){
		std::cerr<<"stops vector is empty!"<<std::endl;
	}else{
		std::cerr<<"Stops vector is ready, contains " << this->stops.size() << " entries."<<std::endl;
	}

	if(stopTimes.empty()){
		std::cerr<<"stop times vector is empty!"<<std::endl;
	}else{
		std::cerr<<"Stop times vector is ready, contains " << this->stopTimes.size() << " entries."<<std::endl;
	}

	if(services.empty()){
		std::cerr<<"services vector is empty!"<<std::endl;
	}else{
		std::cerr<<"Services vector is ready, contains " << this->services.size() << " entries."<<std::endl;
	}

	//todo recursively validate timetable (vector of vectors of vectors of objects FTW)

}

bool DataBase::isValid()
{
	return (!this->stops.empty() && !this->routes.empty() && !this->trips.empty()
			&& !this->services.empty() && !this->stopTimes.empty() && !this->timeTable.empty());
}


