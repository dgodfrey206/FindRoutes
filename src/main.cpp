/*
 * main.cpp
 *
 *  Created on: 15 paź 2014
 *      Author: Wojtek Gumuła
 */

#include <iostream>
#include <fstream>
#include <string>

#include "db/DataReader.h"

int main()
{
	std::string stopsFile("../db/stops.json");
	std::vector<StopData> stopsVector = DataReader::readStops(stopsFile);

	if( stopsVector.empty()){
		std::cout<<"zwr�cono pusty wektor!"<<std::endl;
	}else{
		for(unsigned int i=0; i<stopsVector.size(); i++){
			std::cout<<stopsVector[i];
		}
	}


}


