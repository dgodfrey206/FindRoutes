/*
 * Network.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include <set>
#include <list>
#include <iostream>
#include <cmath> //distance computing

#include "Node.h"
#include "Edge.h"
#include "TransportType.h"
#include "Route.h"
#include "Solver.h"

class Network {
	/*
	 * main class, contains information
	 * about nodes and edges between them.
	 * Should be created from file containing
	 * data in GTFS or other format. //todo
	 * loadFromFile method should load "db/db.ext" file
	 * and save it to inner variables.
	 */
public:
	Network();
	Network(std::string);
	~Network();

	void loadFromFile(std::string);
	void setSover(Solver *);// todosetSolver(Route & (*ptr)(const Network &))?;

	Route * findRouteBetween(const Node *, const Node *);

	friend std::ostream& operator<<(std::ostream&, const Network&);

private:
	std::set<Node *> nodes;
	std::set<Edge *> edges;

	bool isEdgeBetween(const Node *, const Node *) const; //returns true if edge between two nodes exists

	bool addNode(Node *); //adds Node if not exists
	bool addEdge(Edge *); //adds Edge if not exists

	Node * getNode(unsigned int); //get Node by id
	Edge * getEdge(unsigned int); //get Edge by id

	std::list<Edge *> getEdgesForNode(const Node *) const;
	Node * getNodeCloseToPos(double latitude, double longtitude) const; //returns node close do desired position

	Solver * solver;
};

#endif /* SRC_NETWORK_H_ */
