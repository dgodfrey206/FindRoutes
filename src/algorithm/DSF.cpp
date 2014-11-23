/*
 * DsfAlg.c
 *
 *  Created on: 22 lis 2014
 *      Author: rafal
 */

#include "DSF.h"

#include <vector>
#include <list>
#include <stack>

DsfAlg::DsfAlg(){

}

DsfAlg::~DsfAlg(){

}

Route* DsfAlg::solve(const Network * n,Node * start,Node * end){

	std::stack<unsigned int> S;
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
		v = S.top();
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

	/*
	Route* resultRoute;
	resultRoute = new Route();
//todo solver should return Route*
	for(unsigned int i=1; i<resultVector.size();i++){
		unsigned int edgeId = n->calculateEdgeId(resultVector[i-1],resultVector[i]);
		resultRoute->addEdge(n->getEdge(edgeId));
	}


	return resultRoute;*/
	return NULL;

}
