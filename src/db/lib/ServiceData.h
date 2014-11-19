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
#include <bitset> //for binary output
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
	ServiceData(unsigned int id, std::string name, unsigned operationalDays);

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
	 * @return Returns id value.
	 */
	unsigned int getId();

	/**
	 * @return return name value.
	 */
	std::string getName();

	/**
	 * @return return days value.
	 */
	unsigned getDays();

private:
	unsigned int id;
	std::string name;
	unsigned operationalDays; //bitwise sum of DAYS flags casted to int

	enum DAYS {
		MONDAY = 0x01,
		TUESDAY = 0x02,
		WEDNESDAY = 0x04,
		THURSDAY = 0x08,
		FRIDAY = 0x10,
		SATURDAY = 0x20,
		SUNDAY = 0x40
	};
};


#endif /* DB_LIB_SERVICEDATA_H_ */
