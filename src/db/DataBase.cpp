/*
 * DataBase.cpp
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa� Prusak
 */


#include "DataBase.h"
#include "lib/DataReader.h"
#include "lib/GTFSReader.h"


DataBase::DataBase(DataBase::LoadMethod method, std::string p)
	:
	path(p + ((p.back() == '/') ? "" : "/"))
{
	if(method == DataBase::LoadMethod::MULTJSON) this->loadJSON();
	else if(method == DataBase::LoadMethod::GTFS) this->loadGTFS();
	else if(method == DataBase::LoadMethod::JSON) this->loadOneJSON();
	else return;

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

	this->routes = DataReader::readRoutes(routesFile);
	this->trips = DataReader::readTrips(tripsFile);
	this->stops = DataReader::readStops(stopsFile);
	this->stopTimes = DataReader::readStopTimes(stopTimesFile);
	this->services = DataReader::readServices(servicesFile);
}

void DataBase::loadOneJSON() {

	std::string file = this->path + "db.json";

	this->routes = DataReader::readRoutes(file);
	this->trips = DataReader::readTrips(file);
	this->stops = DataReader::readStops(file);
	this->stopTimes = DataReader::readStopTimes(file);
	this->services = DataReader::readServices(file);
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

}


void DataBase::printTimeTable(){
	for(unsigned int trip_id=0; trip_id<this->trips.size(); trip_id++){

		std::cout<<"trasa: "<<this->trips[trip_id].getName()<<std::endl;
		unsigned int route_id = (this->trips[trip_id].getRouteId());
		std::cout<<"linia: "<<this->routes[route_id].getName()<<std::endl;

		if(this->trips[trip_id].getStopSec().size() <= 4){
			std::cerr<<"mo�liwy blad w trip: "<<trip_id<<std::endl;
		}

		for(unsigned int stop=0; stop<this->trips[trip_id].getStopSec().size();stop++){



			unsigned int stop_id = (this->trips[trip_id].getStopSec()[stop]);
			std::cout<< this->stops[stop_id].getName()<<std::endl;
			for(unsigned int stop_time=0; stop_time< this->stopTimes.size();stop_time++){
				if( (this->stopTimes[stop_time].getServiceId() == 0) 	&&
					(this->stopTimes[stop_time].getStopId() == stop_id) &&
					(this->stopTimes[stop_time].getTripId() == trip_id)){
						std::cout<<this->stopTimes[stop_time].getStopTime()<<" ";
				}
			}


			std::cout<<std::endl;
		}
		std::cout<<std::endl;
	}
}


