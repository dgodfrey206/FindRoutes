/*
 * Network.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_
#include <vector>

#include <vector>
#include "Node.h"
#include "Edge.h"

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
	~Network();

	void loadFromFile(std::string filename);

private:
	std::vector<Node&> nodes;
	std::vector<Edge&> edges;

	bool findEdgeBetween(const Node &, const Node &) const; //returns true if edge between two nodes exists

	bool addNode(Node &); //adds Node if not exists
	bool addEdge(Edge &); //adds Edge if not exists

	void /*todo*/ getEdgesForNode(const Node &) const;
	Node & getNodeCloseToPos(double, double) const; //returns node close do desired position

};

#endif /* SRC_NETWORK_H_ */
