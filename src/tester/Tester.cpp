/*
 * Tester.cpp
 *
 *  Created on: 15 Oct 2014
 *      Author: David Godfrey
 */

#include "Tester.h"

Tester::Tester(Network * n):
	network(n){
	this->TStart = 100;
	this->TEnd = 1;
	this->k = 10;
	this->alpha = 0.99;
	this->allowedChanges = 3;
	this->changePunishment = 50;

	this->solver = NULL;

	this->time = Time(600);

	this->from = NULL;
	this->to = NULL;

	this->seed = 0;

	this->directory = "";
}

Tester::~Tester() {
}

void Tester::makeTests(Node * f, Node * t, std::string dir, long long seed) {
	if(this->network == NULL) return;

	if(this->solver == NULL)
	{
		this->solver = new SimAnnealingAlg(seed);
		this->network->setSolver(this->solver);
	}

	this->from = f;
	this->to = t;

    if(this->from == NULL) this->from = this->network->getNode(std::rand() * this->network->getAllNodes().size());
    if(this->to == NULL) this->to = this->network->getNode(std::rand() * this->network->getAllNodes().size());

	this->directory = dir;
	if(this->directory[this->directory.size()-1] != '/') this->directory += "/";

	this->seed = seed;

	this->variableAlphaTest();
	this->variableChangesTest();
	this->variableKTest();
	this->variablePunishmentTest();
	this->variableTempTest();
}

void Tester::variableKTest() {
	std::vector<unsigned> possibleK = { 1, 10, 50, 100 };


	for(auto k: possibleK)
	{
		this->solver->setSeed(this->seed);

		this->solver->setParams(this->TStart, this->TEnd, k, this->alpha, this->allowedChanges, this->changePunishment);

		Route * solution = this->solver->solve(this->network, this->from, this->to, this->time);

		if(solution != NULL)
		{
			auto weights = this->solver->getWeights();
			auto punishmets = this->solver->getPunishments();
			auto bestWeights = this->solver->getBestPosWeights();

			std::ofstream f(this->directory + std::to_string(k) + ".variableKTest");
			f << "weights punishments bestWeights" << std::endl;
			for(unsigned i = 0; i < weights.size(); i++) f << weights[i] << " " << punishmets[i] << " " << bestWeights[i] << std::endl;
			f.close();

		}
	}
}

void Tester::variableAlphaTest() {
	std::vector<double> possibleAlpha = { 0.9, 0.99, 0.999 };

	for(auto a: possibleAlpha)
	{
		this->solver->setSeed(this->seed);

		this->solver->setParams(this->TStart, this->TEnd, this->k, a, this->allowedChanges, this->changePunishment);

		Route * solution = this->solver->solve(this->network, this->from, this->to, this->time);

		if(solution != NULL)
		{
			auto weights = this->solver->getWeights();
			auto punishmets = this->solver->getPunishments();
			auto bestWeights = this->solver->getBestPosWeights();

			std::ofstream f(this->directory + std::to_string(a) + ".variableAlphaTest");
			f << "weights punishments bestWeights" << std::endl;
			for(unsigned i = 0; i < weights.size(); i++) f << weights[i] << " " << punishmets[i] << " " << bestWeights[i] << std::endl;
			f.close();

		}
	}
}

void Tester::variableTempTest() {
	std::vector<unsigned> possibleTemps = { 2, 10, 100, 300, 500, 1000 };

	for(auto t: possibleTemps)
	{
		this->solver->setSeed(this->seed);

		this->solver->setParams(t, this->TEnd, this->k, this->alpha, this->allowedChanges, this->changePunishment);

		Route * solution = this->solver->solve(this->network, this->from, this->to, this->time);

		if(solution != NULL)
		{
			auto weights = this->solver->getWeights();
			auto punishmets = this->solver->getPunishments();
			auto bestWeights = this->solver->getBestPosWeights();

			std::ofstream f(this->directory + std::to_string(t) + ".variableTempTest");
			f << "weights punishments bestWeights" << std::endl;
			for(unsigned i = 0; i < weights.size(); i++) f << weights[i] << " " << punishmets[i] << " " << bestWeights[i] << std::endl;
			f.close();

		}
	}
}

void Tester::variablePunishmentTest() {
	std::vector<unsigned> possiblePuns = { 0, 10, 30, 50, 100, 300 };

	for(auto p: possiblePuns)
	{
		this->solver->setSeed(this->seed);

		this->solver->setParams(this->TStart, this->TEnd, this->k, this->alpha, this->allowedChanges, p);

		Route * solution = this->solver->solve(this->network, this->from, this->to, this->time);

		if(solution != NULL)
		{
			auto weights = this->solver->getWeights();
			auto punishmets = this->solver->getPunishments();
			auto bestWeights = this->solver->getBestPosWeights();

			std::ofstream f(this->directory + std::to_string(p) + ".variablePunishmentTest");
			f << "weights punishments bestWeights" << std::endl;
			for(unsigned i = 0; i < weights.size(); i++) f << weights[i] << " " << punishmets[i] << " " << bestWeights[i] << std::endl;
			f.close();

		}
	}
}

void Tester::variableChangesTest() {
	std::vector<unsigned> possibleChanges = { 0, 1, 3, 5, 10, 20, 100 };

	for(auto c: possibleChanges)
	{
		this->solver->setSeed(this->seed);

		this->solver->setParams(this->TStart, this->TEnd, this->k, this->alpha, c, this->changePunishment);

		Route * solution = this->solver->solve(this->network, this->from, this->to, this->time);

		if(solution != NULL)
		{
			auto weights = this->solver->getWeights();
			auto punishmets = this->solver->getPunishments();
			auto bestWeights = this->solver->getBestPosWeights();

			std::ofstream f(this->directory + std::to_string(c) + ".variableChangesTest");
			f << "weights punishments bestWeights" << std::endl;
			for(unsigned i = 0; i < weights.size(); i++) f << weights[i] << " " << punishmets[i] << " " << bestWeights[i] << std::endl;
			f.close();

		}
	}
}

void Tester::setDefaults(double Tstart, double Tend, unsigned int k,
		double alpha, unsigned int allowedChangeNumber,
		unsigned int changePunishment) {

	this->TStart = Tstart;
	this->TEnd = Tend;
	this->k = k;
	this->alpha = alpha;
	this->allowedChanges = allowedChangeNumber;
	this->changePunishment = changePunishment;
}
 
