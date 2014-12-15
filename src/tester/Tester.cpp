/*
 * Tester.cpp
 *
 *  Created on: 15 gru 2014
 *      Author: Wojtek Gumuła
 */

#include "Tester.h"

Tester::Tester(Network * n):
	network(n){
	// TODO Auto-generated constructor stub
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

	this->directory = "";
}

Tester::~Tester() {
}

void Tester::makeTests(Node * f, Node * t, std::string dir) {
	if(this->network == NULL) return;

	if(this->solver == NULL)
	{
		this->solver = new SimAnnealingAlg;
		this->network->setSolver(this->solver);
	}

	this->from = f;
	this->to = t;

	this->directory = dir;
	if(this->directory[this->directory.size()-1] != '/') this->directory += "/";

	this->variableAlphaTest();
	this->variableChangesTest();
	this->variableKTest();
	this->variablePunishmentTest();
	this->variableTempTest();
}

void Tester::variableKTest() {
	std::vector<unsigned> possibleK = { 1, 10/*, 100, 1000*/ };


	for(auto k: possibleK)
	{
		std::cout << k << std::endl;
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
	std::vector<double> possibleAlpha = { 0.9, 0.99/*, 0.999, 0.9999*/ };

	for(auto a: possibleAlpha)
	{
		std::cout << a << std::endl;
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
	std::vector<unsigned> possibleTemps = { 2, 10, 100, 1000 };

	for(auto t: possibleTemps)
	{
		std::cout << t << std::endl;
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
		std::cout << p << std::endl;
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
	std::vector<unsigned> possibleChanges = { 0, 1, 3, 5, 10, 100 };

	for(auto c: possibleChanges)
	{
		std::cout << c << std::endl;
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
