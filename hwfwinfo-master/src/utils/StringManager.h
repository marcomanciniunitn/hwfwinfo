/*
 * StringManager.h
 *
 *  Created on: May 5, 2016
 *      Author: root
 */

#ifndef UTILS_STRINGMANAGER_H_
#define UTILS_STRINGMANAGER_H_

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ID_STRING "---Scan Date"

using namespace std;


class StringManager{
private:
	/**
	 * Trim on left
	 */
	void ltrim(std::string &s);

	/**
	 * Trim or right
	 */
	void rtrim(std::string &s);

	/**
	 * Trim
	 */
	void trim(std::string &s);

public:
	/**
	 * return a filtered string
	 *
	 * @param toFilter string to filter
	 * @param filter filter to use
	 * @param beforeTheFilter (TRUE=Filter before the string, FALSE=Filter after the string)
	 */
	string getSubString(string toFilter, string filter, bool beforeTheFilter);

	/**
	 * return a filtered(filter= ":") property
	 *
	 * @param toFilter the string to filter to extrapolate the property
	 * @param property the property to filter
	 * @return the filtered property
	 */
	string getProperty(string toFilter, string property);

	/**
	 * Trim a string
	 *
	 * @param s string to trim
	 * @return trimmed string
	 */
	string trimmed(std::string s);

	/**
	 * Check if a string passed is a number or not
	 *
	 */
	bool isNumber(string toCheck);

	/**
	 * This method generate a current timestamp
	 */
	string generateTimeStamp();


};


#endif /* UTILS_STRINGMANAGER_H_ */
