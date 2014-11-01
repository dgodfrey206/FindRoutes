/*
 * Node.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

#include <iostream>
#include <iomanip>
#include <string>

class Node {
	/*
	 * primary element.
	 */
public:
	Node(unsigned int id, std::string name, double lon, double lat);

	double getLongtitude() const;
	double getLatitude() const;
	unsigned int getID() const;
	std::string getName() const;

	friend std::ostream& operator<<(std::ostream&, const Node&);

	bool operator ==(const Node & n) const;
	bool operator !=(const Node & n) const;

	bool operator <(const Node & n) const; //for Network purpose

	Node & operator = (const Node &);

private:
	unsigned int id;
	std::string name;
	double longtitude;
	double latitude;
};

#endif /* SRC_NODE_H_ */
