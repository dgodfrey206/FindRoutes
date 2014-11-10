/*
 * StopData.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#include "StopData.h"

StopData::StopData(){
	this->name = "pusty wpis";
	this->id   =  0;
	this->lat  =  0;
	this->lng  =  0;
}

StopData::StopData(const StopData& src){
	this->name = src.name;
	this->id   = src.id;
	this->lat  = src.lat;
	this->lng  = src.lng;
}

StopData::StopData(std::string name,unsigned int id,double lat,double lng){
	this->name = name;
	this->id   = id;
	this->lat  = lat;
	this->lng  = lng;
}

StopData::~StopData(){

}

StopData StopData::operator=(const StopData src){
	if(this == & src){
		return *this;
	}else{
		this->name = src.name;
		this->id   = src.id;
		this->lat  = src.lat;
		this->lng  = src.lng;
		return *this;
	}
}

std::ostream& operator<<(std::ostream& output, const StopData& src){
	output<<"name="<<src.getName()<<" id="<<src.getId()<<" lat="<<src.getLat()<<" lng="<<src.getLng()<<std::endl;
	return output;
}


bool StopData::operator==(const StopData src){
	if(this->id !=  src.id){
		return false;
	}else if(this->name != src.name){
		return false;
	}else{
		return true;
	}
}

std::string StopData::getName() const{
	return this->name;
}

unsigned int StopData::getId() const{
	return this->id;
}

double StopData::getLat() const{
	return this->lat;
}

double StopData::getLng() const{
	return this->lng;
}


