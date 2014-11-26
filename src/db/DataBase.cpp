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

	//repair for no times for last stops
	for(unsigned int tripId=0; tripId<this->timeTable.size(); tripId++){
		for(unsigned int stopInSec=0; stopInSec<this->timeTable[tripId].size(); stopInSec++){
			if(this->timeTable[tripId][stopInSec].empty()){
				Time delta = this->timeTable[tripId][stopInSec-1][0] - this->timeTable[tripId][stopInSec-2][0];
				for(unsigned int j=0; j<this->timeTable[tripId][stopInSec-1].size();j++){
					this->timeTable[tripId][stopInSec].push_back(this->timeTable[tripId][stopInSec-1][j] + delta);
				}
			}
		}
	}

}

void DataBase::loadSavedDB(const std::string p) {
	std::ifstream ifs(p);
	Json::Reader reader;
	Json::Value root;

	if(!reader.parse(ifs, root)) return;

	Json::Value routes = root["routes"];
	Json::Value stops = root["stops"];
	Json::Value trips = root["trips"];
	Json::Value stopTimes = root["stop_times"];
	Json::Value services = root["services"];
	Json::Value timetable = root["time_table"];

	for(auto val: routes)
	{
		this->routes.push_back(RouteData(
			val["name"].asString(),
			val["id"].asInt()
			)
		);
	}

	for(auto val: trips)
	{
		std::vector<int> sec;
		for(auto i: val["stop_sec"])
		{
			sec.push_back(i.asInt());
		}
		this->trips.push_back(TripData(
			val["id"].asInt(),
			val["route"].asInt(),
			val["name"].asString(),
			sec
			)
		);
	}
	for(auto val: stops)
	{
		this->stops.push_back(StopData(
			val["name"].asString(),
			val["id"].asInt(),
			val["lat"].asDouble(),
			val["lng"].asDouble()
			)
		);
	}

	for(auto val: stopTimes)
	{
		this->stopTimes.push_back(StopTimeData(
			val["id"].asInt(),
			val["stop"].asInt(),
			val["service"].asInt(),
			val["trip"].asInt(),
			val["name"].asString()
			)
		);
	}

	for(auto val: services)
	{
		this->services.push_back(ServiceData(
			val["id"].asInt(),
			val["name"].asString(),
			val["days"].asInt()
			)
		);
	}

	//std::vector<std::vector<std::vector<Time>>> timeTable;
	for(auto val: timetable)
	{
		std::vector<std::vector<Time>> vec;
		for(auto val2: val)
		{
			std::vector<Time> vec2;
			for(auto val3: val2)
			{
				vec2.push_back(Time(
					val3.asInt()
					)
				);
			}
			vec.push_back(vec2);
		}
		this->timeTable.push_back(vec);
	}
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

void DataBase::saveToFile(const std::string filename) const{

	Json::StyledStreamWriter writer;
	Json::Value root;

	for(RouteData r: this->routes)
	{
		Json::Value v;
		v["id"] = r.getId();
		v["name"] = r.getName();
		root["routes"].append(v);
	}

	for(TripData t: this->trips)
	{
		Json::Value v;
		v["id"] = t.getId();
		v["name"] = t.getName();
		v["route"] = t.getRouteId();

		auto stops = t.getStopSec();
		for(auto s: t.getStopSec())
		{
			Json::Value stop(s);
			v["stop_sec"].append(stop);
		}
		root["trips"].append(v);
	}

	for(StopData s: this->stops)
	{
		Json::Value v;
		v["id"] = s.getId();
		v["name"] = s.getName();
		v["lat"] = s.getLat();
		v["lng"] = s.getLng();

		root["stops"].append(v);
	}

	for(StopTimeData s: this->stopTimes)
	{
		Json::Value v;
		v["id"] = s.getId();
		v["name"] = s.getName();
		v["service"] = s.getServiceId();
		v["stop"] = s.getStopId();
		v["trip"] = s.getTripId();
		v["stoptime"] = int(s.getStopTime());

		root["stop_times"].append(v);
	}

	for(ServiceData s: this->services)
	{
		Json::Value v;
		v["id"] = s.getId();
		v["name"] = s.getName();
		v["days"] = s.getDays();

		root["services"].append(v);
	}

	for(auto t1: this->timeTable) //std::vector<std::vector<Time>>
	{
		Json::Value v;
		for(auto t2: t1) //std::vector<Time>
		{
			Json::Value v2;
			for(Time t: t2)
			{
				v2.append(int(t));
			}
			v.append(v2);
		}
		root["time_table"].append(v);
	}

	std::ofstream file(filename.c_str(), std::ios::out);

	writer.write(file, root);


}

