/*
http://open.spotify.com/track/0QervLYxa3WBLkSTLkcGNw * Network.h
 *
 *  Created on: 20 October 2014
 *      Author: David Godfrey
 */

#ifndef SRC_NETWORK_H_
#define SRC_NETWORK_H_

#include <set>
#include <list>
#include <iostream>
#include <cmath> //distance computing

#include "Node.h"
#include "Edge.h"
#include "TransportType.h"
#include "Route.h"
#include "../algorithm/Solver.h"
#include "../db/DataBase.h"
#include "../db/lib/Time.h"

class Solver; //forward declaration

/**
 * main class, contains information
 * about nodes and edges between them.
 * Should be created from file containing
 * data in GTFS or other format.
 * loadFromFile method should load "db/db.ext" file
 * and save it to inner variables.
 */

struct edgePointerCompare{
	bool operator()(Edge* e1,Edge* e2) const{
		return (e1->getID()<e2->getID());
	}
};

struct nodePointerCompare{
	bool operator()(Node* n1,Node* n2) const{
		return (n1->getID()<n2->getID());
	}
};

class Network {
public:
	/**
	 * Network object constructor.
	 * If this constructor is called, loadFromFile method need to be called after.
	 */
	Network();

	/**
	 * Network object constructor in which {@link Network::loadFromFile()} method is being called.
	 * @param f Name of file from which database is loaded.
	 */
	//Network(std::string f);

	/**
	 * Destructs all objects in Network and itself.
	 */
	~Network();

	/**
	 * Creates Network from database
	 */
	Network(DataBase& dataB);

	/**
	 * Set solved used in {@link Network::findRouteBetween()} method.
	 * @param s Pointer to Solver being used.
	 */
	void setSolver(Solver * s);// todosetSolver(Route & (*ptr)(const Network &))?;

	/**
	 * Searches for Route beetween two given points.
	 * @param start Start Node.
	 * @param end End Node.
	 * @param maxSwitches Defines number of maximum transfers permited during trip.
	 * @return Pointer to Route between given nodes, NULL if no route can be found.
	 */
	Route * findRouteBetween(Node * start, Node * end, const unsigned int maxSwitches);

	/**
	 * This function is necessary for GUI.
	 * @return Returns some kind of stl container in which
	 * all nodes are stored in alphabetical order.
	 */
	std::list<Node *> getAllNodes() const;

	/**
	 * For debug.
	 * @return Returns some kind of stl container in which
	 * all edges are stored.
	 */
	std::list<Edge *> getAllEdges()const;

	/**
	 * Used of debug in console purposes.
	 * @param s Stream used for output.
	 * @param n Reference to Network being printed.
	 * @return Given stream.
	 */
	friend std::ostream& operator<<(std::ostream& s, const Network& n);

	/**
	 * @param start Pointer to starting Node.
	 * @param end Pointer to ending Node.
	 * @return True if Edge from start to end exists in graph, false otherwise.
	 */
	bool isEdgeBetween(const Node * start, const Node * end) const; //returns true if edge between two nodes exists

	/**
	 *	@param id Id of desired Node.
	 *	@return Pointer to desired Node if exists in graph, NULL otherwise.
	 */
	Node * getNode(unsigned int id) const; //get Node by id

	/**
	 *	@param id Id of desired Edge.
	 *	@return Pointer to desired Edge if exists in graph, NULL otherwise.
	 */
	Edge* getEdge(unsigned int id) const; //get Edge by id

	/**
	 * @param n Pointer to given Node.
	 * @return std::list of all Edges starting in given Node.
	 */
	std::list<Edge *> getEdgesForNode(const Node * n) const;

	/**
	 * @param latitude Given latitude
	 * @param longtitude Given longtitude.
	 * @return Returns pointer to Node being closest to given geographic position.
	 */
	Node * getNodeCloseToPos(double latitude, double longtitude) const; //returns node close do desired position

	/**
	 * two dimensional bool array containing data about connections
	 * for matrix[i][j], true means there is connection between node.id == i to node.id ==j.
	 */
	bool ** incidenceMatrix;

	/*
	 * Calculates edge id form incident nodes ids
	 * Can be used if findEdge function
	 * @param startId id of node wher edge starts
	 * @param endId id of node where edge ends
	 * */
	unsigned int calculateEdgeId(unsigned int startId, unsigned int endId) const;

	bool validate();
private:
	std::set<Node *, nodePointerCompare> nodes;
	std::set<Edge *, edgePointerCompare> edges;

	/**
	 * Adds given Node to graph.
	 * @param n Pointer to Node.
	 * @return true if Node was added to graph, false otherwise.
	 */
	bool addNode(Node * n); //adds Node if not exists

	/**
	 * Adds given Edge to graph.
	 * @param e Pointer to Edge.
	 * @return true if Edge was added to graph, false otherwise.
	 */
	bool addEdge(Edge * e); //adds Edge if not exists

	/*
	 * Creates an incidence Matrix
	 * */
	void createIncidenceMatrix();
	/*
	 * Calculates edge id form incident nodes ids
	 * Can be used if findEdge function
	 * @param startId id of node wher edge starts
	 * @param endId id of node where edge ends
	 * */
unsigned int calculateEdgeId(unsigned int startId, unsigned int endId);

	Solver * solver;
};

#endif /* SRC_NETWORK_H_ */
