/*
 * Route.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

#include <list>
#include <algorithm> //std::search
#include <iostream>
#include "Edge.h"

class Route {
	/*
	 * contains information about route between two points
	 * Should be used in solver class.
	 */
public:
	Route();
	unsigned int getLength() const;
	double getWeight() const;
	bool validate() const; //checks if all edges are connected, also finds loops

	bool addEdge(const Edge *); //adds edge to end of list.
	bool switchEdge(const Edge *); //locates edge or subroute between two given points and switches it.
	bool switchRoute(Route &); //allows to change one edge for subroute.
	const Node * getStartNode() const;
	const Node * getEndNode() const;
	bool isNodeIn(const Node*) const;
	bool isEdgeIn(const Edge*) const;
	bool isConnectionBetween(const Node*, const Node*) const;

	std::list<const Edge *>::const_iterator begin();
	std::list<const Edge *>::const_iterator end();

	friend std::ostream& operator << (std::ostream&, Route&);


private:
	std::list<const Edge *> route;
};

#endif /* SRC_ROUTE_H_ */
