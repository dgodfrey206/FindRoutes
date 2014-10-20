/*
 * Route.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

#include <vector>
#include "Edge.h"

class Route {
	/*
	 * contains information about route between two points
	 * Should be used in solver class.
	 */
public:
	Route();
	~Route();

private:
	std::vector<Edge &> route;
};

#endif /* SRC_ROUTE_H_ */
