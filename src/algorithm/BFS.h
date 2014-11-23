/*
 * BFS.h
 *
 *  Created on: 23 lis 2014
 *      Author: rafal
 */

#ifndef ALGORITHM_BFS_H_
#define ALGORITHM_BFS_H_

#include "Solver.h"

class BsfAlg: public Solver{
public:
	BsfAlg();
	~BsfAlg();
	virtual Route* solve(const Network * n, Node * start, Node * end);
};


#endif /* ALGORITHM_BFS_H_ */
