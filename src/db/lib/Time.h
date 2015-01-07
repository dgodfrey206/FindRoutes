/*
* Time.h
 *
 *  Created on: 9 lis 2014
 *      Author: Rafa� Prusak
 */

#ifndef DB_LIB_TIME_H_
#define DB_LIB_TIME_H_

#include <iostream>

/**
 * Class providing time functions used in timetable generation.
 */
class Time{
public:

	/**
	 * Default constructor.
	 */
	Time();

	/**
	 * Constructor.
	 * @param hour Hour.
	 * @param minute Minute.
	 */
	Time(unsigned int hour, unsigned int minute);

	/**
	 * Constructor creating object pointing to time minutes ahead of midnight.
	 * @param minutes Minutes from midnight.
	 */
	Time(unsigned int minutes);

	/**
	 * Copying constructor.
	 * @param src Object being copied.
	 */
	Time(const Time& src);

	/**
	 * Destructor.
	 */
	~Time();

	/**
	 * Assignment operator.
	 * @param src Reference object being assigned.
	 * @return Reference to self.
	 */
	Time& operator=(const Time& src);

	/**
	 * Comparation operator.
	 * @param src Reference to compared object.
	 * @return True if given hours are equal.
	 */
	bool operator==(const Time& src) const;

	/**
	 * Comparation operator.
	 * @param src Reference to compared object.
	 * @return True if given hours are not equal.
	 */
	bool operator!=(const Time& src) const;

	/**
	 * Greater than operator.
	 * @return True if given "this" time is later from midnight than src time.
	 */
	bool operator>(const Time src);
	bool operator>=(const Time src);
	/**
	 * Greater than operator.
	 * @return True if given "this" time is sooner from midnight than src time.
	 */
	bool operator<(const Time src);
	bool operator<=(const Time src);


	/**
	 * Addition operator.
	 * Creates object pointing to time created by adding two given hours.
	 * @param src given Time object.
	 * @return Time object.
	 */
	Time operator+(const Time src);

	/**
	 * Subtraction operator.
	 * Creates object pointing to time created by subtracting two given hours.
	 * @param src given Time object.
	 * @return Time object.
	 */
	Time operator-(const Time src);

	/**
	 * Converts Time to int.
	 */
	operator int();

	/**
	 * Helper output function.
	 * @param output Stream
	 * @param src Outputed object.
	 * @return Reference to given stream.
	 */
	friend std::ostream& operator<<(std::ostream& output, const Time src);
private:
	unsigned int minutes;
};


#endif /* DB_LIB_TIME_H_ */
