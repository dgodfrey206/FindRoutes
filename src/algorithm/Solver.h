/*
 * Solver.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_SOLVER_H_
#define SRC_SOLVER_H_

#include "../graph/Network.h"
#include "../graph/Route.h"
#include "../graph/Node.h"
#include "../graph/Edge.h"

class Network; //forward declaration

/**
 * wrapper class for solver algorithm.
 * Those shall inherit from Solver class.
 * Solver needs to implement solve method,
 * which gets Network map as
 *
 * USAGE:
 * int main() {
 * 		Solver * solver;
 * 		solver = new SimAnnealingAlg;
 * 		solver->setParams(...);
 * 		Network net = new Network;
 * 		...
 * 		net.setSolver(solver);
 * 		//in Network:
 * 		// this->solver->solve();
 * }
 */
class Solver {
public:
	virtual ~Solver() {};
	/**
	 * Method used in Network class for finding best connection between points.
	 * This method need to be implemented in any class inheriting from Solver class.
	 * @param n Pointer to Network in which Route is being searched for.
	 * @return Pointer to found Route, NULL if no route can be found.
	 */
	virtual Route* solve(const Network * n,Node * start,Node * end) = 0;
};


#endif /* SRC_SOLVER_H_ */
