/*
 * BaseProperty.h
 *
 *  Created on: May 27, 2016
 *      Author: root
 */

#ifndef BASEPROPERTY_H_
#define BASEPROPERTY_H_

#include <string>
#include "Command.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
//#include "../Visitors/Visitor.h"

class Visitor;
class BaseInfoVisitor;

template <class T>
class BaseInfo;

using namespace std;

/**
 * This class models a base property, it's composed by a string only that
 * rappresents the property name and is extended by @BaseInfo that model
 * the final property composed by the value too
 */
class BaseProperty{
private:
	//the property name.
	string property;
public:
	virtual ~BaseProperty(){};

	void setProperty(string property) { this->property = property; }

	string getProperty() { return this->property; }

	/**
	 * Visit the object and set his generic value with a command
	 *
	 * @param v the visitor used to set the value
	 * @param cmd the command used to set the value
	 * */
	virtual void visitValueWithBaseCommand(Visitor& v, Command* cmd) = 0;

	/**
	 * Visit the object and print his content
	 *
	 * @param v the visitor used to print
	 */
	virtual void visitToPrint(Visitor &v) = 0;

	/**
	 * Visit the object and log it into a log file
	 *
	 * @param v the visitor used
	 * @param logFile the log file
	 */
	virtual void visitToLog(Visitor& v, FILE* logFile) = 0;

	/**
	 * Visit the object and assign his generic value.
	 *
	 *
	 * @param v the visitor used
	 * @param toAssign the value to assign (it's everytime a string and the visitor
	 * will know how to cast it properly)
	 */
	virtual void visitToAssign(Visitor& v, string toAssign) = 0;

};



#endif /* BASEPROPERTY_H_ */
