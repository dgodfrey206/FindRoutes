/*
 * BSFR.h
 *
 *  Created on: 9 gru 2014
 *      Author: rafal
 */

#ifndef ALGORITHM_BSFR_H_
#define ALGORITHM_BSFR_H_

#include "Solver.h"

class BsfRandAlg: public Solver{
public:
	 BsfRandAlg();
	~BsfRandAlg();
	virtual Route* solve(const Network * n, Node * start, Node * end, Time t);
	virtual const std::string & getName() const;
private:
	static const std::string name;
};


#endif /* ALGORITHM_BSFR_H_ */
