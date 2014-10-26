/*
 * main.cpp
 *
 *  Created on: 15 paź 2014
 *      Author: Wojtek Gumuła
 */

#include <iostream>
//#include "Network.h"
#include "Node.h"
#include "Edge.h"
#include "Route.h"

int main()
{
	Node* n1 = new Node(1, "Wezel 1", 12.12319, 23.64345);
	Node* n2 = new Node(2321, "Wezel 2", 13.5312, 24.87455);
	Node* n3 = new Node(321, "Wezel 3", 13.53112, 24.874255);
	Edge* e1 = new Edge(1, n1, n2, 12.444, BUS);
	Edge* e2 = new Edge(2, n2, n3, 14.444, TRAM);
	Route * route = new Route;

	std::cout << *n1 << std::endl;
	std::cout << *n2 << std::endl;
	std::cout << *e1 << std::endl;
	std::cout << *e2 << std::endl;
	std::cout << ((*e1 != *e2) ? "Edges not equal" : "Edges equal") <<std::endl;
	std::cout << *route;
	route->addEdge(e1);
	route->addEdge(e2);
	std::cout << *route;
}


