/*
 * TripData.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */


#include "TripData.h"

TripData::TripData(){
	this->id = 0;
	this->routeId = 0;
}

TripData::TripData(const TripData& src){
	this->id = src.id;
	this->routeId = src.routeId;
	this->stopSec = src.stopSec;
}

TripData::TripData(unsigned int id, unsigned int routeId, std::vector<int> stopSec){
	this->id = id;
	this->routeId = routeId;
	this->stopSec = stopSec;
}

TripData::~TripData(){

}

TripData TripData::operator=(const TripData src){
	if(this == &src){
		return *this;
	}else{
		this->id = src.id;
		this->routeId = src.routeId;
		this->stopSec.clear();
		this->stopSec = src.stopSec;
		return *this;
	}
}

std::ostream& operator<<(std::ostream& output, const TripData& src){
	output<<"id="<<src.id<<" routeId="<<src.routeId<<" stops:";
	for(unsigned int i=0;i<src.stopSec.size();i++){
		output<<src.stopSec[i]<<"->";
	}
	output<<std::endl;
	return output;
}

bool TripData::operator==(const TripData src){
	if( (this->id == src.id) && (this->routeId == src.routeId) ){
		return true;
	}else{
		return false;
	}
}

unsigned int TripData::getId() const{
	return this->id;
}

unsigned int TripData::getRouteId() const{
	return this->routeId;
}
std::vector<int> TripData::getStopSec() const{
	return this->stopSec;
}
