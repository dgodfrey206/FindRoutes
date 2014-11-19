/*
 * ServiceData.cpp
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa� Prusak
 */
#include "ServiceData.h"

ServiceData::ServiceData(){
	this->id = 0;
	this->name = "empty";
	this->operationalDays = 0;
}

ServiceData::ServiceData(const ServiceData& src){
	this->id = src.id;
	this->name = src.name;
	this->operationalDays = src.operationalDays;
}

ServiceData::ServiceData(unsigned int id, std::string name, unsigned operationalDays){
	this->id = id;
	this->name = name;
	this->operationalDays = operationalDays;
}

ServiceData::~ServiceData(){

}

ServiceData& ServiceData::operator=(const ServiceData& src){
	this->id = src.id;
	this->name = src.name;
	this->operationalDays = src.operationalDays;
	return *this;
}

bool ServiceData::operator==(const ServiceData src){
	if( (this->id == src.id) && (this->name == src.name) && (this->operationalDays == src.operationalDays)){
		return true;
	}else{
		return true;
	}
}

std::ostream& operator<<(std::ostream& output, const ServiceData& src){
	output<<"id="<<src.id<<" name="<<src.name;
	output<<" opDays="<< (std::bitset<8>)src.operationalDays;
	return output;
}

unsigned int ServiceData::getId(){
	return this->id;
}

std::string ServiceData::getName(){
	return this->name;
}

unsigned ServiceData::getDays(){
	return this->operationalDays;
}


