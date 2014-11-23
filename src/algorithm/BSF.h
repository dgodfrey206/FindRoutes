/*
 * BFS.h
 *
 *  Created on: 23 lis 2014
 *      Author: rafal
 */

#ifndef ALGORITHM_BSF_H_
#define ALGORITHM_BSF_H_

#include "Solver.h"

class BsfAlg: public Solver{
public:
	BsfAlg();
	~BsfAlg();
	virtual Route* solve(const Network * n, Node * start, Node * end);
};


#endif /* ALGORITHM_BSF_H_ */
