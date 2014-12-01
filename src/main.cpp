/*
 * main.cpp
 *
 *  Created on: 15 paź 2014
 *      Author: Wojtek Gumuła
 */

#include <iostream>
#include <string>

#include "algorithm/DSF.h"
#include "algorithm/BSF.h"
#include "db/DataBase.h"
#include "graph/Network.h"

#include "db/lib/Time.h"

#include "algorithm/SimAnnealingAlg.h"

#include <chrono>
#include <random>

int main()
{
	DataBase db(DataBase::LoadMethod::SAVEDDB, "../db/database.json");
	Network net(db);
	SimAnnealingAlg * solver = new SimAnnealingAlg;

	net.setSolver(solver);

	net.validate();
	Node * start = net.getNode(199);
	Node * end = net.getNode(111);

	std::cout << *start << std::endl << *end << std::endl;
	Route * solution = solver->getFistSolution(&net, start, end);
	if(solution) std::cout << *solution << std::endl << solution->getWeight(Time(1000)) << std::endl;

	solver->setParams(1000, 100, 10, 0.9, Time(1000));
	solution = solver->solve(&net, start, end);
	if(solution) std::cout << *solution << std::endl << solution->getWeight(Time(1000)) << std::endl;

}



