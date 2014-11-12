/*
 * main.cpp
 *
 *  Created on: 15 paź 2014
 *      Author: Wojtek Gumuła
 */

#include <iostream>
#include <fstream>
#include <string>

#include "db/DataBase.h"

#include "graph/Network.h"

int main()
{
	std::string path = "../db/json";

	DataBase db(DataBase::LoadMethod::MULTJSON, "../db/json");

	Network net(db);


	for(Node * n: net.getAllNodes())
	{
		std::cout << "At " << n << ":" << std::endl;
		std::cout << "ID\t" << n->getID() << std::endl;
		std::cout << "Name\t" << n->getName() << std::endl;
		std::cout << "Lat:\t" << n->getLatitude() << std::endl;
		std::cout << "Lon:\t" << n->getLongtitude() << std::endl;
	}
}


