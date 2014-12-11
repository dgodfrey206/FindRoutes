/*
 * BFS.cpp
 *
 *  Created on: 9 gru 2014
 *      Author: rafal
 */

#include "BSFR.h"
#include "Solver.h"
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <time.h>

const std::string BsfRandAlg::name = "BSF Random";

BsfRandAlg::BsfRandAlg(){

}

BsfRandAlg::~BsfRandAlg(){

}

Route* BsfRandAlg::solve(const Network * n, Node * start, Node * end, Time t){

	std::deque<unsigned int> S;
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
	S.push_back(startNodeId);
	P[startNodeId] = startNodeId;
	unsigned int v = startNodeId;
	while(!S.empty()){
		std::random_shuffle(S.begin(), S.end());
		unsigned int j = S.front();
		S.pop_front();
		visited[j] = true;
		v = j;
		if( v == endNodeId) break;
		for(unsigned int i=0; i<nodesNumber; i++){			//przeglądaj wszystkich sąsiadów
			if(n->incidenceMatrix[v][i]){
				if(visited[i]) continue;
				S.push_back(i);
				P[i] = v;
			}
		}
	}

	std::vector<unsigned int> resultVector;
	while( v != startNodeId){
		resultVector.push_back(v);
		v = P[v];
	}
	resultVector.push_back(v);

	Route* resultRoute;
	resultRoute = new Route();

	for( auto it = resultVector.rbegin()+1; it != resultVector.rend(); it++ ){
		//std::cerr<<*it<<" "<<n->getNode(*it)->getName()<<std::endl;
		unsigned int edgeId = n->calculateEdgeId( n->getNode(*(it-1))->getID() ,n->getNode(*it)->getID());
		Edge* newEdge = n->getEdge(edgeId);
		//std::cerr<<*newEdge<<std::endl;
		resultRoute->addEdge(newEdge);
	}

	return resultRoute;
}

const std::string & BsfRandAlg::getName() const{
	return this->name;
}
