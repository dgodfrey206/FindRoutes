/*
 * DataBase.cpp
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa³ Prusak
 */


#include "DataBase.h"
#include "lib/DataReader.h"

DataBase::DataBase():routesFile("../db/json/routes.json"), tripsFile("../db/json/trips.json"), stopsFile("../db/json/stops.json"),
					stopTimesFile("../db/json/stop_times.json"), servicesFile("../db/json/services.json") {

	this->routes = DataReader::readRoutes(this->routesFile);
	if(routes.empty()){
		std::cerr<<"routes vector is empty!"<<std::endl;
	}else{
		std::cerr<<"routes vector is ready"<<std::endl;
	}

	this->trips = DataReader::readTrips(this->tripsFile);

	if(trips.empty()){
		std::cerr<<"trips vector is empty!"<<std::endl;
	}else{
		std::cerr<<"trips vector is ready"<<std::endl;
	}

	this->stops = DataReader::readStops(this->stopsFile);

	if(stops.empty()){
		std::cerr<<"stops vector is empty!"<<std::endl;
	}else{
		std::cerr<<"stops vector is ready"<<std::endl;
	}

	this->stopTimes = DataReader::readStopTimes(this->stopTimesFile);

	if(stopTimes.empty()){
		std::cerr<<"stop times vector is empty!"<<std::endl;
	}else{
		std::cerr<<"stop times vector is ready"<<std::endl;
	}

	this->services = DataReader::readServices(this->servicesFile);

	if(services.empty()){
		std::cerr<<"services vector is empty!"<<std::endl;
	}else{
		std::cerr<<"services vector is ready"<<std::endl;
	}

}

DataBase::~DataBase(){

}

