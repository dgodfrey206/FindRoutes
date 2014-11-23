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
#include "algorithm/BFS.h"

int main()
{
	std::string path = "../db/json";
	DataBase db(DataBase::LoadMethod::MULTJSON, "../db/json");
	Network net(db);

	unsigned int startId, endId;

	std::cerr<<"type start node id: ";
	std::cin>> startId;
	Node* startNode = net.getNode(startId);
	std::cerr<<"chosen start node: "<<startNode ->getName()<<std::endl;
	std::cerr<<"type end node id: ";
	std::cin>> endId;
	Node* endNode = net.getNode(endId);
	std::cerr<<"chosen end node: "<<endNode ->getName()<<std::endl;

	//net.setSover(new DsfAlg());
	net.setSover(new BsfAlg());
	net.findRouteBetween(startNode,endNode,100);

}



