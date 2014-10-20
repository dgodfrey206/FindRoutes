/*
 * Node.h
 *
 *  Created on: 20 paź 2014
 *      Author: Wojtek Gumuła
 */

#ifndef SRC_NODE_H_
#define SRC_NODE_H_

class Node {
	/*
	 * primary element.
	 */
public:
	Node();
	~Node();

	double getLon() const;
	double getLat() const;

private:
	double longtitude;
	double latitude;
	double name;

};

#endif /* SRC_NODE_H_ */
