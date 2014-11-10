/*
 * ServiceData.h
 *
 *  Created on: 10 lis 2014
 *      Author: Rafa³ Prusak
 */

#ifndef DB_LIB_SERVICEDATA_H_
#define DB_LIB_SERVICEDATA_H_

#include <iostream>
#include <string>

class ServiceData{
	public:
		ServiceData();
		ServiceData(const ServiceData& src);
		ServiceData(unsigned int id, std::string name);
	    ~ServiceData();
	    ServiceData operator=(const ServiceData src);
	    bool operator==(const ServiceData src);
	    friend std::ostream& operator<<(std::ostream& output, const ServiceData& src);
	    unsigned int getId();
	    std::string getName();
	private:
		unsigned int id;
		std::string name;
};


#endif /* DB_LIB_SERVICEDATA_H_ */
