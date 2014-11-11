/*
 * DataBase.h
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_DATABASE_H_
#define DB_DATABASE_H_

#include <iostream>
#include <string>

#include "lib/RouteData.h"
#include "lib/TripData.h"
#include "lib/StopData.h"
#include "lib/StopTimeData.h"
#include "lib/ServiceData.h"

class DataBase{
	public:
		enum LoadMethod {
			JSON = 0,
			GTFS = 1
		};
//		DataBase();
		DataBase(DataBase::LoadMethod method, std::string path);
		void printTimeTable();		//combo!
		std::vector<RouteData> routes;
		std::vector<TripData> trips;
		std::vector<StopData> stops;
		std::vector<StopTimeData> stopTimes;
		std::vector<ServiceData> services;



	private:
		const std::string path;

		void loadGTFS();
		void loadJSON();
};


#endif /* DB_DATABASE_H_ */
