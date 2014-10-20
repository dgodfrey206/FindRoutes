/*
 * Edge.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_EDGE_H_
#define SRC_EDGE_H_

#include "Node.h"
#include "TransportType.h"

class Edge {
public:
	Edge();
	~Edge();

	double getWeight() const;
	Node & getStartNode() const;
	Node & getEndNode() const;
	TransportType getType() const;

	void setWeight(double);
	void setType(TransportType);

	friend bool operator == (Edge&, Edge &);
	friend bool operator != (Edge&, Edge &);

private:
	double weight;
	Node & start;
	Node & end;
	TransportType type;

};

#endif /* SRC_EDGE_H_ */
