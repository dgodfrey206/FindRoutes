/*
 * Time.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */


#include "Time.h"
#include <iomanip>

Time::Time(){
	this->minutes = 0;
}

Time::Time(unsigned int hour, unsigned int minute){
	this->minutes = (60*hour + minute) % (60*24);
}

Time::Time(unsigned int minutes){
	this->minutes = minutes % (60*24);
}

Time::Time(const Time& src){
	this->minutes = src.minutes;
}

Time::~Time(){

}

Time& Time::operator=(const Time& src){
	this->minutes = src.minutes;
	return *this;
}

bool Time::operator==(const Time src){
	if( (this->minutes == src.minutes) ){
		return true;
	}else{
		return false;
	}
}

bool Time::operator!=(const Time src){
	return !(this->operator ==(src));
}


bool Time::operator>(const Time src){
	if(this->minutes > src.minutes ){
		return true;
	}else{
		return false;
	}
}

bool Time::operator<(const Time src){
	if(this->minutes < src.minutes ){
			return true;
	}else{
		return false;
	}
}

Time Time::operator+(const Time src){
	if(this->minutes + src.minutes < 60*24)
		return Time(this->minutes + src.minutes);
	else
		return Time(0);
}

Time Time::operator-(const Time src){
	if(this->minutes - src.minutes < 0)
		return Time(0);
	else
		return Time(this->minutes - src.minutes < 0);
}

Time::operator int(){
	return (this->minutes);
}

std::ostream& operator<<(std::ostream& output, const Time src){
	if((src.minutes / 60) < 10){
		output<<0<<(src.minutes / 60)<<":";
	}else{
		output<<std::setw(2)<<(src.minutes / 60)<<":";
	}
	if( (src.minutes % 60) <10){
		output<<"0"<<(src.minutes % 60);
	}else{
		output<<std::setw(2)<<(src.minutes % 60);
	}
	return output;
}

