/*
 * SimAnnealingAlg.cpp
 *
 *  Created on: 19 lis 2014
 *      Author: Wojtek Gumuła
 */

#include "SimAnnealingAlg.h"
#include "BSFR.h"
#include <cmath>
#include <algorithm>

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
	//std::vector<unsigned int> vec;
	this->weights.clear();

	Time t = time;
	double T = this->Tstart;
	Route * currentSolution = this->getFistSolution(n, start, end);
	//Route * best;
	//unsigned int bestWeight =10000;
	unsigned int currentWeight = currentSolution->getWeight(t);
	unsigned int iteration=0;
	while(T>this->Tend){
		for(unsigned int i=0; i<k; i++){	//repeat k times
			iteration++;
			Route * newR =this->getRouteInSurroundings(n,currentSolution);		//get new solution and new weight
			unsigned int newWeight = newR->getWeight(t);


			//if(newWeight < bestWeight){
			//	bestWeight = newWeight;
			//	best = newR;
			//}
			//auto g = std::find(vec.begin(), vec.end(),newWeight);
			//if( g== vec.end()) vec.push_back(newWeight);

			int delta = int(newWeight) - int(currentWeight);

			if(delta <=0){	//if solution is better tha current
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
		//std::cerr << "iteration " << iteration << " temperature "<< T << " weight "<< currentWeight <<std::endl;
		this->weights.push_back(currentWeight);
	}
	//std::cerr << "wieghts founds: "<<vec.size()<<std::endl;
	//std::cerr << "best weight " << bestWeight << std::endl;
	//Route::printRoute(std::cerr,best,t);
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

	Route* result = NULL;
	BsfRandAlg alg;

	auto startEdge = r->begin();
	auto endEdge = --r->end();

	auto startNode = (*startEdge)->getStartNode();
	auto endNode = (*endEdge)->getEndNode();
	//std::cout << startNode->getName() << " -> "<<endNode->getName()<<std::endl;
	result = alg.solve(net,startNode,endNode,Time(0,0));
	return result;

	/*
	if((r != NULL) && (r->getLength() != 0)){
		unsigned int routeLength = r->getLength();
		if(routeLength){
			BsfRandAlg alg;

			unsigned int firstEdgeNumber, secondEdgeNumber;
			firstEdgeNumber = rand() % routeLength;
			secondEdgeNumber = rand() % routeLength;
			while(firstEdgeNumber == secondEdgeNumber){
				secondEdgeNumber = rand() % routeLength;
			}
			if(firstEdgeNumber>secondEdgeNumber){
				unsigned int temp;
				temp = secondEdgeNumber;
				secondEdgeNumber = firstEdgeNumber;
				firstEdgeNumber = temp;
			}

			std::cout << routeLength << " " << firstEdgeNumber << "  " <<secondEdgeNumber<<std::endl;

			auto startEdge = r->begin();
			auto endEdge = r->begin();

			while(firstEdgeNumber--){
				startEdge++;
			}

			while(secondEdgeNumber--){
				endEdge++;
			}

			auto startNode = (*startEdge)->getStartNode();
			auto endNode = (*endEdge)->getEndNode();

			std::cout << startNode->getName() << " -> "<<endNode->getName()<<std::endl;
			Route* solverResult = alg.solve(net,startNode,endNode,Time(0,0));

			if((solverResult != NULL) && (solverResult->getLength() != 0)){
				if(r->switchRoute(*solverResult)) result = r;
			}
		}
	}*/

}
