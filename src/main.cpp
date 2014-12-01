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

	auto startTime = std::chrono::system_clock::now();

	solver->setParams(25, 1, 20, 0.997);
	auto solution = solver->solve(&net, start, end, Time(1000));
	if(solution) std::cout << *solution << std::endl << solution->getWeight(Time(1000)) << std::endl;
	else std::cout << "Solution have not been found" << std::endl;
	auto endTime = std::chrono::system_clock::now();
	auto length = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	std::cout << "Time: " << length.count() << "ms" << std::endl;
}



