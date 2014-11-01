/*
 * Edge.cpp
 *
 *  Created on: 26 paź 2014
 *      Author: Wojtek Gumuła
 */

#include "Edge.h"

Edge::Edge(unsigned int id, Node* start, Node* end, double weight, TransportType type)
	:
	id(id),
	start(start),
	end(end),
	weight(weight),
	type(type)
{
}

unsigned int Edge::getID() const {
	return this->id;
}

double Edge::getWeight() const {
	return this->weight;
}

const Node* Edge::getStartNode() const {
	return this->start;
}

const Node* Edge::getEndNode() const {
	return this->end;
}

TransportType Edge::getType() const {
	return this->type;
}

void Edge::setWeight(double weight) {
	this->weight = weight;
}

void Edge::setType(TransportType type) {
	this->type = type;
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
	this->type = e.getType();
	this->weight = e.getWeight();
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

	if(e.getType() == BUS)
		stream << "[" << std::setw(4) << std::right << "BUS";
	else if(e.getType() == TRAM)
		stream << "[" << std::setw(4) << std::right << "TRAM";
	else
		stream << "[" << std::setw(4) << std::right << "UNKN";

	stream << "]-[" << std::setw(5) << std::right << e.getID();
	stream << "]-[" << std::setw(7) << std::right << e.getWeight() << "]";
	stream << " " << std::setw(19) << std::right <<e.getStartNode()->getName();
	stream << " " << std::setw(19) << std::right <<e.getEndNode()->getName();

	return stream;
}
