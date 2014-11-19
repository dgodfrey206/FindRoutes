/*
 * SimAnnealingAlg.cpp
 *
 *  Created on: 19 lis 2014
 *      Author: Wojtek Gumuła
 */

#include "SimAnnealingAlg.h"

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

Route* SimAnnealingAlg::solve(const Network * n, const Node * start, const Node * end) {

	//k - number of iteration
	//T0 - starting temperature
	//T - current temperature
	//alfa - T = alfa * T for every iteration
	Route * bestKnown;
	double bestKnownWeight;

	//get starting solution

	Route * currentSolution = this->getFistSolution(n, start, end);


	return bestKnown;
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

double SimAnnealingAlg::getAzimuth(Node* from, Node* to, Node * marker) {
	//compute cosine of angle between two vectors, [from, marker] and [from, to]
	double lenASq, lenBSq, lenCSq;
	lenBSq = pow((from->getLatitude() - to->getLatitude()), 2) - pow((from->getLongtitude() - to->getLongtitude()), 2);
	lenASq = pow((from->getLatitude() - marker->getLatitude()), 2) - pow((from->getLongtitude() - marker->getLongtitude()), 2);
	lenCSq = pow((marker->getLatitude() - to->getLatitude()), 2) - pow((marker->getLongtitude() - to->getLongtitude()), 2);

	return (lenASq + lenBSq + lenCSq)/(2 * pow(lenASq, 0.5) * pow(lenBSq, 0.5));
}

Route* SimAnnealingAlg::getFistSolution(const Network* n, const Node* start, const Node* end) {
	Node * currentNode = start;
	Route * route = new Route;

	while(*currentNode != *end)
	{

	}
}
