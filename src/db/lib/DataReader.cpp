/*
 * DataReader.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#include "DataReader.h"
#include "../../jsoncpp/json/json.h"

#include <fstream>
#include <iostream>
#include <cstdlib> 	//dla konwersji lat i lng na liczby

std::vector<RouteData> DataReader::readRoutes(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<RouteData> result;
	result.clear();
	if(!file.is_open()){
		std::cerr<<"Could not open file: "<<filename<<std::endl;
		return result;
	}else{
		std::cerr<<"File "<<filename<<" is now opened"<<std::endl;

		Json::Reader parser;
		Json::Value root;

		if( !parser.parse(file,root) ){
			std::cout<<parser.getFormatedErrorMessages()<<std::endl;
			return result;
		}else{
			Json::Value routes = root["routes"];
			for(unsigned int i=0; i<routes.size();i++){
				RouteData temp(routes[i]["name"].asString(), routes[i]["id"].asInt());
				result.push_back(temp);
			}
		}
		file.close();
		std::cerr<<"File "<<filename<<"file is closed"<<std::endl;
		return result;
	}
}

std::vector<StopData> DataReader::readStops(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<StopData> result;
	//result.clear();
	if(!file.is_open()){
		std::cerr<<"Could not open file: "<<filename<<std::endl;
		return result;
	}else{
		std::cerr<<"File "<<filename<<" is now opened"<<std::endl;
		Json::Reader parser;
		Json::Value root;

		if( !parser.parse(file,root) ){
			std::cout<<parser.getFormatedErrorMessages()<<std::endl;
			return result;
		}else{
			Json::Value stops = root["stops"];
			for(unsigned int i=0; i<stops.size();i++){
				StopData temp(stops[i]["name"].asString(), stops[i]["id"].asUInt(), atof(stops[i]["lat"].asString().c_str()), atof(stops[i]["lng"].asString().c_str()));
				result.push_back(temp);
			}
		}
		file.close();
		std::cerr<<"File "<<filename<<"file is closed"<<std::endl;
		return result;
	}
}

std::vector<TripData> DataReader::readTrips(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<TripData> result;

	if(!file.is_open()){
		std::cerr<<"Could not open file: "<<filename<<std::endl;
		return result;
	}else{
		std::cerr<<"File "<<filename<<" is now opened"<<std::endl;
		Json::Reader parser;
		Json::Value root;

		if( !parser.parse(file,root) ){
			std::cout<<parser.getFormatedErrorMessages()<<std::endl;
			return result;
		}else{
			Json::Value trips = root["trips"];
			for(unsigned int i=0; i<trips.size();i++){
				std::vector<int> stops;
				Json::Value stop_sec = trips[i]["stop_sec"];
				unsigned int j = 0;
				stops.push_back(stop_sec[j].asInt());
				for(j =1; j<stop_sec.size(); j++){
					if(stop_sec[j].asInt() != stop_sec[j-1].asInt()){
						stops.push_back(stop_sec[j].asInt());
					}
				}
				/*
				if(stop_sec[0].asUInt() == stop_sec[1].asUInt()){
					j=1;
				}else{
					j=0;
				}*/


				TripData tmp(trips[i]["id"].asInt(), trips[i]["route_id"].asInt(),trips[i]["name"].asString() ,stops);
				result.push_back(tmp);
			}
		}
		file.close();
		std::cerr<<"File "<<filename<<"file is closed"<<std::endl;
		return result;
	}

}

std::vector<StopTimeData> DataReader::readStopTimes(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<StopTimeData> result;

	if(!file.is_open()){
		std::cerr<<"Could not open file: "<<filename<<std::endl;
		return result;
	}else{
		std::cerr<<"File "<<filename<<" is now opened"<<std::endl;
		Json::Reader parser;
		Json::Value root;
		if( !parser.parse(file,root) ){
			std::cout<<parser.getFormatedErrorMessages()<<std::endl;
			return result;
		}else{
			Json::Value stopTimes = root["stop_times"];
			for(unsigned int i=0; i<stopTimes.size();i++){

				StopTimeData temp(stopTimes[i]["id"].asInt(), stopTimes[i]["stop_id"].asUInt(),
								  stopTimes[i]["service_id"].asUInt(), stopTimes[i]["trip_id"].asUInt(),
								  stopTimes[i]["name"].asString());
				result.push_back(temp);
			}
		}
		file.close();
		std::cerr<<"File "<<filename<<"file is closed"<<std::endl;
		return result;
	}

}

std::vector<ServiceData> DataReader::readServices(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<ServiceData> result;

		if(!file.is_open()){
			std::cerr<<"Could not open file: "<<filename<<std::endl;
			return result;
		}else{
			std::cerr<<"File "<<filename<<" is now opened"<<std::endl;
			Json::Reader parser;
			Json::Value root;
			if( !parser.parse(file,root) ){
				std::cout<<parser.getFormatedErrorMessages()<<std::endl;
				return result;
			}else{
				Json::Value services = root["services"];
				for(unsigned int i=0; i<services.size();i++){
					ServiceData temp(services[i]["id"].asUInt(), services[i]["name"].asString());
					result.push_back(temp);
				}
			}
			file.close();
			std::cerr<<"File "<<filename<<"file is closed"<<std::endl;
			return result;
		}

}
