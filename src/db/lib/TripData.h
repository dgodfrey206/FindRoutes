/*
 * TripData.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_LIB_TRIPDATA_H_
#define DB_LIB_TRIPDATA_H_

#include <iostream>
#include <string>
#include <vector>

//todo appendStopToSec(unsigned int id); would be nice to have

/**
 * Class containing data about Trip when database is being created.
 * Then converted into Trip object.
 */
class TripData{
public:

	/**
	 * Default constructor.
	 */
	TripData();

	/**
	 * Copying constructor.
	 * @param src Object being copied.
	 */
	TripData(const TripData& src);

	/**
	 * Constructor.
	 * @param name Name of route.
	 * @param id id of route.
	 * @param routeId RouteData id value.
	 * @param stopSec Vector containing stop sequence.
	 */
	TripData(unsigned int id, unsigned int routeId,std::string name,std::vector<int> stopSec);

	/**
	 * Destructor.
	 */
	~TripData();

	/**
	 * Assignment operator.
	 * @param src Reference object being assigned.
	 * @return Reference to self.
	 */
	TripData& operator=(const TripData& src);

	/**
	 * Helper output function.
	 * @param output Stream
	 * @param src Outputed object.
	 * @return Reference to given stream.
	 */
	friend std::ostream& operator<<(std::ostream& output, const TripData& src);

	/**
	 * Comparation operator.
	 * @param src Reference to compared object.
	 * @return True if name and is are equal.
	 */
	bool operator==(const TripData src);

	/**
	 * @return Returns id value.
	 */
	unsigned int getId() const;

	/**
	 * @return Returns RouteData id value.
	 */
	unsigned int getRouteId() const;

	/**
	 * @return Returns stop sequence in vector<int>.
	 */
	std::vector<int> getStopSec() const;

	/**
	 * @return Returns name value.
	 */
	std::string getName() const;
private:
	unsigned int id;
	unsigned int routeId;
	std::vector<int> stopSec;
	std::string name;
};

#endif /* DB_LIB_TRIPDATA_H_ */
