/*
 * GTFSReader.cpp
 *
 *  Created on: 9 lis 2014
 *      Author: Wojtek Gumuła
 */

#include "GTFSReader.h"

GTFSReader::GTFSReader() {
}

GTFSReader::~GTFSReader() {
}

Network* GTFSReader::readGTFS(std::string filename) {

	std::cout << "readGTFS called. Filename " << filename << std::endl;
	//open zip archive
	int error = 0;
	char errorBuffer[100];
	struct zip * z = zip_open(filename.c_str(), 0, &error); //-lzip for g++ linked is needed!

	if(error != ZIP_ER_OK)
	{
		std::cout << "Err value: " << error << std::endl;
		zip_error_to_str(errorBuffer, 100, 0, error);
		std::cout << "Err msg: " << errorBuffer << std::endl;
		return NULL;
	}

	//load stops:
	this->loadStops(z);

	for(StopData * s: this->stops)
	{
		std::cout << *s << std::endl;
	}

	return NULL;
}

void GTFSReader::loadStops(struct zip* z) {
	std::cout << "loadStops called." << std::endl;
	if(z == NULL)
	{
		std::cout << "Got empty pointer as argument, return." << std::endl;
		return;
	}

	zip_file * f;
	struct zip_stat st;

	zip_stat_init(&st);
	zip_stat(z, "stops.txt", 0, &st);

	char * c = new char[st.size];

	f = zip_fopen(z, "stops.txt", 0);
	zip_fread(f, c, st.size);
	zip_fclose(f);

	std::string contents(c, st.size);
	std::vector<std::string> stops = GTFSReader::splitStrings(contents, '\n');

	unsigned int id = 0;

	for(std::string s: stops)
	{
		std::vector<std::string> stopData = GTFSReader::splitStrings(s, ',');
		int id = 0;
//		for(std::string d: stopData) std::cout << id++ << ". " << d << std::endl; //todo debug
		//create StopData object and populate it
		try
		{
			this->stops.push_back(new StopData(stopData[2], id, std::stod(stopData[4]), std::stod(stopData[5])));
			this->stopIDsTranslate.insert(std::pair<std::string, unsigned int>(stopData[0], id++));
		}
		catch(std::invalid_argument & e)
		{
			continue;//first line, skip
		}

	}
}

std::vector<std::string> GTFSReader::splitStrings(const std::string &s, char delim) {
	/*
	 * source: https://stackoverflow.com/questions/236129/split-a-string-in-c/236803#236803
	 */

    std::vector<std::string> elems;
    std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
    return elems;
}
