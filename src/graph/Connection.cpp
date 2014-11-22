/*
 * Connection.cpp
 *
 *  Created on: 19 lis 2014
 *      Author: rafal
 */

#include "Connection.h"

Connection::Connection(){
	this->departureTime = Time(0);
	this->arrivalTime =  Time(0);
	this->tripId = 0;
}

Connection::Connection(Time departureTime, Time arrivalTime,unsigned int tripId){
	this->departureTime = departureTime;
	this->arrivalTime = arrivalTime;
	this->tripId = tripId;
}

Connection::Connection(const Connection& con){
	this->departureTime = con.departureTime;
	this->arrivalTime = con.arrivalTime;
	this->tripId = con.tripId;
}

Connection& Connection::operator=(const Connection& con){
	this->departureTime = con.departureTime;
	this->arrivalTime = con.arrivalTime;
	this->tripId = con.tripId;
	return *this;
}

std::ostream& operator<<(std::ostream& output, Connection con){
	output<<con.departureTime<<" - "<<con.arrivalTime<<" trip: "<<con.tripId;
	return output;
}

Time Connection::getDepartureTime() const{
	return this->departureTime;
}
Time Connection::getArrivalTime() const{
	return this->arrivalTime;
}

unsigned int Connection::getTripID() const{
	return this->tripId;
}

