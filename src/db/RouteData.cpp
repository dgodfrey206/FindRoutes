/*
 * RouteData.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#include "../db/RouteData.h"

RouteData::RouteData(){
	this->id = 0;
	this->name = "pusty wpis";
}

RouteData::RouteData(const RouteData& src){
	this->id = src.id;
	this->name = src.name;
}

RouteData::RouteData(std::string name,unsigned int id){
	this->id = id;
	this->name = name;
}

RouteData RouteData::operator=(const RouteData src){
	this->name = src.name;
	this->id = src.id;
	return *this;
}

std::ostream& operator<<(std::ostream& output, const RouteData& src){
	output<<"Nazwa lini: "<<src.getName()<<" -- id="<<src.getId()<<std::endl;
	return output;
}

RouteData::~RouteData(){

}

std::string RouteData::getName() const{
	return this->name;
}

unsigned int RouteData::getId() const{
	return this->id;
}

