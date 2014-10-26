/*
 * Route.cpp
 *
 *  Created on: 26 paź 2014
 *      Author: Wojtek Gumuła
 */

#include "Route.h"

Route::Route() {
	/*
	 * init empty list
	 */
	route = std::list<const Edge *>();
}

unsigned int Route::getLength() const {
	/*
	 * return length of route
	 */
	if(this->route.empty())
		return 0;

	unsigned int len = 0;
	for(std::list<const Edge *>::const_iterator it = this->route.begin(); it != this->route.end(); it++)
		len++;
	return len;
}

double Route::getWeight() const {
	/*
	 * return weight of route
	 */
	if(this->route.empty())
			return 0;

	double weight = 0;
	for(std::list<const Edge *>::const_iterator it = this->route.begin(); it != this->route.end(); it++)
		weight += (*it)->getWeight();
	return weight;
}

bool Route::validate() const {
	/*
	 * check if all edges are connected and if there are any loops.
	 */
	return true;//todo
}

bool Route::addEdge(const Edge * e) {
	/*
	 * add edge to the end of route
	 */
	if((this->getLength() != 0) && (*this->route.back()->getEndNode()) != (*e->getStartNode()))
		return false;
	this->route.push_back(e);
	return true;
}

bool Route::switchEdge(const Edge * e) {
	//todo list is broken. Switch to std::set
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
	std::cout << '1';
	if(r.begin() == r.end())
		return false; //unknown behavior
	std::cout << '2';
	//std::list<const Edge *>::iterator pos = std::search(this->route.begin(), this->route.end(), r.begin(), r.end());

	std::list<const Edge *>::iterator startPos = this->route.begin();
	while(*((*startPos)->getStartNode()) != *(r.getStartNode()) && startPos++ != this->route.end()); //locate starting position
	std::cout << '3';

	if(startPos == this->route.end())
		return false;
	std::cout << '4';

	std::list<const Edge *>::iterator endPos = startPos;
	while((endPos++ != this->route.end()) && (*(*(endPos))->getEndNode()) != *(r.getEndNode()));
	std::cout << '5';
	if(endPos == this->route.end())
		return false;
	std::cout << '6';
//	for(std::list<const Edge *>::iterator it = startPos; it != endPos;it = this->route.erase(it));
	//this->route.erase(startPos, endPos);
	std::list<const Edge *>::iterator it = startPos;
	while(*it != *endPos)
	{
		this->route.erase(*it);
	}

	this->route.insert(startPos, r.begin(), r.end());
	std::cout << '7';
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
	pos--;
	stream << "[" << std::setw(5) << std::right << (*pos)->getEndNode()->getID() << "]";
	stream << "[*END] " << (*pos)->getEndNode()->getName() << std::endl;

	stream << "Total length: " << std::setw(10) << std::right << r.getLength() << std::endl;
	stream << "Total weight: " << std::setw(10) << std::right << r.getWeight();

	return stream;
}
