/*
 * RouteData.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_LIB_ROUTEDATA_H_
#define DB_LIB_ROUTEDATA_H_

#include <iostream>
#include <string>


/**
 * Class containing data about routes when database is being created.
 * Then converted into Route object.
 */
class RouteData{
public:

	/**
	 * Default constructor.
	 */
	RouteData();

	/**
	 * Copying constructor.
	 * @param src Object being copied.
	 */
	RouteData(const RouteData& src);

	/**
	 * Constructor.
	 * @param name Name of route.
	 * @param id id of route.
	 */
	RouteData(std::string name,unsigned int id);

	/**
	 * Destructor.
	 */
	~RouteData();

	/**
	 * Assignment operator.
	 * @param src Reference object being assigned.
	 * @return Reference to self.
	 */
	RouteData& operator=(const RouteData & src);

	/**
	 * Helper output function.
	 * @param output Stream
	 * @param src Outputed object.
	 * @return Reference to given stream.
	 */
	friend std::ostream& operator<<(std::ostream& output, const RouteData& src);

	/**
	 * Comparation operator.
	 * @param src Reference to compared object.
	 * @return True if name and is are equal.
	 */
	bool operator==(const RouteData & src);

	/**
	 * @return Returns name value.
	 */
	std::string getName() const;

	/**
	 * @return return id value.
	 */
	unsigned int getId() const;
private:
	std::string name;
	unsigned int id;
};



#endif /* DB_LIB_ROUTEDATA_H_ */
