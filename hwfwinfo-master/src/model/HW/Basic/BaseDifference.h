/*
 * BaseDifference.h
 *
 *  Created on: May 31, 2016
 *      Author: root
 */

#ifndef BASEDIFFERENCE_H_
#define BASEDIFFERENCE_H_

#include <string>
#include "../Visitors/Visitor.h"

class Visitor;

using namespace std;

/**
 * Models a basic difference
 */
class BaseDifference{
protected:
	//TRUE = difference found , NOT = no difference found
	bool check;

	//property checked
	string prop;

public:
	virtual ~BaseDifference(){};

	/**
	 * Default Basedifference = no difference
	 */
	BaseDifference(){
		this->check = false;
		this->prop = " ";
	}

	/**
	 * Setter and getter for check attribute
	 */
	void setCheck(bool check){ this->check = check; }
	bool getCheck(){ return this->check; };

	/**
	 * Settere and getter for propr attribute
	 */
	void setProp(string prop) { this->prop = prop; }
	string getProp() { return this->prop; }

	/**
	 * Method used to visit the base difference and set his generic value
	 *
	 * @param v visitor used to visit the base difference
	 * @param toAssign value to assign, it's a string and the specific
	 * 		  implementation will know how to handle and cast it properly
	 */
	virtual void visitToAssign(Visitor& v, string toAssign) = 0;

	/**
	 * Method used to visit the base difference and print his property
	 *
	 * @param v visitor used to print it.
	 */
	virtual void visitToPrint(Visitor& v) = 0;
};




#endif /* BASEDIFFERENCE_H_ */
