/*
 * StopData.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_LIB_STOPDATA_H_
#define DB_LIB_STOPDATA_H_

#include <string>
#include <iostream>

/**
 * Class containing data about routes when database is being created.
 * Then convered into Route object.
 */
class StopData{
public:

	/**
	 * Default constructor.
	 */
	StopData();

	/**
	 * Copying constructor.
	 * @param src Object being copied.
	 */
	StopData(const StopData& src);

	/**
	 * Constructor.
	 * @param name Name of route.
	 * @param id id of route.
	 * @param lat, lng coords of stop.
	 */
	StopData(std::string name,unsigned int id,double lat,double lng);

	/**
	 * Destructor.
	 */
	~StopData();

	/**
	 * Assignment operator.
	 * @param src Reference object being assigned.
	 * @return Reference to self.
	 */
	StopData operator=(const StopData src);

	/**
	 * Helper output function.
	 * @param output Stream
	 * @param src Outputed object.
	 * @return Reference to given stream.
	 */
	friend std::ostream& operator<<(std::ostream& output, const StopData& src);

	/**
	 * Comparation operator.
	 * @param src Reference to compared object.
	 * @return True if name and is are equal.
	 */
	bool operator==(const StopData src);

	/**
	 * @return Returns name value.
	 */
	std::string getName() const;

	/**
	 * @return return id value.
	 */
	unsigned int getId() const;

	/**
	 * @return return latitude value.
	 */
	double getLat() const;

	/**
	 * @return return longtitude value.
	 */
	double getLng() const;
private:
	std::string name;
	unsigned int id;
	double lat;
	double lng;
};



#endif /* DB_LIB_STOPDATA_H_ */
