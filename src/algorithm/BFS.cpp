/*
 * BFS.cpp
 *
 *  Created on: 23 lis 2014
 *      Author: rafal
 */

#include "BFS.h"
#include "Solver.h"
#include <vector>
#include <list>
#include <queue>

BsfAlg::BsfAlg(){

}

BsfAlg::~BsfAlg(){

}
Route* BsfAlg::solve(const Network * n, Node * start, Node * end){

	std::queue<unsigned int> S;
	unsigned int* P;
	unsigned int startNodeId = start->getID();
	unsigned int endNodeId = end->getID();
	unsigned int nodesNumber = n->getAllNodes().size();

	bool* visited = new bool[nodesNumber];
	for(unsigned i=0; i<nodesNumber; i++){
		visited[i] = false;
	}

	P = new unsigned int[nodesNumber];
	for(unsigned int i=0; i<nodesNumber; i++)
		P[i] = 0;

	visited[startNodeId] = true;
	S.push(startNodeId);
	P[startNodeId] = startNodeId;
	unsigned int v;
	while(!S.empty()){
		v = S.front();
		S.pop();
		if( v == endNodeId) break;
		for(unsigned int i=0; i<nodesNumber; i++){			//przeglądaj wszystkich sąsiadów
			if(n->incidenceMatrix[v][i]){
				if(visited[i]) continue;
				P[i] = v;
				S.push(i);
				visited[i] = true;
			}
		}
	}

	std::vector<unsigned int> resultVector;

	while( v != startNodeId){
		std::cerr<<v<<" "<<n->getNode(v)->getName()<<std::endl;
		resultVector.push_back(v);
		v = P[v];
	}
	resultVector.push_back(v);
	std::cerr<<v<<" "<<n->getNode(v)->getName()<<std::endl;

	return NULL;
}

