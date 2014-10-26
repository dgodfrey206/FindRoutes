/*
 * Solver.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_SOLVER_H_
#define SRC_SOLVER_H_

class Solver {
public:
	/*
	 * wrapper class for solver algorithm.
	 * Those shall inherit from Solver class.
	 * Solver needs to implement solve method,
	 * which gets Network map as
	 */
	Solver();
	virtual ~Solver();

	virtual static Route& solve(const Network &) = 0;
};

#endif /* SRC_SOLVER_H_ */
