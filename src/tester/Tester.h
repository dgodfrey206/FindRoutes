/*
 * Tester.h
 *
 *  Created on: 15 gru 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_TESTER_TESTER_H_
#define SRC_TESTER_TESTER_H_

#include <iostream>
#include <string>

#include "../graph/Network.h"
#include "../algorithm/SimAnnealingAlg.h"

class Tester {
public:
	Tester(Network * n);
	~Tester();

	void makeTests(Node * from, Node * to, std::string directory, long long seed = 0);

	void setDefaults(double Tstart, double Tend, unsigned int k, double alpha, unsigned int allowedChangeNumber, unsigned int changePunishment);

private:
	void variableKTest();
	void variableAlphaTest();
	void variableTempTest();
	void variablePunishmentTest();
	void variableChangesTest();

	Network * 			network;
	SimAnnealingAlg *	solver;

	double 				TStart;
	double 				TEnd;
	unsigned int 		k;
	double 				alpha;
	unsigned int 		allowedChanges;
	unsigned int 		changePunishment;
	Node *				from;
	Node *				to;
	Time				time;
	std::string			directory;
	long long 			seed;
};

#endif /* SRC_TESTER_TESTER_H_ */
