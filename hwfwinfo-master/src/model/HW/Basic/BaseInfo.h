/*
 * BaseInfo.h
 *
 *  Created on: May 26, 2016
 *      Author: root
 */

#ifndef BASEINFO_H_
#define BASEINFO_H_

#include <string>
#include "BaseProperty.h"
#include "../Visitors/Visitor.h"



class BaseInfoVisitor;

using namespace std;


/* *
 * This template models a generic BaseInfo used by a generic
 * @HWDevice to model his properties.
 *
 *  */
template <class T>
class BaseInfo : public BaseProperty{
private:
	// The property value
	T value;
public:

	void setValue(T value){ this->value = value; }

	T getValue(){ return this->value; }


	void visitValueWithBaseCommand(Visitor& visitor, Command* cmd){ visitor.visitBaseInfoWithCommand(value, cmd); }

	void visitToPrint(Visitor& v){ v.visitBaseInfoToPrint(value, getProperty()); }

	void visitToLog(Visitor& v, FILE* logFile){ v.visitBaseInfoToLog(value, getProperty(), logFile); }

	void visitToAssign(Visitor& v, string toAssign){
		v.visitBaseInfoWithValue(value, toAssign);
	}

};



#endif /* BASEINFO_H_ */
