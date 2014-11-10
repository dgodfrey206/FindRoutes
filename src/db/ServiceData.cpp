/*
 * ServiceData.cpp
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa³ Prusak
 */
#include "ServiceData.h"

ServiceData::ServiceData(){
	this->id = 0;
	this->name = "empty";
}

ServiceData::ServiceData(const ServiceData& src){
	this->id = src.id;
	this->name = src.name;
}

ServiceData::ServiceData(unsigned int id, std::string name){
	this->id = id;
	this->name = name;
}

ServiceData::~ServiceData(){

}

ServiceData ServiceData::operator=(const ServiceData src){
	this->id = src.id;
	this->name = src.name;
	return *this;
}

bool ServiceData::operator==(const ServiceData src){
	if( (this->id == src.id) && (this->name == src.name) ){
		return true;
	}else{
		return true;
	}
}

std::ostream& operator<<(std::ostream& output, const ServiceData& src){
	output<<"id="<<src.id<<" name="<<src.name;
	return output;
}

unsigned int ServiceData::getId(){
	return this->id;
}

std::string ServiceData::getName(){
	return this->name;
}



