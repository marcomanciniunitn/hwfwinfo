/*
 * BaseLogDifference.h

 *
 *  Created on: May 31, 2016
 *      Author: root
 */

#ifndef BASELOGDIFFERENCE_H_
#define BASELOGDIFFERENCE_H_

#include "BaseInfo.h"
#include "../Visitors/Visitor.h"

class BaseInfoVisitor;

using namespace std;

/**
 * This template class rappresents a generic BaseLogDifference used to find
 * difference during the checking phase.
 */
template <class T>
class BaseLogDifference : public BaseDifference{
private:
	//The property value
	T value;

public:
	void setValue(T value){ this->value = value; }

	T getValue(){ return this->value; }


	/**
	 * Method used to assign the T value by a visitor.
	 *
	 * @param v the visitor used
	 * @param toAssign the value to assign. it's a string and the visitor
	 * 		   will know how to cast it.
	 */
	void visitToAssign(Visitor& v, string toAssign){
		v.visitBaseInfoWithValue(value, toAssign);
	}

	/**
	 * Method used to print the generic value.
	 *
	 * @param v visitor used to print.
	 */
	void visitToPrint(Visitor& v){
		v.visitLogToPrint(this->check,this->prop, value);
	}

};


#endif
