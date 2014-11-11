/*
 * Network.cpp
 *
 *  Created on: 28 paź 2014
 *      Author: Wojtek Gumuła
 */

#include "Network.h"

Network::Network() {
	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();

	this->solver = NULL;
}

Network::Network(std::string filename) {
	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();

	this->solver = NULL;

	this->loadFromFile(filename);
}

Network::~Network() {
	//todo

	for(Node* e: this->nodes){
		delete e;
	}

	delete this->solver;
}

void Network::loadFromFile(std::string filename) {
}

void Network::setSover(Solver * s) {
	if(s != NULL && s != this->solver)
	{
		delete this->solver;
		this->solver = s;
	}
}

Route* Network::findRouteBetween(const Node * start, const Node * end, const unsigned int maxSwitches) {
	return NULL;
}

bool Network::isEdgeBetween(const Node * start, const Node * end) const {

	for(Edge * e: this->edges)
	{
		if(*(e->getStartNode()) == *start && *(e->getEndNode()) == *end)
			return true;
	}

	return false;
}

bool Network::addNode(Node * n) {
	if(n == NULL)
		return false;

	this->nodes.insert(n);
	return true;
}

bool Network::addEdge(Edge* e) {
	if(e == NULL)
		return false;

	this->edges.insert(e);
	return true;
}

Node * Network::getNode(unsigned int id) {
	if(this->nodes.size() <= id)
		return NULL;

	Node * tempNode = new Node(id, "temp", 0, 0);

	auto it = this->nodes.find(tempNode);

	if(it == this->nodes.end())
		return NULL;

	delete tempNode;

	return *it;
}

Edge* Network::getEdge(unsigned int id) {
	if(this->edges.size() <= id)
			return NULL;

	Edge * tempEdge = new Edge(id, NULL, NULL, 0, UNKNOWN);

	auto it = this->edges.find(tempEdge);

	if(it == this->edges.end())
		return NULL;

	delete tempEdge;

	return *it;
}

std::list<Edge *> Network::getEdgesForNode(const Node* n) const {
	std::list<Edge *> found;
	for(Edge * e: this->edges)
		if(*(e->getStartNode()) == *n)
			found.push_back(e);

	return found;
}

std::list<Node*> Network::getAllNodes() {
	std::list<Node *> nodes;
	for(Node * n: this->nodes)
	{
		nodes.push_back(n);
	}
	return nodes;
}

Node * Network::getNodeCloseToPos(double lat, double lon) const {
	double shortestDist, distance;
	Node * closestNode = NULL;

	for(Node * n: this->nodes)
	{
		//compute distance
		distance = std::sqrt(std::pow(lat - n->getLatitude(), 2) + std::pow(lon - n->getLongtitude(), 2));

		if(closestNode == NULL || distance < shortestDist)
		{
			closestNode = n;
			shortestDist = distance;
		}
	}

	return closestNode;
}


Network::Network(DataBase& dataB){
	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();
	this->solver = NULL;
	std::cerr<<"stops number:"<<dataB.stops.size()<<std::endl;

	for(unsigned int i=0; i<dataB.stops.size(); i++){
		Node* temp = new Node(dataB.stops[i].getId(),dataB.stops[i].getName(),dataB.stops[i].getLat(), dataB.stops[i].getLng());
		this->addNode(temp);
	}
}


