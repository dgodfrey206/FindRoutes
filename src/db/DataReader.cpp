/*
 * DataReader.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#include "DataReader.h"

#include "../jsoncpp/json/json.h"

#include <fstream>
#include <iostream>
#include <cstdlib> 	//dla konwersji lat i lng na liczby

std::vector<RouteData> DataReader::readRoutes(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<RouteData> result;
	result.clear();
	if(!file.is_open()){
		std::cout<<"Otwarcie pliku "<<filename<<" nie powiod³o sie!"<<std::endl;
		return result;
	}else{
		std::cout<<"Otwarto poprawnie plik "<<filename<<std::endl;

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
		return result;
	}
}

std::vector<StopData> DataReader::readStops(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<StopData> result;
	//result.clear();
	if(!file.is_open()){
		std::cout<<"Otwarcie pliku "<<filename<<" nie powiod³o sie!"<<std::endl;
		return result;
	}else{
		std::cout<<"Otwarto poprawnie plik "<<filename<<std::endl;
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

		return result;
	}
}

std::vector<TripData> DataReader::readTrips(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<TripData> result;

	if(!file.is_open()){
		std::cout<<"Otwarcie pliku "<<filename<<" nie powiod³o sie!"<<std::endl;
		return result;
	}else{
		std::cout<<"Otwarto poprawnie plik "<<filename<<std::endl;
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
				for(unsigned int j=0; j<stop_sec.size(); j++){
					stops.push_back(stop_sec[j].asInt());
				}
				TripData tmp(trips[i]["id"].asInt(), trips[i]["route_id"].asInt(),trips[i]["name"].asString() ,stops);
				result.push_back(tmp);
			}
		}
	}

	return result;
}

std::vector<StopTimeData> DataReader::readStopTimes(std::string filename){
	std::ifstream file(filename.c_str(),std::ios::in);
	std::vector<StopTimeData> result;

	if(!file.is_open()){
		std::cout<<"Otwarcie pliku "<<filename<<" nie powiod³o sie!"<<std::endl;
		return result;
	}else{
		std::cout<<"Otwarto poprawnie plik "<<filename<<std::endl;
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
				/*
				std::cout<<stopTimes[i]["stop_id"].asUInt()<<std::endl;
				std::cout<<temp;*/
				//StopTimeData temp(stopTimes[i]["id"].asUInt(),0,0,0,stopTimes[i]["name"].asString());
				result.push_back(temp);
			}
		}
	}
	return result;
}

