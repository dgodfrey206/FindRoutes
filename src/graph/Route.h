/*
 * Route.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

#include <list>
#include <set> //validate() fctn
#include <iostream>

#include "Edge.h"

/**
 * contains information about route between two points
 * Should be used in solver class.
 */
class Route {
public:
	/**
	 * Constructs object. No data is necessary.
	 */
	Route();

	/**
	 * @return Returns length - number of Edge objects.
	 */
	unsigned int getLength() const;

	/**
	 * @return Returns sum of weights of Edge objects.
	 */
	double getWeight() const;

	/**
	 * Checks if Route does not contain any loops and if all edges are connected.
	 * I.e. A->B and then B->C is ok, but A->B and C->D is wrong.
	 * @return True if test is passed, false otherwise.
	 */
	bool validate() const; //checks if all edges are connected, also finds loops

	/**
	 * Add one Edge to the end of Route.
	 * Given edge must start in Node, in which current route ends.
	 * @param e Pointer to given edge.
	 * @return True if edge could be connected to route, false otherwise.
	 */
	bool addEdge(const Edge * e); //adds edge to end of list.

	/**
	 * Switches given edge with one included in path,
	 * @param e Pointer to Edge. Its start Node and end Node must be same as start and
	 * end nodes of edge included in route.
	 * @return True if switch was successful, false otherwise.
	 */
	bool switchEdge(const Edge * e); //locates edge or subroute between two given points and switches it.

	/**
	 * Switches part of Route with given route.
	 * @param r Reference to subroute which needs to be inserted into object. It must to be
	 * correct (validate method is being called), and start and end of subroute must have
	 * corresponding values as start and end of some subroute inside current object.
	 * Length of switched subroutes do not need to be equal.
	 * @return True if switch was successful, false otherwise.
	 */
	bool switchRoute(Route & r); //allows to change one edge for subroute.

	/**
	 * @return Returns pointer to Node on the begining of Route.
	 */
	const Node * getStartNode() const;

	/**
	 * @return pointer to Node on the end of Route.
	 */
	const Node * getEndNode() const;

	/**
	 * @param n Pointer to Node which is being checked.
	 * @return True if given node is currently in route. False otherwise.
	 */
	bool isNodeIn(const Node* n) const;

	/**
	 * @param e Pointer to Edge which is being searched for.
	 * @return True if Edge is included in route, false otherwise.
	 */
	bool isEdgeIn(const Edge* e) const;

	/**
	 * Checks for subroute between given nodes.
	 * @param start Pointer to Node of start.
	 * @param end Pinter to Node of end.
	 * @return True if there is subroute from start to end in route, false otherwise.
	 */
	bool isConnectionBetween(const Node* start, const Node* end) const;

	/**
	 * @return Returns iterator to the begining of route.
	 */
	std::list<const Edge *>::const_iterator begin();

	/**
	 * @return Returns iterator to point after last Edge in route.
	 */
	std::list<const Edge *>::const_iterator end();

	/**
	 * Used of debug in console purposes.
	 * @param s Stream used for output.
	 * @param r Reference to Route being printed.
	 * @return Given stream.
	 */
	friend std::ostream& operator << (std::ostream& s, Route& r);


private:
	std::list<const Edge *> route;
};

#endif /* SRC_ROUTE_H_ */
