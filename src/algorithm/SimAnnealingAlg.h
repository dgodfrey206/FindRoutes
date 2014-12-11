/*
 * SimAnnealingAlg.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_SIMANNEALINGALG_H_
#define SRC_SIMANNEALINGALG_H_

#include "Solver.h"

#include <random>
#include <cmath>
#include <stack>
#include <algorithm>
#include <array>
#include <limits>
#include <cstdlib>
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
	virtual Route* solve(const Network * n, Node * start, Node * end, Time t);
	void setParams(double Tstart, double Tend, unsigned int k, double alpha);

	virtual const std::string & getName() const;

	std::vector<unsigned> getWeights() const;

private:
	static const std::string name;
	std::default_random_engine generator;
	std::uniform_real_distribution<> distribution;
	double Tstart;
	double Tend;
	unsigned int k;
	double alpha;
	std::vector<unsigned> weights;

	double getRandom(unsigned i = 1);

public://todo private
	Route * getRouteInSurroundings(const Network * n, Route * r);
	Route * getFistSolution(const Network * n, Node * start, Node * end);

};

#endif /* SRC_SIMANNEALINGALG_H_ */
