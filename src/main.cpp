/*
 * main.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: David Godfrey
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

	long seed = 889573451;
	std::vector<unsigned> sizes = {/*5, 10, 20, 30, 40,*/ 50};
	for(auto s : sizes)
	{
		Node * start;
		Node * end;

		Network * net = Network::generateRandomNetwork(s, s, seed, 1);

		auto nodes = net->getAllNodes();
		auto pos = nodes.begin();
		std::advance(pos, std::rand() % nodes.size());
		start = *pos;
		pos = nodes.begin();
		std::advance(pos, std::rand() % nodes.size());
		end = *pos;
		std::cout << end <<std::endl;
		Tester tester(net);
		tester.setDefaults(100, 1, 10, 0.99, 10, 50);
		tester.makeTests(start, end, "../tests/data/" + std::to_string(s), seed);

	}


}
 
