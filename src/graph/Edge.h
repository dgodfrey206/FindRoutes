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
#include "../db/lib/Time.h"
#include "Connection.h"
#include <vector>
/**
 * Object used for storage of one connections.
 * Includes info about start and end positions,
 * type of connection and weight of it.
 */
class Edge {
public:
	Edge();
	/**
	 * Constructor of Edge object.
	 * @param id Identificator of object.
	 * @param start Pointer to Node assigned as starting position.
	 * @param end Pointer to Node assigned as ending position.
	 * @param weight Given weight.
	 * @param type Enumerated value describing type of route.
	 */
	Edge(unsigned int id, Node* start, Node* end);

	Edge(const Edge& e);

	/**
	 * @return Returns id of itself.
	 */
	unsigned int getID() const;

	/**
	 * @return Returns pointer to starting Node.
	 */
	const Node * getStartNode() const;

	/**
	 * @return Returns pointer to ending Node.
	 */
	const Node * getEndNode() const;

	/**
	 * Compares itself id with given edge id.
	 * @param e Given Edge.
	 * @return True if ids are equal, false otherwise.
	 */
	bool operator ==(const Edge & e) const;

	/**
	 * Compares itself id with given edge id.
	 * @param e Given Edge.
	 * @return True if ids are not equal, false otherwise.
	 */
	bool operator !=(const Edge & e) const;

	/**
	 * Compares itself id with given edge id. Method used in Network class.
	 * @param e Given Edge.
	 * @return True if this->id is smaller than e.id, false otherwise.
	 */
	bool operator <(const Edge & e) const; //for network sets

	/**
	 * Assign operator.
	 * @param e Given Edge.
	 * @return Reference to itself.
	 */
	Edge & operator = (const Edge & e);

	/**
	 * Operator used for console debug purposes.
	 * @param s Stream which is used for output.
	 * @param e Edge on which operator is called.
	 * @return Given stream.
	 */
	friend std::ostream& operator<<(std::ostream& s, const Edge& e);


	void addConnection(Time departureTime, Time arrivalTime,unsigned int tripId);

	std::vector<Connection> connections;
private:
	unsigned int id;
	const Node * start;
	const Node * end;

};

#endif /* SRC_EDGE_H_ */
