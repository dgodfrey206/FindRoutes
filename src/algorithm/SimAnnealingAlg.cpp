/*
 * SimAnnealingAlg.cpp
 *
 *  Created on: 19 lis 2014
 *      Author: Wojtek Gumuła
 */

#include "SimAnnealingAlg.h"
#include <cmath>

const std::string SimAnnealingAlg::name = "Simulated annealing";

SimAnnealingAlg::SimAnnealingAlg()
	:
	Tstart(1000),
	Tend(100),
	k(100),
	alpha(0.999)
{
	this->distribution = std::uniform_real_distribution<>(0.0, 1.0);
	this->generator = std::default_random_engine(100); //todo constant seed for debug
}

SimAnnealingAlg::~SimAnnealingAlg()
{

}

Route* SimAnnealingAlg::solve(const Network * n, Node * start, Node * end, Time time) {

	//k - number of iteration
	//Tstart - starting temperature
	//Tend - ending temperature
	//T - current temperature
	//alfa - T = alfa * T for every iteration
	this->weights.clear();

	Time t = time;
	double T = this->Tstart;
	Route * currentSolution = this->getFistSolution(n, start, end);
	unsigned int currentWeight = currentSolution->getWeight(t);
	while(T>this->Tend){
		for(unsigned int i=0; i<k; i++){	//repeat k times
			Route * newR =this->getRouteInSurroundings(n,currentSolution);		//get new solution and new weight
			unsigned int newWeight = newR->getWeight(t);
			int delta = int(newWeight) - int(currentWeight);

			if(delta <0){	//if solution is better tha current
				currentSolution = newR;
				currentWeight = newWeight;
			}else{
				if( this->getRandom() < std::exp(double((-1)*delta) / double(T)) ){
					currentSolution = newR;
					currentWeight = newWeight;
				}
			}
		}
		T *= this->alpha;
		this->weights.push_back(currentWeight);
	}

	return currentSolution;
}

const std::string & SimAnnealingAlg::getName() const {
	return this->name;
}

double SimAnnealingAlg::getRandom(unsigned i) {
	return i * this->distribution(this->generator);
}

void SimAnnealingAlg::setParams(double Tstart, double Tend, unsigned int k, double alpha) {
	this->Tstart = Tstart;
	this->Tend = Tend;
	this->k = k;
	this->alpha = alpha;
}

std::vector<unsigned> SimAnnealingAlg::getWeights() const {
	return this->weights;
}

Route* SimAnnealingAlg::getFistSolution(const Network* n, Node* start, Node* end) {

	Node * currentNode = start;

	std::vector<Node *> stack;
	std::vector<Edge *> route;
	std::vector<Node *> ignored;


	while(*currentNode != *end)
	{
		std::list<Edge *> edgesForNode = n->getEdgesForNode(currentNode);

		//search all edges and select one closest to end node
		double closestDist = std::numeric_limits<double>::max();
		Edge * closestNodeEdge = NULL;

		for(Edge * e: edgesForNode)
		{
			//skip visited nodes:
			bool isIgnored = false;

			for(Node * n: stack)
			{
				if(*n == (*e->getEndNode()))
				{
					isIgnored = true;
					break;
				}
			}
			for(Node * n: ignored)
			{
				if(*n == (*e->getEndNode()))
				{
					isIgnored = true;
					break;
				}
			}
			if(isIgnored) continue;

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
			stack.push_back(currentNode);
			route.push_back(closestNodeEdge);

			currentNode = n->getNode(closestNodeEdge->getEndNode()->getID());
		}
		else
		{
			if(stack.size() == 0) return NULL;

			ignored.push_back(currentNode);

			currentNode = stack.back();
			stack.pop_back();
			route.pop_back();


		}
	}

	Route * r = new Route;
	for(Edge * e: route) r->addEdge(e);
	if(r->validate()) return r;

	std::cerr << "Created route is invalid";
	std::cerr << *r << std::endl;
	return NULL;
}

Route* SimAnnealingAlg::getRouteInSurroundings(const Network* net, Route* r) {

	//select two nodes and recreate connection between them.

	std::vector<const Node *> nodes;
	for(auto it = r->begin(); it != r->end(); it++)
	{
		nodes.push_back((*it)->getEndNode());
	}
	nodes.pop_back(); //remove ending node
	std::random_shuffle(nodes.begin(), nodes.end());

	Route * newRoute = NULL;

	while(newRoute == NULL && nodes.size() > 0)
	{
		const Node * n = nodes.back();
		nodes.pop_back(); //get random node from list

		//first, try to remove node from route, then, if failed, adding node in front or back of given to route
		//locate node in route
		auto it = r->begin();
		decltype(it) inEdgeIt;
		decltype(it) outEdgeIt;

		for(; it != r->end(); it++)
		{

			if(*((*it)->getEndNode()) == *n)
			{
				inEdgeIt = it;
			}
			else if(*((*it)->getStartNode()) == *n)
			{
				outEdgeIt = it;
			}
		}

		const Node * startNode = (*inEdgeIt)->getStartNode();
		const Node * endNode = (*outEdgeIt)->getEndNode();

		//try removing
		if(net->isEdgeBetween(startNode, endNode))
		{
			//get that edge and return new Route
			unsigned edgeID = net->calculateEdgeId(startNode->getID(), endNode->getID());
			const Edge * newEdge = net->getEdge(edgeID);

			Route * newRoute = new Route(*r);

			newRoute->switchEdge(newEdge);

			return newRoute;
		}

		//try adding
		std::list<Edge *> startNodeEdges = startNode->getEdges();

		for(Edge * e: startNodeEdges)
		{
//			std::cout << "t81" << std::endl;
			if(net->isEdgeBetween(e->getEndNode(), n))
			{
				unsigned edgeID = net->calculateEdgeId(e->getEndNode()->getID(), n->getID());
				const Edge * newEdge = net->getEdge(edgeID);

				if(r->isEdgeIn(newEdge)) continue;

				Route * newR = new Route;
				newR->addEdge(e);
				newR->addEdge(newEdge);

				Route * newRoute = new Route(*r);

				if(newRoute->switchRoute(*newR) && newRoute->validate())
				{
					return newRoute;
				}
			}
		}
		std::list<Edge *> endNodeEdges = endNode->getEdges();
		for(Edge * e: endNodeEdges)
		{
			if(net->isEdgeBetween(n, e->getStartNode()))
			{
				unsigned edgeID = net->calculateEdgeId(n->getID(), e->getStartNode()->getID());
				const Edge * newEdge = net->getEdge(edgeID);

				if(r->isEdgeIn(newEdge)) continue;

				Route * newR = new Route;
				newR->addEdge(newEdge);
				newR->addEdge(e);

				Route * newRoute = new Route(*r);

				if(newRoute->switchRoute(*newR) && newRoute->validate())
				{
					return newRoute;
				}
			}
		}
	}

	return newRoute;
}
