/*
 * SimAnnealingAlg.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_SIMANNEALINGALG_H_
#define SRC_SIMANNEALINGALG_H_

#include "Solver.h"

class SimAnnealingAlg: public Solver {
public:
	SimAnnealingAlg();
	~SimAnnealingAlg();

	virtual static Route& solve(const Network &);
};

#endif /* SRC_SIMANNEALINGALG_H_ */
