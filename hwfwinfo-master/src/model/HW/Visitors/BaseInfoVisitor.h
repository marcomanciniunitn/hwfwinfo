/*
 * SetInfoVisitor.h
 *
 *  Created on: May 27, 2016
 *      Author: root
 */

#ifndef SETINFOVISITOR_H_
#define SETINFOVISITOR_H_

#include "Visitor.h"
#include "../Basic/HWDevice.h"

class HWDevice;

using namespace std;

/**
 * This class model a visitor able to visit properties and log differences and manage them
 */
class BaseInfoVisitor : public Visitor{
public:
	~BaseInfoVisitor(){};

	void visitBaseInfoWithCommand(int& v , Command* cmd){
		CommandManager<int>* intCmdManager = new CommandManager<int>();
		v = intCmdManager->getInfoFromCommand(cmd);
	}

	void visitBaseInfoWithCommand(string& v, Command* cmd){
		CommandManager<string>* stringCmdManager = new CommandManager<string>();
		v = stringCmdManager->getInfoFromCommand(cmd);
	}

	void visitBaseInfoToPrint(int v, string property){
		cout << property << ": " <<  v << endl;
	}

	void visitBaseInfoToPrint(string v, string property){
		cout << property << ": " <<  v << endl;
	}

	void visitBaseInfoToLog(int v, string property, FILE* logFile){
		fprintf(logFile, "%s: %d\n",property.c_str(), v);
	}

	void visitBaseInfoToLog(string v, string property, FILE* logFile){
		fprintf(logFile, "%s: %s\n",property.c_str(), v.c_str());
	}


	void visitBaseInfoWithValue(int& v , string toAssign){
		v = stoi(toAssign);
	}
	void visitBaseInfoWithValue(string& v, string toAssign){
		v = toAssign;
	}

	void visitLogToPrint(bool check, string prop,string value){
		if(check){
			cout << prop << " changed in: " << value << endl;
		}else{
			cout << prop << " not changed" << endl;
		}
	}

	void visitLogToPrint(bool check, string prop,int value){
		if(check){
			cout << prop << " changed in: " << value << endl;
		}else{
			cout << prop << " not changed" << endl;
		}
	}

	void visitAndSetBaseLogVisitor(string& toAssign, string value){
		toAssign = value;
	}

};




#endif /* SETINFOVISITOR_H_ */
