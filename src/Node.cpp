/*
 * Node.cpp
 *
 *  Created on: 26 paź 2014
 *      Author: Wojtek Gumuła
 */

#include "Node.h"

Node::Node(unsigned int id, std::string name, double lon, double lat)
	:
	id(id),
	name(name),
	longtitude(lon),
	latitude(lat)
{}

double Node::getLongtitude() const
{
	return this->longtitude;
}

double Node::getLatitude() const
{
	return this->latitude;
}

unsigned int Node::getID() const
{
	return this->id;
}

std::string Node::getName() const
{
	return this->name;
}

std::ostream& operator<<(std::ostream& stream, const Node& n)
{
	stream << "Node #";
	stream << std::setw(5) << std::right << n.getID() << ". ";
	stream << n.getName() << std::endl;
	stream << '\t' << std::setw(8) << std::right  << n.getLatitude() << ' ';
	stream << std::setw(8) << std::right << n.getLongtitude();

	return stream;
}

bool Node::operator ==(Node& n) {
	return this->id == n.getID();
}

bool Node::operator !=(Node& n) {
	return this->id != n.getID();
}
