/*
 * Route.cpp
 *
 *  Created on: 26 paź 2014
 *      Author: Wojtek Gumuła
 */

#include "Route.h"

Route::Route() {
	route = std::list<const Edge *>();
}

unsigned int Route::getLength() const {
	if(this->route.empty())
		return 0;

	unsigned int len = 0;
	for(std::list<const Edge *>::const_iterator it = this->route.begin(); it != this->route.end(); it++)
		len++;
	return len;
}

double Route::getWeight() const {
	if(this->route.empty())
			return 0;

	double weight = 0;
	for(std::list<const Edge *>::const_iterator it = this->route.begin(); it != this->route.end(); it++)
		weight += (*it)->getWeight();
	return weight;
}

bool Route::validate() const {
	return true;//todo
}

bool Route::addEdge(const Edge * e) {
	if((this->getLength() != 0) && this->route.back()->getEndNode() != e->getEndNode())
		return false;
	this->route.push_back(e);
	return true;
}

bool Route::switchEdge(const Edge * e) {
	std::list<const Edge *>::iterator pos;
	for(pos = this->route.begin(); pos != this->route.end(); pos++)
	{
		if((*pos)->getStartNode() == e->getStartNode() && (*pos)->getEndNode() == e->getEndNode())
		{
			this->route.erase(pos);
			this->route.insert(pos, e);
			return true;
		}
	}
	return false;
}

bool Route::switchRoute(Route& r) {
	if(r.begin() == r.end())
		return false; //unknown behavior

	std::list<const Edge *>::iterator pos = std::search(this->route.begin(), this->route.end(), r.begin(), r.end());
	if(pos == this->route.end())
		return false;

	std::list<const Edge *>::iterator it = pos;
	while(*((*it)->getStartNode()) != *(r.getEndNode()))
	{
		this->route.remove(*it);
	}
	this->route.insert(pos, r.begin(), r.end());
	return true;
}

const Node* Route::getStartNode() const {
	return this->route.front()->getStartNode();
}

const Node* Route::getEndNode() const {
	return this->route.back()->getEndNode();
}

bool Route::isNodeIn(const Node* n) const {
	for(std::list<const Edge *>::const_iterator it = this->route.begin(); it != this->route.end(); it++)
	{
		if((*(*it)->getStartNode()) == *n)
			return true;
	}
	return *(this->route.back()->getEndNode()) == *n;
}

bool Route::isEdgeIn(const Edge * e) const {
	for(std::list<const Edge *>::const_iterator it = this->route.begin(); it != this->route.end(); it++)
	{
		if(*it == e)
			return true;
	}
	return false;
}

std::list<const Edge*>::const_iterator Route::begin() {
	return this->route.begin();
}

std::list<const Edge*>::const_iterator Route::end() {
	return this->route.end();
}

bool Route::isConnectionBetween(const Node* start, const Node* end) const {
	bool startNodeExists = false;
	std::list<const Edge *>::const_iterator pos;
	for(pos = this->route.begin(); pos != this->route.end(); pos++)
	{
		if((*(*pos)->getStartNode()) == *start)
		{
			startNodeExists = true;
			break;
		}
	}
	if(!startNodeExists)
		return false;

	while(pos++ != route.end())
		if((*(*pos)->getEndNode()) == *end)
			return true;

	return false;
}

std::ostream& operator << (std::ostream& stream, Route & r){
	std::list<const Edge *>::const_iterator pos;
	stream << "Route:" << std::endl;

	for(pos = r.begin(); pos != r.end(); pos++)
	{
		stream << "[" << std::setw(5) << std::right << (*pos)->getStartNode()->getID() << "]";
		if((*pos)->getType() == BUS)
			stream << "[" << std::setw(4) << std::right << "BUS";
		else if((*pos)->getType() == TRAM)
			stream << "[" << std::setw(4) << std::right << "TRAM";
		else
			stream << "[" << std::setw(4) << std::right << "UNKN";
		stream << "] " << (*pos)->getStartNode()->getName() << std::endl;
	}
	stream << "Total length: " << std::setw(10) << std::right << r.getLength() << std::endl;
	stream << "Total weight: " << std::setw(10) << std::right << r.getWeight() << std::endl;

	return stream;
}
