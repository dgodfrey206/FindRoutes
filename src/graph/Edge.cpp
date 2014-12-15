/*
 * Edge.cpp
 *
 *  Created on: 26 paź 2014
 *      Author: Wojtek Gumuła
 */

#include "Edge.h"
#include <algorithm>

Edge::Edge():id(0),start(NULL),end(NULL){
	connections = std::vector<Connection>();
};

Edge::Edge(unsigned int id, Node* start, Node* end)
	:
	id(id),
	start(start),
	end(end)
{
	connections = std::vector<Connection>();
}

Edge::Edge(const Edge& e){
	this->id = e.getID();
	this->start = e.getStartNode();
	this->end = e.getEndNode();
	this->connections = e.connections;
}

unsigned int Edge::getID() const {
	return this->id;
}

Node* Edge::getStartNode() const {
	return this->start;
}

Node* Edge::getEndNode() const {
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
	this->connections = e.connections;
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
	stream << "[" << std::setw(8) << std::right << e.getID()<<"]";
	stream << " " << std::setw(19) << std::left <<e.getStartNode()->getName();
	stream << " " << std::setw(19) << std::left <<e.getEndNode()->getName();
	return stream;
}

void Edge::addConnection(Time departureTime, Time arrivalTime,unsigned int tripId){

	Connection newCon(departureTime,arrivalTime,tripId);

	auto it = std::find_if(this->connections.begin(), this->connections.end(), [&](Connection c){
		return (newCon.getArrivalTime() == c.getArrivalTime()) && (newCon.getDepartureTime() == c.getDepartureTime()) && (newCon.getTripID() == c.getTripID());
	});
	if(it == this->connections.end()){
		this->connections.push_back(Connection(departureTime,arrivalTime,tripId));
	}
}

Time Edge::getNextTime(Time t) const{

	if(this->connections.empty()){
		//std::cerr << "no connections!" <<std::endl; //todo
		return Time(0,0);
	}

	Time bestTimeDiff(int(this->connections[0].getArrivalTime()-t));
	Time bestTime = this->connections[0].getArrivalTime();

	for(auto c: this->connections){
		if( (c.getDepartureTime() >= t) && ( int(c.getArrivalTime()-t)< int(bestTimeDiff))){
			bestTimeDiff = c.getArrivalTime()-t;
			bestTime = c.getArrivalTime();
		}
	}

	return bestTime;
}

