/*
 * DfsAlg.h
 *
 *  Created on: 22 lis 2014
 *      Author: rafal
 */

#ifndef ALGORITHM_DSF_H_
#define ALGORITHM_DSF_H_

#include "Solver.h"

class DsfAlg: public Solver{
public:
	DsfAlg();
	~DsfAlg();
	virtual Route* solve(const Network * n, Node * start, Node * end);
};



#endif /* ALGORITHM_DSF_H_ */
