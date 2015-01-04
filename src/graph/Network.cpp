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

bool Network::validate() {
	bool isValid = true;
	for(Node * n: this->nodes)
	{
		if(n == NULL)
		{
			std::cerr << "Null node." << std::endl;
			isValid = false;
		}
	}
	for(Edge * e: this->edges)
	{
		if(e == NULL)
		{
			std::cerr << "Null edge." << std::endl;
			isValid = false;
		}
		else
		{
			if(e->getEndNode() == NULL || e->getStartNode() == NULL)
			{
				std::cerr << "Null node in edge at address " << e << std::endl;
				isValid = false;
			}
		}
	}
	return isValid;
}

Network* Network::generateRandomNetwork(unsigned width, unsigned height,
		long seed, double probability)
{
	std::srand(seed);

	Network * network = new Network();
	Node * tempNode = NULL;
	Edge * tempEdge = NULL;

	std::cout << "generateRandomNetwork: Generating nodes" << std::endl;
	for(unsigned i = 0; i < height; i++)
	{
		for(unsigned j = 0; j < width; j++)
		{
			if(std::rand() < probability * RAND_MAX)
			{
				tempNode = new Node(width * i + j, std::to_string(width * i + j), 0.02 * j, 0.02 * i);
				network->addNode(tempNode);
			}
		}
	}

	/*
	 * add edges between nodes in style:
	 * 1 | 2 | 3
	 * ---------
	 * 4 | 5 | 6
	 * ---------
	 * 7 | 8 | 9
	 *
	 * For node 5, add connections to 2, 4, 6 and 8, for 1: to 2 and 4.
	 *
	 * For graph:
	 * 1 | 2 | 3 | 4
	 * -------------
	 * 5 | 6 | e | 8
	 * --------------
	 * 9 | 10| 11| 12
	 * For node 6: to 2, 5, 8 and 9, for node 3: to 2, 4, 11.
	 */

	unsigned currentEdgeID = 0;
	std::cout << "generateRandomNetwork: Generating edges" << std::endl;
	for(auto n : network->getAllNodes())
	{
		unsigned id = n->getID();
		//top
		if(id >= width) //not first row
		{
			unsigned searchedID = id;
			Node * searchedNode = NULL;

			do
			{
				searchedID -= width;
				searchedNode = network->getNode(searchedID);
			}
			while(searchedNode == NULL && searchedID >= width && searchedID < width * height);

			if(searchedNode != NULL)
			{
				//create edge
				tempEdge = NULL;
				currentEdgeID = network->calculateEdgeId(n->getID(), searchedNode->getID());
				tempEdge = new Edge(currentEdgeID, n, searchedNode);
				if(tempEdge != NULL) network->addEdge(tempEdge);
			}
		}

		//bottom
		if(id < width * (height - 1)) //not last row
		{
			unsigned searchedID = id;
			Node * searchedNode = NULL;

			do
			{
				searchedID += width;
				searchedNode = network->getNode(searchedID);
			}
			while(searchedNode == NULL && searchedID <= (width * (height - 1) - 1));

			if(searchedNode != NULL)
			{
				//create edge
				tempEdge = NULL;
				currentEdgeID = network->calculateEdgeId(n->getID(), searchedNode->getID());
				Edge * tempEdge = new Edge(currentEdgeID, n, searchedNode);
				if(tempEdge != NULL) network->addEdge(tempEdge);
			}
		}

		//left
		if(id % width != 0) //not first column
		{
			unsigned searchedID = id;
			Node * searchedNode = NULL;

			do
			{
				searchedID--;
				searchedNode = network->getNode(searchedID);
			}
			while(searchedNode == NULL && searchedID > (id - (id % width)) && searchedID < width * height);

			if(searchedNode != NULL)
			{
				//create edge
				tempEdge = NULL;
				currentEdgeID = network->calculateEdgeId(n->getID(), searchedNode->getID());
				Edge * tempEdge = new Edge(currentEdgeID, n, searchedNode);
				if(tempEdge != NULL) network->addEdge(tempEdge);
			}
		}

		//right
		if(id % width != width - 1) //not last column
		{
			unsigned searchedID = id;
			Node * searchedNode = NULL;

			do
			{
				searchedID++;
				searchedNode = network->getNode(searchedID);
			}
			while(searchedNode == NULL && searchedID < (id - (id % width) + width - 1));

			if(searchedNode != NULL)
			{
				//create edge
				tempEdge = NULL;
				currentEdgeID = network->calculateEdgeId(n->getID(), searchedNode->getID());
				Edge * tempEdge = new Edge(currentEdgeID, n, searchedNode);
				if(tempEdge != NULL) network->addEdge(tempEdge);
			}
		}
	}

	//manage trips
	unsigned tripID = 0;
	unsigned currentStop = 0;
	const unsigned drivingTime = 2;

	Node * start = NULL;
	Node * end = NULL;
	Node * temp = NULL;

	//top-bottom
	std::cout << "generateRandomNetwork: Generating trips, top-bottom" << std::endl;
	for(unsigned i = 0; i < width; i++)
	{
		currentStop = 0;
		start = end = temp = NULL;

		unsigned currentNodeID = i;
		do
		{
			if((temp = network->getNode(currentNodeID)) != NULL)
			{
				start = end;
				end = temp;

				if(start != NULL && end != NULL)
				{
					//locate proper edge:
					Edge * edgeBetween = NULL;

					for(auto e: start->getEdges())
					{
						if(e->getEndNode() == end)
						{
							edgeBetween = e;
							break;
						}
					}

					//populate connections
					if(edgeBetween != NULL)
					{
						for(unsigned t = 8; t < 44; t++) //trip every half an hour, from 4 to 22.
						{
							edgeBetween->addConnection(Time(30 * t + currentStop * drivingTime),
									Time(30 * t + (currentStop + 1) * drivingTime), tripID);
						}
						currentStop++;
					}
				}
			}

			currentNodeID += width;

		}
		while(currentNodeID < width * height);

		tripID++;
	}

	//bottom-top
	std::cout << "generateRandomNetwork: Generating trips, bottom-top" << std::endl;
	for(unsigned i = 0; i < width; i++)
	{
		currentStop = 0;
		start = end = temp = NULL;

		unsigned currentNodeID = width * (height - 1) + i;
		do
		{
			if((temp = network->getNode(currentNodeID)) != NULL)
			{
				start = end;
				end = temp;

				if(start != NULL && end != NULL)
				{
					//locate proper edge:
					Edge * edgeBetween = NULL;

					for(auto e: start->getEdges())
					{
						if(e->getEndNode() == end)
						{
							edgeBetween = e;
							break;
						}
					}
					//populate connections
					if(edgeBetween != NULL)
					{
						for(unsigned t = 8; t < 44; t++) //trip every half an hour, from 4 to 22.
						{
							edgeBetween->addConnection(Time(30 * t + currentStop * drivingTime),
									Time(30 * t + (currentStop + 1) * drivingTime), tripID);
						}
						currentStop++;
					}
				}
			}

			currentNodeID -= width;

		}
		while(currentNodeID >= 0 && currentNodeID < width * height);

		tripID++;
	}


	//left-right
	std::cout << "generateRandomNetwork: Generating trips, left-right" << std::endl;
	for(unsigned i = 0; i < height; i++)
	{
		currentStop = 0;
		start = end = temp = NULL;

		unsigned currentNodeID = i * width;
		do
		{
			if((temp = network->getNode(currentNodeID)) != NULL)
			{
				start = end;
				end = temp;

				if(start != NULL && end != NULL)
				{
					//locate proper edge:
					Edge * edgeBetween = NULL;

					for(auto e: start->getEdges())
					{
						if(e->getEndNode() == end)
						{
							edgeBetween = e;
							break;
						}
					}

					//populate connections
					if(edgeBetween != NULL)
					{
						for(unsigned t = 8; t < 44; t++) //trip every half an hour, from 4 to 22.
						{
							edgeBetween->addConnection(Time(30 * t + currentStop * drivingTime),
									Time(30 * t + (currentStop + 1) * drivingTime), tripID);
						}
						currentStop++;
					}
				}
			}

			currentNodeID++;

		}
		while(currentNodeID < (i + 1) * width);

		tripID++;
	}

	//right-left
	std::cout << "generateRandomNetwork: Generating trips, right-left" << std::endl;
	for(unsigned i = 0; i < height; i++)
	{
		currentStop = 0;
		start = end = temp = NULL;

		unsigned currentNodeID = (i + 1) * width - 1;
		do
		{
			if((temp = network->getNode(currentNodeID)) != NULL)
			{
				start = end;
				end = temp;

				if(start != NULL && end != NULL)
				{
					//locate proper edge:
					Edge * edgeBetween = NULL;

					for(auto e: start->getEdges())
					{
						if(e->getEndNode() == end)
						{
							edgeBetween = e;
							break;
						}
					}

					//populate connections
					if(edgeBetween != NULL)
					{
						for(unsigned t = 8; t < 44; t++) //trip every half an hour, from 4 to 22.
						{
							edgeBetween->addConnection(Time(30 * t + currentStop * drivingTime),
									Time(30 * t + (currentStop + 1) * drivingTime), tripID);
						}
						currentStop++;
					}
				}
			}

			currentNodeID--;

		}
		while(currentNodeID >= i * width && currentNodeID < width * height);

		tripID++;
	}

	network->createIncidenceMatrix();
	return network;
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

	std::cerr<<"Network::Network(DataBase& dataB): creating network from database"<<std::endl;
	std::cerr<<"Network::Network(DataBase& dataB): creating nodes"<<std::endl;
	for(unsigned int i=0; i<dataB.stops.size(); i++){
		Node* new_node = NULL;
		new_node = new Node(dataB.stops[i].getId(),dataB.stops[i].getName(),dataB.stops[i].getLat(), dataB.stops[i].getLng());
		if(new_node) this->addNode(new_node);
	}
	std::cerr<<"Network::Network(DataBase& dataB): nodes done, network contains "<<this->nodes.size()<<" nodes"<<std::endl;

	std::cerr<<"Network::Network(DataBase& dataB): connecting times with stop sequences"<<std::endl;
	std::vector<std::vector<std::vector<Time>>>	stopTimesTable;

//	for(unsigned int trip_id=0; trip_id<dataB.trips.size(); trip_id++){
//		std::vector<std::vector<Time>> _stops_in_sec;
//		for(unsigned int stop=0; stop<dataB.trips[trip_id].getStopSec().size();stop++){
//			unsigned int stop_id = (dataB.trips[trip_id].getStopSec()[stop]);
//			std::vector<Time> _times;
//			for(unsigned int stop_time=0; stop_time< dataB.stopTimes.size();stop_time++){
//				if( (dataB.stopTimes[stop_time].getServiceId() == 0) 	&&
//					(dataB.stopTimes[stop_time].getStopId() == stop_id) &&
//					(dataB.stopTimes[stop_time].getTripId() == trip_id)){
//						_times.push_back(dataB.stopTimes[stop_time].getStopTime());
//				}
//			}
//			_stops_in_sec.push_back(_times);
//		}
//		stopTimesTable.push_back(_stops_in_sec);
//	}

	stopTimesTable = dataB.timeTable;

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
							break;
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
							break;
						}
					}
				}
			}

		}
	}

	std::cerr<<"Network::Network(DataBase& dataB): edges done, network contains "<<this->edges.size()<<" edges"<<std::endl;

	createIncidenceMatrix();

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

void Network::setSolver(Solver * s) {
	if(s != NULL && s != this->solver)
	{
		delete this->solver;
		this->solver = s;
	}
}

Route* Network::findRouteBetween(Node * start, Node * end, Time t) {
	return this->solver->solve(this,start,end, t);
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
	e->getStartNode()->addEdge(e);
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
	/*std::list<Edge *> found;
	for(Edge * e: this->edges)
		if(*(e->getStartNode()) == *n)
			found.push_back(e);

	return found;*/
	return n->getEdges();
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

unsigned int Network::calculateEdgeId(unsigned int startId, unsigned int endId) const{
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
void Network::limitRandomly(unsigned size, long seed) {
	if(this->nodes.size() <= size) return;

	//prepare list od nodes ids and shuffle it
	std::vector<unsigned> ids = {};
	for(auto n: this->nodes) ids.push_back(n->getID());

	std::srand(seed);
	std::random_shuffle(ids.begin(), ids.end());

	//reset incidenceMatrix
	for(unsigned i = 0; i < this->nodes.size(); i++)
	{
		for(unsigned j = 0; j < this->nodes.size(); j++) this->incidenceMatrix[i][j] = false;
	}


	//save toMantain number of elements and corresponding edges.
	std::set<Node *, nodePointerCompare> newNodes;
	std::set<Edge *, edgePointerCompare> newEdges;

	for(unsigned i = 0; i < size; i++)
	{
		newNodes.insert(this->getNode(ids[i]));
	}

	for(auto n: newNodes)
	{
		for(auto e: n->getEdges())
		{
			if(newNodes.find(e->getEndNode()) != newNodes.end())
			{
				this->incidenceMatrix[n->getID()][e->getEndNode()->getID()] = true;
				newEdges.insert(e);
			}
		}
	}
	this->nodes.clear();
	this->edges.clear();

	this->nodes = newNodes;
	this->edges = newEdges;
	//todo remove unused resources
}
