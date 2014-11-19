/*
 * Network.cpp
 *
 *  Created on: 28 Oct 2014
 *      Author: David Godfrey
 */

#include "Network.h"

Network::Network() {
	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();

	this->solver = NULL;

	this->incidenceMatrix = NULL;
}

void Network::createIncidenceMatrix() {
	unsigned int numNodes = this->nodes.size();

	if(numNodes == 0)
		return;

	this->incidenceMatrix = new bool*[numNodes];
	for (unsigned int i = 0; i < numNodes; i++) {
		this->incidenceMatrix[i] = new bool[numNodes];
	}
	for (Edge* e : this->edges)
	{
		this->incidenceMatrix[e->getStartNode()->getID()][e->getEndNode()->getID()] = true;
	}
}
/*
Network::Network(std::string filename) {
	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();

	this->solver = NULL;

	this->loadFromFile(filename);

	this->incidenceMatrix = NULL;
	this->createIncidenceMatrix();
}*/

Network::Network(DataBase& dataB){
	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();
	this->solver = NULL;

	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();
	this->solver = NULL;

	std::vector<Edge*> edge_temp;

	for(unsigned int i=0; i<dataB.stops.size(); i++){
		Node* new_node = NULL;
		new_node = new Node(dataB.stops[i].getId(),dataB.stops[i].getName(),dataB.stops[i].getLat(), dataB.stops[i].getLng());
		if(new_node) this->addNode(new_node);
	}


	for(unsigned int i=0; i<dataB.trips.size(); i++){
		for(unsigned int stop_num=1; stop_num<dataB.trips[i].getStopSec().size(); stop_num++){
			
			unsigned int startNodeId = dataB.trips[i].getStopSec()[stop_num -1];
			unsigned int endNodeId = dataB.trips[i].getStopSec()[stop_num];
			unsigned int edgeId = calculateEdgeId(startNodeId, endNodeId);

			if( !getEdge(edgeId) ){
				
				Node* startNode = getNode(startNodeId);
				Node* endNode = getNode(endNodeId);
				Edge* newEdge = new Edge(edgeId,startNode,endNode);

				std::vector<Time> startNodeStopTimes;
				std::vector<Time> endNodeStopTimes;
			}
		}
	}


	this->incidenceMatrix = NULL;
	this->createIncidenceMatrix();
}

Network::~Network() {

	for(Node* e: this->nodes){
		delete e;
	}

	if(this->incidenceMatrix != NULL)
	{
		unsigned int nodes = this->nodes.size();
		for(unsigned int i = 0; i < nodes; i++)
		{
			if(this->incidenceMatrix[i] != NULL)
				delete [] this->incidenceMatrix[i];
		}
		delete [] this->incidenceMatrix;
	}

	delete this->solver;
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

	/*for(Edge * e: this->edges)
	{
		if(*(e->getStartNode()) == *start && *(e->getEndNode()) == *end)
			return true;
	}

	return false;*/
	return this->incidenceMatrix[start->getID()][end->getID()];
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

Node * Network::getNode(unsigned int id) const {
	if(this->nodes.size() <= id)
		return NULL;

	Node * tempNode = new Node(id, "temp", 0, 0);

	auto it = this->nodes.find(tempNode);

	if(it == this->nodes.end())
		return NULL;

	delete tempNode;

	return *it;
}

Edge* Network::getEdge(unsigned int id) const {
	if(this->edges.size() <= id)
			return NULL;

	Edge * tempEdge = new Edge(id, NULL, NULL);

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

unsigned int Network::calculateEdgeId(unsigned int startId, unsigned int endId){
	return startId + 2000*endId;
}

Network::Network(DataBase& dataB){
	this->edges = std::set<Edge *>();
	this->nodes = std::set<Node *>();
	this->solver = NULL;

	std::vector<Edge*> edge_temp;

	for(unsigned int i=0; i<dataB.stops.size(); i++){
		Node* new_node = NULL;
		new_node = new Node(dataB.stops[i].getId(),dataB.stops[i].getName(),dataB.stops[i].getLat(), dataB.stops[i].getLng());

		if(new_node) this->addNode(new_node);
	}


	for(unsigned int i=0; i<dataB.trips.size(); i++){
		for(unsigned int stop_num=1; stop_num<dataB.trips[i].getStopSec().size(); stop_num++){
			
			unsigned int startNodeId = dataB.trips[i].getStopSec()[stop_num -1];
			unsigned int endNodeId = dataB.trips[i].getStopSec()[stop_num];
			unsigned int edgeId = calculateEdgeId(startNodeId, endNodeId);

			if( !getEdge(edgeId) ){
			
				Node* startNode = getNode(startNodeId);
				Node* endNode = getNode(endNodeId);
				Edge* newEdge = new Edge(edgeId,startNode,endNode);

				std::vector<Time> startNodeStopTimes;
				std::vector<Time> endNodeStopTimes;
			}




		}
	}
}

