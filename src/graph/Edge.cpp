/*
 * Edge.cpp
 *
 *  Created on: 26 paź 2014
 *      Author: Wojtek Gumuła
 */

#include "Edge.h"

Edge::Edge(unsigned int id, Node* start, Node* end)
	:
	id(id),
	start(start),
	end(end)
{
}

unsigned int Edge::getID() const {
	return this->id;
}

const Node* Edge::getStartNode() const {
	return this->start;
}

const Node* Edge::getEndNode() const {
	return this->end;
}

bool Edge::operator ==(const Edge& e) const {
	//return (this->getStartNode()->getID() == e.getStartNode()->getID())
	//		&& (this->getEndNode()->getID() == e.getEndNode()->getID());
	return this->getID() == e.getID();
}

bool Edge::operator !=(const Edge& e) const {
	//return (this->getStartNode()->getID() != e.getStartNode()->getID())
	//			|| (this->getEndNode()->getID() != e.getEndNode()->getID());
	return this->getID() != e.getID();
}

Edge& Edge::operator =(const Edge& e) {
	this->id = e.getID();
	this->start = e.getStartNode();
	this->end = e.getEndNode();
	return *this;
}

bool Edge::operator <(const Edge& e) const {
	return this->id < e.getID();
}

std::ostream& operator<<(std::ostream& stream, const Edge& e)
{
	stream << "Edge:" << std::endl;
	stream << "[" << std::setw(4) << std::right << e.getStartNode()->getID() << "]->";
	stream << "[" << std::setw(4) << std::right << e.getEndNode()->getID() << "]-";
	stream << "]-[" << std::setw(5) << std::right << e.getID();
	stream << " " << std::setw(19) << std::right <<e.getStartNode()->getName();
	stream << " " << std::setw(19) << std::right <<e.getEndNode()->getName();

	return stream;
}

void Edge::addConnection(Time departureTime, Time arrivalTime,unsigned int tripId){
	this->connections.push_back(Connection(departureTime,arrivalTime,tripId));
}
