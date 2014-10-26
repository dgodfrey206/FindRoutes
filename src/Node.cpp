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
	stream << "Node:" << std::endl;
	stream << "[" << std::setw(4) << std::right << n.getID();
	stream << "]--[" << std::setw(8) << std::right << n.getLatitude();
	stream << "]-[" << std::setw(8) << std::right << n.getLongtitude();
	stream << "] " << std::setw(49) << std::right << n.getName();

	return stream;
}

bool Node::operator ==(const Node& n) const {
	return this->id == n.getID();
}

bool Node::operator !=(const Node& n) const {
	return this->id != n.getID();
}

Node& Node::operator =(const Node& n) {
	this->id = n.getID();
	this->name = n.getName();
	this->longtitude = n.getLongtitude();
	this->latitude = n.getLatitude();

	return *this;
}
