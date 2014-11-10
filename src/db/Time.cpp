/*
 * Time.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */


#include "Time.h"

#include <iomanip>

Time::Time(){
	this->hour = 0;
	this->minute = 0;
}

Time::Time(unsigned int hour, unsigned int minute){
	this->hour = hour % 24;
	this->minute = minute % 60;
}

Time::Time(unsigned int minutes){
	this->hour = minutes / 60;
	this->minute = minutes % 60;
}

Time::Time(const Time& src){
	this->hour = src.hour;
	this->minute = src.minute;
}

Time::~Time(){

}

Time Time::operator=(const Time src){
	this->hour = src.hour;
	this->minute = src.minute;
	return *this;
}

bool Time::operator==(const Time src){
	if( (this->hour == src.hour) && (this->minute == src.minute) ){
		return true;
	}else{
		return false;
	}
}

bool Time::operator!=(const Time src){
	return !(this->operator ==(src));
}


bool Time::operator>(const Time src){
	if(this->hour > src.hour){
		return true;
	}else if(this->hour == src.hour) {
		if(this->minute > src.minute){
			return true;
		}else{
			return false;
		}
	}else{
		return false;
	}
}

bool Time::operator<(const Time src){
	return !( (this->operator >(src)) || (this->operator ==(src)) );
}

Time Time::operator+(const Time src){
	return Time((this->hour)+(src.hour), (this->minute)+(src.minute));
}

Time Time::operator-(const Time src){
	if(*this > src){
		return Time((this->hour)-(src.hour), (this->minute)-(src.minute));
	}else{
		return Time((src.hour)-(this->hour), (src.minute)- (this->minute));
	}
}

Time::operator int(){
	return (this->hour) * 60 + this->minute;
}

std::ostream& operator<<(std::ostream& output, const Time src){
	if(src.hour < 10){
		output<<0<<src.hour<<":";
	}else{
		output<<std::setw(2)<<src.hour<<":";
	}
	if(src.minute <10){
		output<<"0"<<src.minute;
	}else{
		output<<std::setw(2)<<src.minute;
	}
	return output;
}

