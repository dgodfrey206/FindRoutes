/*
 * main.cpp
 *
 *  Created on: 15 paź 2014
 *      Author: Wojtek Gumuła
 */

#include <iostream>
#include <fstream>
#include <streambuf>

#include <string>
#include "Network.h"
#include "Node.h"
#include "Edge.h"
#include "Route.h"

#include "jsoncpp/json/json.h"

int main()
{
	/*
	Node * nodes[5];
	Edge * edges[8];
	for(int i = 0; i < 5; i++)
	{
		nodes[i] = new Node(i, "Wezel", i, i);
		std::cout << *(nodes[i]) << std::endl;
	}
	for(int i = 0; i < 8; i++)
	{
		edges[i] = new Edge(i, nodes[i % 4], nodes[i% 4 + 1], i + 1, TransportType(2 * i/3 % 2));
		std::cout << *(edges[i]) << std::endl;
	}

	Route * r1 = new Route;
	for(int i = 0; i < 4; i++)
		r1->addEdge(edges[i]);
	std::cout << *r1 << std::endl;

	Route * r2 = new Route;
	r2->addEdge(edges[6]);
	r2->addEdge(edges[7]);
	std::cout << *r2 << std::endl;

	if(!(r1->switchRoute(*r2)))
			std::cout << "Switch failed" << std::endl;

	if(!(r1->switchEdge(edges[4])))
		std::cout << "Switch failed" << std::endl;
	std::cout << *r1 << std::endl;

	if(r1->validate())
		std::cout << "ok";
	else
		std::cout << ":(";
*/
	std::string filename = "../db/db.json";
	std::ifstream in(filename);
	std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

	std::cout << "Load network from file test program" << std::endl;
	std::cout << "DB file is: " << filename << std::endl;
	std::cout << "Calling method..." << std::endl;

	Json::Value root;
	Json::Reader reader;
	if(reader.parse(s, root))
		std::cout << "Successfully read file" << std::endl;
	else
	{
		std::cout  << "Failed to parse \n"
		               << reader.getFormattedErrorMessages();
		return 0;
	}
	Json::Value stops = root["stops"];

	for(unsigned int i = 0; i < stops.size(); i++)
	{
		std::cout << stops[i].toStyledString();
	}


}


