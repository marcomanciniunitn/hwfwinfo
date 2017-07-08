/*
 * StringManager.cpp
 *
 *  Created on: May 5, 2016
 *      Author: root
 */

#include "StringManager.h"


// trim from start (in place)
void StringManager::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
void StringManager::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
void StringManager::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}


// trim from both ends (copying)
std::string StringManager::trimmed(std::string s) {
    trim(s);
    return s;
}



string StringManager::getSubString(string toFilter,string filter, bool beforeTheFilter){
	string filtered = toFilter;
	std::size_t found = toFilter.find(filter);
	if(found != std::string::npos){
		if(beforeTheFilter){
			filtered = toFilter.substr(0,found);
		}else{
			filtered = toFilter.substr(found + 1, toFilter.size());
		}
	}
	return trimmed(filtered);
}

string StringManager::getProperty(string toFilter, string property){
	string value = "NOT FOUND";
	std::istringstream stream(toFilter);
	std::string line;

	while (std::getline(stream, line)) {
		if(getSubString(line,":", true).compare(property) == 0){
			return trimmed(value = getSubString(line, ":", false));
		}
	}

	return trimmed(value);
}

bool StringManager::isNumber(string toCheck){
	return !toCheck.empty() && std::find_if(toCheck.begin(),
			toCheck.end(), [](char c) { return !std::isdigit(c); }) == toCheck.end();
}

string StringManager::generateTimeStamp(){
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	string day = to_string(aTime->tm_mday);
	string month = to_string(aTime->tm_mon + 1); // Month is 0 - 11, add 1 to get a jan-dec 1-12 concept
	string year = to_string(aTime->tm_year + 1900); // Year starts from 1900
	string hour = to_string(aTime->tm_hour);
	string minutes = to_string(aTime->tm_min);
	string seconds = to_string(aTime->tm_sec);

	string id = ID_STRING;
	id.append(": ").append(day).append("-").append(month).append("-").append(year)
			.append(" ").append(hour).append(":").append(minutes)
			.append(":").append(seconds).append("\n");

	return id;
}

