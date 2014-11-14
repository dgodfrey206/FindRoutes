/*
 * StopTimeData.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_LIB_STOPTIMEDATA_H_
#define DB_LIB_STOPTIMEDATA_H_

#include <iostream>
#include <string>
#include "Time.h"


/**
 * Class containing data about stopTimes when database is being created.
 */
class StopTimeData{
public:

	/**
	 * Default constructor.
	 */
	StopTimeData();

	/**
	 * Copying constructor.
	 * @param src Object being copied.
	 */
	StopTimeData(const StopTimeData& src);

	/**
	 * Constructor.
	 * @param name Name of route.
	 * @param id id of route.
	 * @param stopID ID of StopData object of which timetable info contains this object.
	 * @param serviceID id of ServiceData object.
	 * @param tripID TripData object being mentioned.
	 *
	 */
	StopTimeData(unsigned int id, unsigned int stopID, unsigned int serviceID, unsigned int tripID, std::string name);

	/**
	 * Destructor.
	 */
	~StopTimeData();

	/**
		 * Assignment operator.
		 * @param src Reference object being assigned.
		 * @return Reference to self.
		 */
	StopTimeData operator=(const StopTimeData src);

	/**
	 * Helper output function.
	 * @param output Stream
	 * @param src Outputed object.
	 * @return Reference to given stream.
	 */
	 friend std::ostream& operator<<(std::ostream& output, const StopTimeData& src);

	 /**
	 * Comparation operator.
	 * @param src Reference to compared object.
	 * @return True if name and is are equal.
	 */
	bool operator==(const StopTimeData src);

	/**
	 * @return Returns id value.
	 */
	unsigned int getId() const;

	/**
	 * @return Returns ServiceData id value.
	 */
	unsigned int getServiceId() const;

	/**
	 * @return Returns StopData id value.
	 */
	unsigned int getStopId() const;

	/**
	 * @return Returns TripData id value.
	 */
	unsigned int getTripId() const;

	/**
	 * @return Returns Time value.
	 */
	Time getStopTime() const;

	/**
	 * @return Returns name value.
	 */
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
