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
	return this->id == e.getID();
}

bool Edge::operator !=(const Edge& e) const {
	return this->id != e.getID();
}

Edge& Edge::operator =(const Edge& e) {
	this->id = e.getID();
	this->type = e.getType();
	this->weight = e.getWeight();
	this->start = e.getStartNode();
	this->end = e.getEndNode();

	return *this;
}

std::ostream& operator<<(std::ostream& stream, const Edge& e)
{
	stream << "Edge #";
		stream << std::setw(5) << std::right << e.getID() << "." << std::endl;
		stream << std::setw(8) << std::left << "From:" <<  " [" << std::setw(5) << std::right << e.getStartNode()->getID() << "] " << e.getStartNode()->getName() << std::endl;
		stream << std::setw(8) << std::left << "To:" <<  " [" << std::setw(5) << std::right << e.getEndNode()->getID() << "] " << e.getEndNode()->getName() << std::endl;
		stream << std::setw(8) << std::left << "Type: ";
		if(e.getType() == BUS)
			stream <<  "BUS";
		else if(e.getType() == TRAM)
			stream << "TRAM";
		else
			stream << "UNKNOWN";
		stream << std::endl;

		stream << std::setw(8) << std::left << "Weight: " << e.getWeight();

		return stream;
}
