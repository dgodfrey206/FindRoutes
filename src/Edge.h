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
	Edge(unsigned int id, const Node& start, const Node& end,
			const double weight, const TransportType type);

	unsigned int getID() const;
	double getWeight() const;
	const Node & getStartNode() const;
	const Node & getEndNode() const;
	TransportType getType() const;

	void setWeight(double);
	void setType(TransportType);

	bool operator ==(Edge &);
	bool operator !=(Edge &);

	friend std::ostream& operator<<(std::ostream&, const Edge&);

private:
	unsigned int id;
	const Node & start;
	const Node & end;
	double weight;
	TransportType type;

};

#endif /* SRC_EDGE_H_ */
