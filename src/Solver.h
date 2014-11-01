/*
 * Solver.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_SOLVER_H_
#define SRC_SOLVER_H_

#include "Network.h"
#include "Route.h"

class Network; //forward declaration

class Solver {
public:
	/*
	 * wrapper class for solver algorithm.
	 * Those shall inherit from Solver class.
	 * Solver needs to implement solve method,
	 * which gets Network map as
	 */
public:
	virtual ~Solver();

	virtual Route& solve(const Network & n) = 0;
};


#endif /* SRC_SOLVER_H_ */
