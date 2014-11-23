/*
 * BFS.cpp
 *
 *  Created on: 23 lis 2014
 *      Author: rafal
 */

#include "Solver.h"
#include <vector>
#include <list>
#include <queue>
#include "BSF.h"

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

