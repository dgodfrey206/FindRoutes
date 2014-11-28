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

int main()
{
	DataBase db(DataBase::LoadMethod::SAVEDDB, "../db/database.json");
	Network net(db);
	SimAnnealingAlg * solver = new SimAnnealingAlg;

	net.setSolver(solver);

	net.validate();

	Node * start = net.getNode(3);
	Node * end = net.getNode(40);

	std::cout << "Searching route between" << std::endl;

	std::cout << *start << std::endl << *end << std::endl;

	Route * first = solver->getFistSolution(&net, start, end);
	Route * surr = first;
	Route * newR;
	for(int i = 0; i < 100; i++)
	{

		newR = solver->getRouteInSurroundings(&net, surr);
		if(surr != NULL)
		{
			std::cout << "Changed " << std::endl << *surr << std::endl;
			std::cout << "Len:" << surr->getLength() << std::endl;
			std::cout << "To " << std::endl << *newR << std::endl;
			std::cout << "Len:" << newR->getLength() << std::endl;
			surr = newR;
		}
		else
		{
			std::cout << "brik" << std::endl;
			break;
		}

	}

	//std::cout << *first << std::endl << *surr << std::endl;
}



