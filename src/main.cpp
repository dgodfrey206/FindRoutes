/*
 * main.cpp
 *
 *  Created on: 15 paź 2014
 *      Author: Wojtek Gumuła
 */

#include <iostream>
#include "Network.h"
#
int main()
{
	Network net;
	SimAnnealingAlg::solve(net);
	std::cout << "Lorem ipsum" << std::endl;
}


