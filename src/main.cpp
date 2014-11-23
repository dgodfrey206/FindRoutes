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

int main()
{
	std::string path = "../db/json";
	DataBase db(DataBase::LoadMethod::MULTJSON, "../db/json");
	Network net(db);
	while(1){
	unsigned int startId, endId;

	std::cerr<<"type start node id: ";
	std::cin>> startId;
	Node* startNode = net.getNode(startId);
	std::cerr<<"chosen start node: "<<startNode ->getName()<<std::endl;
	std::cerr<<"type end node id: ";
	std::cin>> endId;
	Node* endNode = net.getNode(endId);
	std::cerr<<"chosen end node: "<<endNode ->getName()<<std::endl;


	std::cerr<<"select algorithm:"<<std::endl;
	std::cerr<<"1 - BSF - path with minimum number of edges"<<std::endl;
	std::cerr<<"2 - DSF - any path connecting begin node with end node"<<std::endl;
	int alg;
	std::cin>>alg;
	Route* result;
	switch(alg){
		case 1:
			net.setSolver(new BsfAlg());
			result = net.findRouteBetween(startNode,endNode,100);
			std::cerr<<*result<<std::endl;
		break;
		case 2:
			net.setSolver(new DsfAlg());
			result = net.findRouteBetween(startNode,endNode,100);
			std::cerr<<*result<<std::endl;
		break;
		default:
			std::cerr<<"error"<<std::endl;
		break;
	}
	std::cerr<<"repeat? 0-no, 1-yes"<<std::endl;
	std::cin>>alg;
	system("clear");
	if(!alg) break;
	}
}



