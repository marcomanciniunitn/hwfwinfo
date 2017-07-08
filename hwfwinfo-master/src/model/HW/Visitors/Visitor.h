/*
 * Visitor.h
 *
 *  Created on: May 27, 2016
 *      Author: root
 */

#ifndef VISITOR_H_
#define VISITOR_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "../../HW/Basic/Command.h"
#include "../../../utils/CommandManager.h"

class HWDevice;
template <class T>
class BaseInfo;


using namespace std;

/**
 * This class rappresents a generic visitor.
 * It's used to visit and manage (set, print, log) both property and logdifferences.
 */
class Visitor{
public:
	virtual ~Visitor(){};

	/**
	 * Method used to visit a baseinfo and set his value to an information retrieved
	 * by a command passed by param
	 *
	 * @param v the int value to set
	 * @param cmd the command used
	 */
	virtual void visitBaseInfoWithCommand(int& v,Command* cmd) = 0 ;

	/**
	 * Method used to visit a baseinfo and set his value to an information retrieved
	 * by a command passed by param
	 *
	 * @param v the string value to set
	 * @param cmd the command used
	 */
	virtual void visitBaseInfoWithCommand(string& v, Command* cmd) = 0;

	/**
	 * Method used to visit a baseinfo and print his value and his property
	 *
	 * @param v the int value to print
	 * @param property the property to print
	 */
	virtual void visitBaseInfoToPrint(int v, string property) =  0;

	/**
	 * Method used to visit a baseinfo and print his value and his property
	 *
	 * @param v the string value to print
	 * @param property the property to print
	 */
	virtual void visitBaseInfoToPrint(string v, string property) = 0;

	/**
	 * Method used to visit a baseinfo and log his value and his property
	 *
	 * @param v the int value to log
	 * @param property the property to log
	 * @param logFile the log file to populate.
	 */
	virtual void visitBaseInfoToLog(int v, string property, FILE* logFile) = 0;

	/**
	 * Method used to visit a baseinfo and log his value and his property
	 *
	 * @param v the string value to log
	 * @param property the property to log
	 * @param logFile the log file to populate.
	 */
	virtual void visitBaseInfoToLog(string v, string property, FILE* logFile) = 0;


	/**
	 * Method used to visit a baseinfo and set his value.
	 *
	 * @param v the int value to set
	 * @param property the property to set
	 */
	virtual void visitBaseInfoWithValue(int& v , string toAssign) = 0 ;

	/**
	 * Method used to visit a baseinfo and set his value.
	 *
	 * @param v the string value to set
	 * @param property the property to set
	 */
	virtual void visitBaseInfoWithValue(string& v, string toAssign) = 0;

	/**
	 * Method used to visit a log file and populate it
	 *
	 * @param check the check value
	 * @param prop the property checked
	 * @param value the value checked
	 */
	virtual void visitLogToPrint(bool check, string prop, string value) = 0;

	/**
	 * Method used to visit a log file and populate it
	 *
	 * @param check the check value
	 * @param prop the property checked
	 * @param value the value checked
	 */
	virtual void visitLogToPrint(bool check, string prop, int value) = 0;

};



#endif /* VISITOR_H_ */
