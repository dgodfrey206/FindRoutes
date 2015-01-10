/*
 * Node.h
 *
 *  Created on: 20 Oct 2014
 *      Author: David Godfrey
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <iostream>
#include <iomanip>
#include <string>
#include "Edge.h"
#include <list>
/**
 * primary element.
 * Contains info about position and name of itself.
 */

class Edge;

class Node {
public:
	/**
	 * Constructs new Node object.
	 * @param id Id of an node.
	 * @param name Name of node (stop).
	 * @param lon Longtitude coord.
	 * @param lat Latitude coord.
	 */
	Node(unsigned int id, std::string name, double lon, double lat);

	/**
	 * @return Returns longtitude as double.
	 */
	double getLongtitude() const;

	/**
	 * @return Returns latutide as double.
	 */
	double getLatitude() const;

	/**
	 * @return Returns id of itself.
	 */
	unsigned int getID() const;

	/**
	 * @return Returns string containing name.
	 */
	std::string getName() const;

	std::list<Edge *> getEdges() const;

	bool addEdge(Edge * e);
	/**
	 * Operator used for console debug purposes.
	 * @param s Stream which is used for output.
	 * @param n Node on which operator is called.
	 * @return Given stream.
	 */
	friend std::ostream& operator<<(std::ostream& s, const Node& n);

	/**
	 * Operator compares id of this and given node.
	 * @param n Node which is being compared.
	 * @return True if ids are equal, false otherwise.
	 */
	bool operator ==(const Node & n) const;

	/**
	 * Operator compares id of this and given node.
	 * @param n Node which is being compared.
	 * @return False if ids are equal, true otherwise.
	 */
	bool operator !=(const Node & n) const;

	/**
	 * Operator used in sets in Network class. Compares ids.
	 * @param n Node which is being compared.
	 * @return True if this->id is smaller than n.id, false otherwise.
	 */
	bool operator <(const Node & n) const; //for Network purpose

	/**
	 * Copies params from given Node to itself.
	 * @param n Node which is being copied.
	 * @return Reference to itself.
	 */
	Node & operator = (const Node & n);

private:
	unsigned int id;
	std::string name;
	double longtitude;
	double latitude;

	std::list<Edge *> edges;
};

#endif /* SRC_NODE_H_ */
