/*
 * main.cpp
 *
 *  Created on: 15 paź 2014
 *      Author: Wojtek Gumuła
 */

#include <iostream>
#include <string>

#include "db/DataBase.h"
#include "graph/Network.h"
#include "algorithm/DfsAlg.h"

int main()
{
	std::string path = "../db/json";
	DataBase db(DataBase::LoadMethod::MULTJSON, "../db/json");
	Network net(db);

	unsigned int startId, endId;

	for(auto node: net.getAllNodes())
		std::cout<<*node<<std::endl;

	std::cerr<<"type start node id: ";
	std::cin>> startId;
	Node* startNode = net.getNode(startId);
	std::cerr<<"chosen start node: "<<startNode ->getName()<<std::endl;
	std::cerr<<"type end node id: ";
	std::cin>> endId;
	Node* endNode = net.getNode(endId);
	std::cerr<<"chosen end node: "<<endNode ->getName()<<std::endl;

	net.setSover(new DsfAlg());
	net.findRouteBetween(startNode,endNode,100);
}



