/*
 * DataBase.cpp
 *
 *  Created on: 10 lis 2014
 *      Author: Rafaï¿½ Prusak
 */


#include "DataBase.h"
#include "lib/DataReader.h"
#include "lib/GTFSReader.h"


DataBase::DataBase(DataBase::LoadMethod method, std::string path)
	:
	path(path)
{
	if(method == DataBase::LoadMethod::JSON) this->loadJSON();
	else if(method == DataBase::LoadMethod::GTFS) this->loadGTFS();
	else return;
}

void DataBase::loadGTFS() {
	return;
}

void DataBase::loadJSON() {

	const std::string routesFile = this->path + "/" + "routes.json";
	const std::string tripsFile = this->path + "/" + "trips.json";
	const std::string stopsFile = this->path + "/" + "stops.json";
	const std::string stopTimesFile = this->path + "/" + "stop_times.json";
	const std::string servicesFile = this->path + "/" + "services.json";

	this->routes = DataReader::readRoutes(routesFile);
	if(routes.empty()){
		std::cerr<<"routes vector is empty!"<<std::endl;
	}else{
		std::cerr<<"routes vector is ready"<<std::endl;
	}

	this->trips = DataReader::readTrips(tripsFile);

	if(trips.empty()){
		std::cerr<<"trips vector is empty!"<<std::endl;
	}else{
		std::cerr<<"trips vector is ready"<<std::endl;
	}

	this->stops = DataReader::readStops(stopsFile);

	if(stops.empty()){
		std::cerr<<"stops vector is empty!"<<std::endl;
	}else{
		std::cerr<<"stops vector is ready"<<std::endl;
	}

	this->stopTimes = DataReader::readStopTimes(stopTimesFile);

	if(stopTimes.empty()){
		std::cerr<<"stop times vector is empty!"<<std::endl;
	}else{
		std::cerr<<"stop times vector is ready"<<std::endl;
	}

	this->services = DataReader::readServices(servicesFile);

	if(services.empty()){
		std::cerr<<"services vector is empty!"<<std::endl;
	}else{
		std::cerr<<"services vector is ready"<<std::endl;
	}


}


void DataBase::printTimeTable(){
	for(unsigned int trip_id=0; trip_id<this->trips.size(); trip_id++){

		std::cout<<"trasa: "<<this->trips[trip_id].getName()<<std::endl;
		unsigned int route_id = (this->trips[trip_id].getRouteId());
		std::cout<<"linia: "<<this->routes[route_id].getName()<<std::endl;

		if(this->trips[trip_id].getStopSec().size() <= 4){
			std::cerr<<"mo¿liwy blad w trip: "<<trip_id<<std::endl;
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


