/*
 * SimAnnealingAlg.cpp
 *
 *  Created on: 19 lis 2014
 *      Author: Wojtek Gumuła
 */

#include "SimAnnealingAlg.h"

const std::string SimAnnealingAlg::name = "Simulated annealing";

SimAnnealingAlg::SimAnnealingAlg()
	:
	Tstart(1000),
	Tend(100),
	k(100),
	alpha(0.999)
{
	this->distribution = std::uniform_real_distribution<>(0.0, 1.0);
	this->generator = std::default_random_engine(8); //todo constant seed for debug
}

SimAnnealingAlg::~SimAnnealingAlg()
{

}

Route* SimAnnealingAlg::solve(const Network * n, Node * start, Node * end) {

	//k - number of iteration
	//T0 - starting temperature
	//T - current temperature
	//alfa - T = alfa * T for every iteration
	Route * bestKnown = NULL;
//	double bestKnownWeight = -1;

	//get starting solution

	Route * currentSolution = this->getFistSolution(n, start, end);
	bestKnown = currentSolution;
//	bestKnownWeight = currentSolution->getWeight();

	return bestKnown;
}

const std::string & SimAnnealingAlg::getName() const {
	return this->name;
}

double SimAnnealingAlg::getRandom(unsigned i) {
	return i * this->distribution(this->generator);
}

void SimAnnealingAlg::setParams(double Tstart, double Tend, double k, double alpha) {
	this->Tstart = Tstart;
	this->Tend = Tend;
	this->k = k;
	this->alpha = alpha;
}

Route* SimAnnealingAlg::getFistSolution(const Network* n, Node* start, Node* end) {
	std::cerr << "getFistSolution called" << std::endl;

	Node * currentNode = start;
	Route * route = new Route;

	std::vector<Node *> visited;

	while(*currentNode != *end)
	{
		visited.push_back(currentNode);

		std::cerr << " while loop" << std::endl;
		std::cerr << " current node: " << *currentNode << std::endl;
		std::list<Edge *> edgesForNode = n->getEdgesForNode(currentNode);
		std::cerr << " Edges for node: " << edgesForNode.size() << std::endl;

		//search all edges and select one closest to end node
		double closestDist = 0;
		Edge * closestNodeEdge = NULL;

		for(Edge * e: edgesForNode)
		{
			//skip visited nodes:
			bool isVisited = false;
			for(Node * n: visited)
			{
				if(*n == (*e->getEndNode()))
				{
					isVisited = true;
					break;
				}
			}
			if(isVisited) continue;

			double distance = sqrt(pow(e->getEndNode()->getLatitude() - end->getLatitude(), 2)
					+ pow(e->getEndNode()->getLongtitude() - end->getLongtitude(), 2));
			if(closestNodeEdge == NULL || distance < closestDist)
			{
				closestNodeEdge = e;
				closestDist = distance;
			}
		}

		if(closestNodeEdge != NULL)
		{
			std::cerr <<"found closest node: " << *(closestNodeEdge->getEndNode()) << std::endl;
			route->addEdge(closestNodeEdge);
		}
		else
		{
			std::cerr << " closest node edge is null" << std::endl;
		}

		currentNode = n->getNode(closestNodeEdge->getEndNode()->getID());
	}

	std::cerr << "getFistSolution finished" << std::endl;
	return route;
}

Route* SimAnnealingAlg::getRouteInSurroundings(const Network* net, Route* r) {
	std::cerr << "getRouteInSurroundings called" << std::endl;

	//select two nodes and recreate connection between them.

	std::vector<const Node *> nodes;
	for(auto it = r->begin(); it != r->end(); it++)
	{
		nodes.push_back((*it)->getEndNode());
	}
	nodes.pop_back(); //remove ending node
	std::random_shuffle(nodes.begin(), nodes.end());

	Route * newRoute = NULL;

	while(newRoute == NULL)
	{
		std::cout << "t1" << std::endl;
		const Node * n = nodes.back();
		nodes.pop_back(); //get random node from list

		std::cout << "t2" << std::endl;
		//decide what to do first
		//first, try to remove node from route, then, if failed, adding node in front or back of given to route

		std::cout << "t3" << std::endl;
		//locate node in route
		auto it = r->begin();
		decltype(it) inEdgeIt;
		decltype(it) outEdgeIt;
		std::cout << "t4" << std::endl;
		for(; it != r->end(); it++)
		{
			std::cout << "t41" << std::endl;
			std::cout << *(*it) << std::endl;
			if(*((*it)->getEndNode()) == *n)
			{
				std::cout << "t411" << std::endl;
				inEdgeIt = it;
			}
			else if(*((*it)->getStartNode()) == *n)
			{
				std::cout << "t412" << std::endl;
				outEdgeIt = it;
			}
			std::cout << "t42" << std::endl;
		}
		std::cout << "t5" << std::endl;
		const Node * startNode = (*inEdgeIt)->getStartNode();
		const Node * endNode = (*outEdgeIt)->getEndNode();
		std::cout << "t6" << std::endl;
		if(net->isEdgeBetween(startNode, endNode))
		{
			std::cout << "t61" << std::endl;
			//get that edge and return new Route
			unsigned edgeID = net->calculateEdgeId(startNode->getID(), endNode->getID());
			const Edge * newEdge = net->getEdge(edgeID);
			Route * newRoute = new Route(*r);
			newRoute->switchEdge(newEdge);
			std::cout << "t62" << std::endl;
			return newRoute;
		}
		std::cout << "t7" << std::endl;



	}

	return newRoute;
}
