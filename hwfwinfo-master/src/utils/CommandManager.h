/*
 * CommandManager.h
 *
 *  Created on: Apr 14, 2016
 *      Author: root
 */

#ifndef UTILS_COMMANDMANAGER_H_
#define UTILS_COMMANDMANAGER_H_

#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "../model/HW/Basic/Command.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include "StringManager.h"
#include <type_traits>


using namespace std;

/**
 * This helper contains all common methods for differents commandManagers
 */
class helper_cmdManager{
public:

	/**
	 * execute a command and return the stdout
	 *
	 * @param cmd the command to execute
	 */
	string GetStdoutFromCommand(Command* cmd){
		string data;
		string command;
		command = cmd->getCommand();
		FILE * stream;
		const int max_buffer = 256;
		char buffer[max_buffer];
		command.append(" 2>&1");

		stream = popen(command.c_str(), "r");
		if (stream) {
			while (!feof(stream))
		if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
			pclose(stream);
		}
		return data;
	}

};

template <class T>
/**
 * Used to manage commands and return the output command in string type.
 *
 *  */
class CommandManager : public helper_cmdManager{
};

template<>
class CommandManager<string> : public helper_cmdManager{
public:
	string getInfoFromCommand(Command* cmd){
		string commandOutput = this->GetStdoutFromCommand(cmd);
		StringManager* strManager = new StringManager();

		std::size_t found = commandOutput.find(cmd->getFilter());
		if (found!=std::string::npos){
			return strManager->trimmed(commandOutput.substr(found + cmd->getFilter().size(), commandOutput.size()));
		}else{
			return "NOTFOUND";
		}
	}

};

/**
 * Used to manage commands and return the output command in integer type.
 */
template<>
class CommandManager<int> : public helper_cmdManager{
private:
public:
	int getInfoFromCommand(Command* cmd){
		string commandOutput = this->GetStdoutFromCommand(cmd);
		StringManager* strManager = new StringManager();

		std::size_t found = commandOutput.find(cmd->getFilter());
		if (found!=std::string::npos){
			string tmp = strManager->trimmed(commandOutput.substr(found + cmd->getFilter().size(), commandOutput.size()));
			string toCheck = strManager->getSubString(tmp, cmd->getSecondFilter(), true);
			if(strManager->isNumber(toCheck)){
				return stoi(strManager->getSubString(tmp, " ", true));
			}else{
				return -1;
			}

		}else{
			return -1;
		}
	}
};

#endif /* UTILS_COMMANDMANAGER_H_ */
