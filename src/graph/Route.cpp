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

unsigned int Route::getWeight(Time t) const{
	/*
	 * return weight of route
	 */
	Time tStart = t;
	if(this->route.empty())
			return 0;

	for(auto it = this->route.begin(); it != this->route.end(); it++){
		auto edge = **it;
		t = edge.getNextTime(t);
		std::cerr<<t<<std::endl;
	}

	t= t - tStart;
	unsigned int weight = t;
	//for(std::list<const Edge *>::const_iterator it = this->route.begin(); it != this->route.end(); it++)
		//weight += (*it)->getWeight();
	return weight;
}

bool Route::validate() const {
	/*
	 * check if all edges are connected and if there are any loops.
	 */

	if(this->route.empty())
		return true;

	std::set<unsigned int> nodes;
	unsigned int id = (this->route.front())->getStartNode()->getID();
	unsigned int lastEndID;
	bool first = true;
	nodes.insert(id);

	for(std::list<const Edge *>::const_iterator pos = this->route.begin(); pos != this->route.end(); pos++)
	{
		if(!first && (lastEndID != (*pos)->getStartNode()->getID()))
			return false;

		id = (*pos)->getEndNode()->getID();

		if(nodes.find(id) != nodes.end()) //found node in set, invalid route
			return false;

		nodes.insert(id);
		lastEndID = id;
	}

	return true;
}

bool Route::addEdge(const Edge * e) {
	/*
	 * add edge to the end of route
	 */
	/*if((this->getLength() != 0) && (*this->route.back()->getEndNode()) != (*e->getStartNode()))
		return false;
		*/
	this->route.push_back(e);
	return true;
}

bool Route::switchEdge(const Edge * e) {
	// todo rewrite for optimisation, do not create route object.
	Route r;
	r.addEdge(e);
	return this->switchRoute(r);

}

bool Route::switchRoute(Route& r) {
	/*
	 * removes subroute from object and replaces it with given subroute.
	 */
	if(r.begin() == r.end()) //empty route
		return false;

	std::list<const Edge *>::iterator startPos = this->route.begin();
	while(*((*startPos)->getStartNode()) != *(r.getStartNode()) && startPos++ != this->route.end()); //locate starting position

	if(startPos == this->route.end())	//did not find
		return false;

	std::list<const Edge *>::iterator endPos(startPos);


	while(endPos != this->route.end())
		if(*(*endPos)->getEndNode() != *r.getEndNode())
			endPos++;
		else
			break;
	if(endPos == this->route.end()) return false;


	if(endPos == this->route.end())
		return false;

	std::list<const Edge *> newRoute;
	std::list<const Edge *>::iterator it;

	newRoute.splice(newRoute.begin(), this->route, this->route.begin(), startPos);

	newRoute.insert(newRoute.end(), r.begin(), r.end());

	newRoute.splice(newRoute.end(), this->route, ++endPos, this->route.end());

	this->route = newRoute;

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
	//stream << "[ FROM]->[   TO]-[WITH]-[ EDGE] ";
	//stream << std::setw(23) << std::right << "FROM NAME" << std::setw(24) << std::right << "TO NAME" << std::endl;

	for(pos = r.begin(); pos != r.end(); pos++)
	{
		stream << "[" << std::setw(5) << std::right << (*pos)->getStartNode()->getID() << "]->";
		stream << "[" << std::setw(5) << std::right << (*pos)->getEndNode()->getID() ;

		stream << "]-[" <<std::setw(10) << std::right << (*pos)->getID() << "]";
		stream << " " << std::setw(25) << std::left <<(*pos)->getStartNode()->getName();
		stream << " " << std::setw(25) << std::left <<(*pos)->getEndNode()->getName() << std::endl;
	}
	//stream << std::endl << std::setw(15) << std::left << "Total length: [" << std::setw(10) << std::right << r.getLength() << "]";
	//stream << std::endl << std::setw(15) << std::left << "Total weight: [" << std::setw(10) << std::right << r.getWeight() << "]";

	return stream;
}

Route::Route(const Route& r) {
	this->route = r.route;
}
