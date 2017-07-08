/*
 * Command.h
 *
 *  Created on: Apr 14, 2016
 *      Author: Marco Mancini
 */

#ifndef MODEL_COMMAND_H_
#define MODEL_COMMAND_H_

#include <string>

using namespace std;

/**
 * Reppresents a specific command that will be execute
 * to retrieve informations about devices
 */

class Command{
private:
	//command to execute
	string command;

	/*
	 * string to filter from the command's output.
	 * A generic command retrieve infos like (VENDOR: LENOVO)
	 * using this filter properly (in this case setted to "VENDOR: ")
	 * in combo with the commandmanager will retrieve only the desired information
	 */

	string mainFilter;

	/**
	 * string to filter from a mainfiltered command.
	 *	EXAMPLE: ROM SIZE: 33K -> after mainfilter("ROM SIZE: ")
	 *			 		   33K ->after secondFilter("K")
	 *			 		   33
	 */
	string secondFilter;

public:
	Command();
    ~Command(){};

	/*Setters*/
	void setCommand(string command);
	void setFilter(string toFilter);
	void setSecondFilter(string secondFilter);

	/*Getters*/
	int getPosition();
	string getCommand();
	string getFilter();
	string getSecondFilter();
};



#endif /* MODEL_COMMAND_H_ */
