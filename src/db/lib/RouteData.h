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
//todo RouteData need to contain TransportType enum value or coresponding.
class RouteData{
	public:
		RouteData();
		RouteData(const RouteData& src);
		RouteData(std::string name,unsigned int id);
		~RouteData();
		RouteData operator=(const RouteData src);
		friend std::ostream& operator<<(std::ostream& output, const RouteData& src);
		bool operator==(const RouteData src);
		std::string getName() const;
		unsigned int getId() const;
	private:
		std::string name;
		unsigned int id;
};



#endif /* DB_LIB_ROUTEDATA_H_ */
