/*
 * Network.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
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
#include "Solver.h"

/**
 * main class, contains information
 * about nodes and edges between them.
 * Should be created from file containing
 * data in GTFS or other format. //todo
 * loadFromFile method should load "db/db.ext" file
 * and save it to inner variables.
 */
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
	Network(std::string f);

	/**
	 * Destructs all objects in Network and itself.
	 */
	~Network();


	/**
	 * Load database entries from given file.
	 * @param f Filename from which database is being loaded.
	 */
	void loadFromFile(std::string f);

	/**
	 * Set solved used in {@link Network::findRouteBetween()} method.
	 * @param s Pointer to Solver being used.
	 */
	void setSover(Solver * s);// todosetSolver(Route & (*ptr)(const Network &))?;

	/**
	 * Searches for Route beetween two given points.
	 * @param start Start Node.
	 * @param end End Node.
	 * @return Pointer to Route between given nodes, NULL if no route can be found.
	 */
	Route * findRouteBetween(const Node * start, const Node * end);

	/**
	 * Used of debug in console purposes.
	 * @param s Stream used for output.
	 * @param n Reference to Network being printed.
	 * @return Given stream.
	 */
	friend std::ostream& operator<<(std::ostream& s, const Network& n);

private:
	std::set<Node *> nodes;
	std::set<Edge *> edges;

	/**
	 * @param start Pointer to starting Node.
	 * @param end Pointer to ending Node.
	 * @return True if Edge from start to end exists in graph, false otherwise.
	 */
	bool isEdgeBetween(const Node * start, const Node * end) const; //returns true if edge between two nodes exists

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

	/**
	 *	@param id Id of desired Node.
	 *	@return Pointer to desired Node if exists in graph, NULL otherwise.
	 */
	Node * getNode(unsigned int id); //get Node by id

	/**
	 *	@param id Id of desired Edge.
	 *	@return Pointer to desired Edge if exists in graph, NULL otherwise.
	 */
	Edge * getEdge(unsigned int id); //get Edge by id

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

	Solver * solver;
};

#endif /* SRC_NETWORK_H_ */
