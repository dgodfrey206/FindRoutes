/*
 * StopTimeData.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#ifndef DB_LIB_STOPTIMEDATA_H_
#define DB_LIB_STOPTIMEDATA_H_

#include <iostream>
#include <string>
#include "Time.h"


class StopTimeData{
public:
		StopTimeData();
		StopTimeData(const StopTimeData& src);
		StopTimeData(unsigned int id, unsigned int stopID, unsigned int serviceID, unsigned int tripID, std::string name);
		~StopTimeData();
		StopTimeData operator=(const StopTimeData src);
		friend std::ostream& operator<<(std::ostream& output, const StopTimeData& src);
		bool operator==(const StopTimeData src);
		unsigned int getId() const;
		unsigned int getServiceId() const;
		unsigned int getStopId() const;
		unsigned int getTripId() const;
		Time getStopTime() const;
		std::string getName() const;
	private:
		unsigned int id;
		unsigned int serviceId;
		unsigned int stopId;
		unsigned int tripId;
		Time stoptime;
		std::string name;
};



#endif /* DB_LIB_STOPTIMEDATA_H_ */
