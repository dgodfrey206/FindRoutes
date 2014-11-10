/*
 * Time.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa³ Prusak
 */

#ifndef DB_LIB_TIME_H_
#define DB_LIB_TIME_H_

#include <iostream>

class Time{
	public:
		Time();
		Time(unsigned int hour, unsigned int minute);
		Time(unsigned int minutes);
		Time(const Time& src);
		~Time();
		Time operator=(Time src);
		bool operator==(const Time src);
		bool operator!=(const Time src);
		bool operator>(const Time src);
		bool operator<(const Time src);
		Time operator+(const Time src);
		Time operator-(const Time src);
		operator int();
		friend std::ostream& operator<<(std::ostream& output, const Time src);
	private:
		unsigned int hour;
		unsigned int minute;
};


#endif /* DB_LIB_TIME_H_ */
