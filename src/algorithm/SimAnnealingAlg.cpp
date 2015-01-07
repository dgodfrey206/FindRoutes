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
	alpha(0.999),
	allowedChangeNumber(10),
	changePunishment(50)
{
	this->setSeed(0);
}

SimAnnealingAlg::SimAnnealingAlg(long long seed)
	:
	Tstart(1000),
	Tend(100),
	k(100),
	alpha(0.999),
	allowedChangeNumber(10),
	changePunishment(50)
{
	this->setSeed(seed);
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
	this->bestPosWeights.clear();
	this->punishments.clear();

	Time t = time;
	double T = this->Tstart;
	Route * currentSolution = this->getFistSolution(n, start, end);
	unsigned int currentWeight = currentSolution->getWeight(t);

	Route * bestPossible = NULL;
	unsigned bestPossibleWeight = std::numeric_limits<unsigned>::max();

	while(T>this->Tend){
		std::cout << "Current temperature: " << T << " (" << Tstart << " : " << Tend << ")" << std::endl;

		for(unsigned int i=0; i<k; i++)
		{	//repeat k times

			Route * newR =this->getRouteInSurroundings(n,currentSolution);		//get new solution and new weight
			unsigned int newWeight = newR->getWeight(t);
			unsigned int changeNumber = newR->getChangeNumber(t);
			bool isPossible = true; //determines if number of changes is not greater than permited

			if( changeNumber > allowedChangeNumber)
			{
				newWeight += (changeNumber - allowedChangeNumber) * changePunishment;
				isPossible = false;
			}

			int delta = int(newWeight) - int(currentWeight);

			if(delta <=0 || (this->getRandom() < std::exp(double((-1)*delta) / double(T))))
			{	//if solution is better tha current
				currentSolution = newR;
				currentWeight = newWeight;

				if(isPossible && currentWeight < bestPossibleWeight)
				{
					bestPossible = currentSolution;
					bestPossibleWeight = currentWeight;
				}
			}
		}
		T *= this->alpha;
		this->weights.push_back(currentWeight);
		unsigned changes = currentSolution->getChangeNumber(t);
		if(changes > allowedChangeNumber) this->punishments.push_back((changes - allowedChangeNumber) * changePunishment);
		else this->punishments.push_back(0);

		this->bestPosWeights.push_back(bestPossibleWeight);
	}
	return bestPossible;
}

const std::string & SimAnnealingAlg::getName() const {
	return this->name;
}

double SimAnnealingAlg::getRandom(unsigned i) {
	return i * this->distribution(this->generator);
}

void SimAnnealingAlg::setParams(double Tstart, double Tend, unsigned int k, double alpha, unsigned int allowedChangeNumber, unsigned int changePunishment){
	this->Tstart = Tstart;
	this->Tend = Tend;
	this->k = k;
	this->alpha = alpha;
	this->allowedChangeNumber = allowedChangeNumber;
	this->changePunishment = changePunishment;
}

std::vector<unsigned> SimAnnealingAlg::getWeights() const {
	return this->weights;
}

std::vector<unsigned> SimAnnealingAlg::getPunishments() const {
	return this->punishments;
}
std::vector<unsigned> SimAnnealingAlg::getBestPosWeights() const {
	return this->bestPosWeights;
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
		//double closestDist = std::numeric_limits<double>::max();
		Edge * closestNodeEdge = NULL;

		std::vector<Edge *> possible;
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

			/*double distance = sqrt(pow(e->getEndNode()->getLatitude() - end->getLatitude(), 2)
					+ pow(e->getEndNode()->getLongtitude() - end->getLongtitude(), 2));

			if(closestNodeEdge == NULL || distance < closestDist)
			{
				closestNodeEdge = e;
				closestDist = distance;
			}*/
			possible.push_back(e);
		}
		if(possible.size() > 0)
		{
			closestNodeEdge = possible[this->getRandom(possible.size())];
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
}

void SimAnnealingAlg::setSeed(long long seed)
{
	this->distribution = std::uniform_real_distribution<>(0.0, 1.0);
	this->generator = std::default_random_engine(seed);
}
