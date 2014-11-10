/*
 * TripData.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#ifndef DB_TRIPDATA_H_
#define DB_TRIPDATA_H_

#include <iostream>
#include <string>
#include <vector>

class TripData{
	public:
		TripData();
		TripData(const TripData& src);
		TripData(unsigned int id, unsigned int routeId,std::string name,std::vector<int> stopSec);
		~TripData();
		TripData operator=(const TripData src);
		friend std::ostream& operator<<(std::ostream& output, const TripData& src);
		bool operator==(const TripData src);
		unsigned int getId() const;
		unsigned int getRouteId() const;
		std::vector<int> getStopSec() const;
		std::string getName() const;
	private:
		unsigned int id;
		unsigned int routeId;
		std::vector<int> stopSec;
		std::string name;
};

#endif /* DB_TRIPDATA_H_ */
