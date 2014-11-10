/*
 * DataBase.h
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa³ Prusak
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
#include "lib/ItersData.h"

class DataBase{
	public:
		DataBase();
		~DataBase();

		std::vector<RouteData> routes;
		std::vector<TripData> trips;
		std::vector<StopData> stops;
		std::vector<StopTimeData> stopTimes;
		std::vector<ServiceData> services;
		ItersData data;

	private:
		const std::string routesFile;
		const std::string tripsFile;
		const std::string stopsFile;
		const std::string stopTimesFile;
		const std::string servicesFile;
		const std::string itersFile;
};


#endif /* DB_DATABASE_H_ */
