/*
 * Connection.h
 *
 *  Created on: 19 lis 2014
 *      Author: rafal
 */

#ifndef GRAPH_CONNECTION_H_
#define GRAPH_CONNECTION_H_

#include "../db/lib/Time.h"

class Connection{
public:
	Connection();
	Connection(Time departureTime, Time arrivalTime,unsigned int tripId);
	Time getDepartureTime() const;
	Time getArrivalTime() const;
	unsigned int getTripID() const;
private:
	Time departureTime;
	Time arrivalTime;
	unsigned int tripId;
};



#endif /* GRAPH_CONNECTION_H_ */
