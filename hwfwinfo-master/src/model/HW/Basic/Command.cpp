/*
 * Command.cpp

 *
 *  Created on: Apr 14, 2016
 *      Author: root
 */

#include "Command.h"

Command::Command(){
	this->mainFilter = " ";
	this->secondFilter = " ";
};



void Command::setCommand(string command){
	this->command = command;
}

void Command::setFilter(string toFilter){
	this->mainFilter = toFilter;
}

void Command::setSecondFilter(string secondFilter){
	this->secondFilter = secondFilter;
}

string Command::getCommand(){
	return this->command;
}

string Command::getFilter(){
	return this->mainFilter;
}

string Command::getSecondFilter(){
	return this->secondFilter;
}


