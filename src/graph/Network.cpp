/*
 * Network.cpp
 *
 *  Created on: 28 Oct 2014
 *      Author: David Godfrey
 */

#include "Network.h"

Network::Network() {
	/*
	this->edges = std::set<Edge *, Network::edgePointerCompare>();
	this->nodes = std::set<Node *, Network::nodePointerCompare>();*/
	this->solver = NULL;
	this->incidenceMatrix = NULL;
}

void Network::createIncidenceMatrix() {
	std::cerr<<"Network::createIncidenceMatrix(): creating incidence matrix"<<std::endl;
	unsigned int numNodes = this->nodes.size();

	if(numNodes == 0){
		std::cerr<<"Network::createIncidenceMatrix(): creating incidence matrix failed, no nodes found"<<std::endl;
		return;
	}
	this->incidenceMatrix = new bool*[numNodes];
	for (unsigned int i = 0; i < numNodes; i++) {
		this->incidenceMatrix[i] = new bool[numNodes];
	}
	for(unsigned int i = 0; i < numNodes; i++){
		for(unsigned int j = 0; j < numNodes; j++){
			incidenceMatrix[i][j] = false;
		}
	}
	for (Edge* e : this->edges)
	{
		this->incidenceMatrix[e->getStartNode()->getID()][e->getEndNode()->getID()] = true;
	}
	std::cerr<<"Network::createIncidenceMatrix(): incidence matrix done"<<std::endl;

}

Network::Network(DataBase& dataB){
	/*this->edges = std::set<Edge *, Network::edgePointerCompare>();
	this->nodes = std::set<Node *, Network::nodePointerCompare>();*/
	this->solver = NULL;
	this->incidenceMatrix = NULL;

	std::cerr<<"Network::Network(DataBase& dataB): creating netork from database"<<std::endl;
	std::cerr<<"Network::Network(DataBase& dataB): creating nodes"<<std::endl;
	for(unsigned int i=0; i<dataB.stops.size(); i++){
		Node* new_node = NULL;
		new_node = new Node(dataB.stops[i].getId(),dataB.stops[i].getName(),dataB.stops[i].getLat(), dataB.stops[i].getLng());
		if(new_node) this->addNode(new_node);
	}
	std::cerr<<"Network::Network(DataBase& dataB): nodes done, network contains "<<this->nodes.size()<<" nodes"<<std::endl;

	std::cerr<<"Network::Network(DataBase& dataB): connecting times with stop sequences"<<std::endl;
	std::vector<std::vector<std::vector<Time>>>	stopTimesTable;

	for(unsigned int trip_id=0; trip_id<dataB.trips.size(); trip_id++){
		std::vector<std::vector<Time>> _stops_in_sec;
		for(unsigned int stop=0; stop<dataB.trips[trip_id].getStopSec().size();stop++){
			unsigned int stop_id = (dataB.trips[trip_id].getStopSec()[stop]);
			std::vector<Time> _times;
			for(unsigned int stop_time=0; stop_time< dataB.stopTimes.size();stop_time++){
				if( (dataB.stopTimes[stop_time].getServiceId() == 0) 	&&
					(dataB.stopTimes[stop_time].getStopId() == stop_id) &&
					(dataB.stopTimes[stop_time].getTripId() == trip_id)){
						_times.push_back(dataB.stopTimes[stop_time].getStopTime());
				}
			}
			_stops_in_sec.push_back(_times);
		}
		stopTimesTable.push_back(_stops_in_sec);
	}
	std::cerr<<"Network::Network(DataBase& dataB): done"<<std::endl;

	std::cerr<<"Network::Network(DataBase& dataB): creating edges"<<std::endl;
	for(auto trip: dataB.trips){
		std::vector<int> stopSec = trip.getStopSec();
		for(unsigned int stop=1; stop<stopSec.size(); stop++){

	for(unsigned int i=0; i<dataB.trips.size(); i++){
		for(unsigned int stop_num=1; stop_num<dataB.trips[i].getStopSec().size(); stop_num++){
			
			unsigned int startNodeId = dataB.trips[i].getStopSec()[stop_num -1];
			unsigned int endNodeId = dataB.trips[i].getStopSec()[stop_num];
	//for(unsigned int trip_num=0; trip_num<dataB.trips.size(); trip_num++){
	unsigned int trip_num=0;
		for(unsigned int stop_num=1; stop_num<dataB.trips[trip_num].getStopSec().size(); stop_num++){
			
			unsigned int startNodeId = dataB.trips[trip_num].getStopSec()[stop_num -1];
			unsigned int endNodeId = dataB.trips[trip_num].getStopSec()[stop_num];
			unsigned int edgeId = calculateEdgeId(startNodeId, endNodeId);

			if( !getEdge(edgeId) ){
				
				Node* startNode = getNode(startNodeId);
				Node* endNode = getNode(endNodeId);
				Edge* newEdge = new Edge(edgeId,startNode,endNode);
			
				for(unsigned int i = 0; i< dataB.stopTimesTable[trip_num][stop_num -1].size(); i++){
					for(unsigned int j = 0; j< dataB.stopTimesTable[trip_num][stop_num].size(); j++){

						if(dataB.stopTimesTable[trip_num][stop_num-1][i] < dataB.stopTimesTable[trip_num][stop_num][j]){
							newEdge->addConnection(dataB.stopTimesTable[trip_num][stop_num-1][i], dataB.stopTimesTable[trip_num][stop_num][j],trip_num);
							break;
			unsigned int startNodeId = stopSec[stop -1];
			unsigned int endNodeId = stopSec[stop];
			unsigned int edgeId = calculateEdgeId(startNodeId, endNodeId);

			if(!getEdge(edgeId)){
				Node* startNode = getNode(startNodeId);
				Node* endNode = getNode(endNodeId);
				Edge* newEdge = new Edge(edgeId,startNode,endNode);
				for(Time t1: stopTimesTable[trip.getId()][stop-1]){
					for(Time t2: stopTimesTable[trip.getId()][stop]){
						if(t1<t2){
							newEdge->addConnection(t1,t2,trip.getId());
						}
					}
				}
				this->addEdge(newEdge);
			}else{
				Edge* existingEdge = getEdge(edgeId);
				for(Time t1: stopTimesTable[trip.getId()][stop-1]){
					for(Time t2: stopTimesTable[trip.getId()][stop]){
						if(t1<t2){
							existingEdge->addConnection(t1,t2,trip.getId());
						}
					}
				}
			}

		}
	}

	std::cerr<<"Network::Network(DataBase& dataB): edges done, network contains "<<this->edges.size()<<" edges"<<std::endl;

	createIncidenceMatrix();

	unsigned int numNodes = this->nodes.size();
	for(unsigned int i = 0; i < numNodes; i++){
		for(unsigned int j = 0; j < numNodes; j++){
			if(incidenceMatrix[i][j])
				std::cout<<1<<" ";
			else
				std::cout<<0<<" ";
		}
		std::cout<<std::endl;
	}

	std::cerr<<"Network::Network(DataBase& dataB): network created"<<std::endl;
}

Network::~Network() {

	for(Node* n: this->nodes){
		if(n != NULL) delete n;
	}

	for(Edge* e: this->edges){
		if(e != NULL) delete e;
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

Route* Network::findRouteBetween(Node * start, Node * end, const unsigned int maxSwitches) {
	return this->solver->solve(this,start,end);
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
	Node * tempNode = new Node(id, "temp", 0, 0);

	auto it = this->nodes.find(tempNode);

	if(it == this->nodes.end()){
		return NULL;
	}else{
		delete tempNode;
		return *it;
	}
}

Edge* Network::getEdge(unsigned int id) const {
	Edge * tempEdge = new Edge(id, NULL, NULL);

	auto it = this->edges.find(tempEdge);

	if(it == this->edges.end()){
		return NULL;
	}else{
		delete tempEdge;
		return *it;
	}
}

std::list<Edge *> Network::getEdgesForNode(const Node* n) const {
	std::list<Edge *> found;
	for(Edge * e: this->edges)
		if(*(e->getStartNode()) == *n)
			found.push_back(e);

	return found;
}

std::list<Node*> Network::getAllNodes()const{
	std::list<Node *> nodes;
	for(Node * n: this->nodes)
	{
		nodes.push_back(n);
	}
	return nodes;
}

std::list<Edge *> Network::getAllEdges()const{
	std::list<Edge *> edges;
	for(Edge * e: this->edges)
	{
		edges.push_back(e);
	}
	return edges;
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
	return startId + (this->nodes.size()+1)*endId;
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





