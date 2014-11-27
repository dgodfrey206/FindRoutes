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
	double bestKnownWeight = -1;

	//get starting solution

	Route * currentSolution = this->getFistSolution(n, start, end);
	bestKnown = currentSolution;
	bestKnownWeight = currentSolution->getWeight();

	return bestKnown;
}

const std::string & SimAnnealingAlg::getName() const {
	return this->name;
}

double SimAnnealingAlg::getRandom() {
	return this->distribution(this->generator);
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
