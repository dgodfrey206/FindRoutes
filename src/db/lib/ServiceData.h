/*
 * ServiceData.h
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_LIB_SERVICEDATA_H_
#define DB_LIB_SERVICEDATA_H_

#include <iostream>
#include <string>

/**
 * Class containing data about services when database is being created.
 */
class ServiceData{
public:

	/**
	 * Default constructor.
	 */
	ServiceData();

	/**
	 * Copying constructor.
	 * @param src Object being copied.
	 */
	ServiceData(const ServiceData& src);

	/**
	 * Constructor.
	 * @param name Name of route.
	 * @param id id of route.
	 */
	ServiceData(unsigned int id, std::string name);

	/**
	 * Destructor.
	 */
	~ServiceData();

	/**
	 * Assignment operator.
	 * @param src Reference object being assigned.
	 * @return Reference to self.
	 */
	ServiceData& operator=(const ServiceData& src);

	/**
	 * Comparation operator.
	 * @param src Reference to compared object.
	 * @return True if name and is are equal.
	 */
	bool operator==(const ServiceData src);

	/**
	 * Helper output function.
	 * @param output Stream
	 * @param src Outputed object.
	 * @return Reference to given stream.
	 */
	friend std::ostream& operator<<(std::ostream& output, const ServiceData& src);

	/**
	 * @return Returns name value.
	 */
	unsigned int getId();

	/**
	 * @return return id value.
	 */
	std::string getName();

private:
	unsigned int id;
	std::string name;
};


#endif /* DB_LIB_SERVICEDATA_H_ */
