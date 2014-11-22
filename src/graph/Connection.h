/*
 * Connection.h
 *
 *  Created on: 19 lis 2014
 *      Author: rafal
 */

#ifndef GRAPH_CONNECTION_H_
#define GRAPH_CONNECTION_H_

#include "../db/lib/Time.h"
#include <iostream>

class Connection{
public:
	/**
	 * Default constructor which makes connection with zero id and times
	 * */
	Connection();

	/**
	 * Constructor
	 * @param departureTime time when bus leaves starting stop
	 * @param arrivalTime time when bus goes on ending stop
	 * @param tripId trip of bus
	 * */
	Connection(Time departureTime, Time arrivalTime,unsigned int tripId);

	/**
	 * Consturctor which copies object
	 * @param con object to copy
	 * */
	Connection(const Connection& con);

	/**
	 * Assign one object to another
	 * @param con object to copy
	 * @return object which was coppied in
	 * */
	Connection& operator=(const Connection& con);

	/**
	 * get departue time
	 * @return time when bus leaves starting stop
	 * */
	Time getDepartureTime() const;

	/**
	 * get arrival time
	 * @return time when bus goes on ending stop
	 * */
	Time getArrivalTime() const;

	/**
	 * get id of trip which makes connectio
	 * @return id of trip
	 */
	unsigned int getTripID() const;

	/**
	 * print connection to stream
	 * @param output stream where information will be print to
	 * @con object to printing
	 * @retur stream where object were printed
	 * */
	friend std::ostream& operator<<(std::ostream& output, Connection con);
private:
	Time departureTime;
	Time arrivalTime;
	unsigned int tripId;
};



#endif /* GRAPH_CONNECTION_H_ */
