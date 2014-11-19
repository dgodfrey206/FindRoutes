/*
 * StopTimeData.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */

#include "StopTimeData.h"

#include <cstdlib>

StopTimeData::StopTimeData(){
	this->id = 0;
	this->serviceId = 0;
	this->stopId = 0;
	this->tripId = 0;
}

StopTimeData::StopTimeData(const StopTimeData& src){
	this->id = src.id;
	this->serviceId = src.serviceId;
	this->stopId = src.stopId;
	this->tripId = src.tripId;
	this->name = src.name;
	this->stoptime = src.stoptime;
}

StopTimeData::StopTimeData(unsigned int id, unsigned int stopId, unsigned int serviceId, unsigned int tripId, std::string name){
	this->id = id;
	this->serviceId = serviceId;
	this->stopId = stopId;
	this->tripId = tripId;
	this->name = name;
	this->stoptime = Time(std::atoi(name.substr(0,2).c_str()), std::atoi(name.substr(3,4).c_str()));
}

StopTimeData::~StopTimeData(){

}

StopTimeData& StopTimeData::operator=(const StopTimeData& src){
	if(this == &src){
		return *this;
	}else{
		this->id = src.id;
		this->serviceId = src.serviceId;
		this->stopId = src.stopId;
		this->tripId = src.tripId;
		this->name = src.name;
		this->stoptime = src.stoptime;
		return *this;
	}
}

std::ostream& operator<<(std::ostream& output, const StopTimeData& src){
	output<<"id="<<src.id<<" serviceId="<<src.serviceId<<" stopId="<<src.stopId<<" tripId="<<src.tripId<<" name="<<src.name<<" time="<<src.stoptime<<std::endl;
	return output;
}

bool StopTimeData::operator==(const StopTimeData src){
	if( (this->id == src.id) && (this->serviceId == src.serviceId) && (this->tripId == src.tripId)
		&& (this->stopId == src.stopId) && (this->stoptime == src.stoptime)){
		return true;
	}else{
		return false;
	}
}

unsigned int StopTimeData::getId() const{
	return this->id;
}

unsigned int StopTimeData::getServiceId() const{
	return this->serviceId;
}

unsigned int StopTimeData::getStopId() const{
	return this->stopId;
}

unsigned int StopTimeData::getTripId() const{
	return this->tripId;
}

Time StopTimeData::getStopTime() const{
	return this->stoptime;
}

std::string StopTimeData::getName() const{
	return this->name;
}
