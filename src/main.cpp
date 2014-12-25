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

#include "tester/Tester.h"


int main()
{
	DataBase db(DataBase::LoadMethod::SAVEDDB, "../db/database.json");
	Network net(db);
	SimAnnealingAlg * solver = new SimAnnealingAlg;

	net.setSolver(solver);

	net.validate();
	Node * start = net.getNode(711);
	Node * end = net.getNode(21);

//	auto startTime = std::chrono::system_clock::now();
//
//	solver->setParams(50, 10, 10, 0.99, 5, 15);
//	auto solution = solver->solve(&net, start, end, Time(1000));
//	if(solution) std::cout << *solution << std::endl << solution->getWeight(Time(1000)) << std::endl;
//	else std::cout << "Solution have not been found" << std::endl;
//	auto endTime = std::chrono::system_clock::now();
//	auto length = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
//	std::cout << "Time: " << length.count() << "ms" << std::endl;
//
//	std::ofstream f("../tests/data/save");
//	auto w = solver->getWeights();
//	auto p = solver->getPunishments();
//	auto b = solver->getBestPosWeights();
//	for(unsigned i = 0; i < w.size(); i++) f << w[i] << " " << p[i] << " " << b[i] << std::endl;
//	f.close();

//	Tester tester(&net);
//	tester.setDefaults(100, 1, 10, 0.99, 10, 50);
//	tester.makeTests(start, end, "../tests/data");

	std::cout << "nodes:" << net.getAllNodes().size() << std::endl;
	std::cout << "edges:" << net.getAllEdges().size() << std::endl;
	net.limitRandomly(1000, 10000);
	//std::cout << net << std::endl;
	std::cout << "nodes:" << net.getAllNodes().size() << std::endl;
	std::cout << "edges:" << net.getAllEdges().size() << std::endl;
}



