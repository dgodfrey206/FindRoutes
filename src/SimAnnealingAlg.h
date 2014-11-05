/*
 * SimAnnealingAlg.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_SIMANNEALINGALG_H_
#define SRC_SIMANNEALINGALG_H_

#include "Solver.h"

/**
 * Simulated Annealing Algorithm used for finding routes.
 * See doc folder for more information.
 */
class SimAnnealingAlg: public Solver {
public:
	SimAnnealingAlg();
	~SimAnnealingAlg();

	/**
	 * Method used in Network class for finding best connection between points.
	 * @param n Pointer to Network in which Route is being searched for.
	 * @return Pointer to found Route, NULL if no route can be found.
	 */
	virtual static Route* solve(const Network * n);
};

#endif /* SRC_SIMANNEALINGALG_H_ */
