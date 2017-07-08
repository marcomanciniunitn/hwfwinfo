/*
 * ShellMenuParser.h
 *
 *  Created on: Jun 20, 2016
 *      Author: root
 */

#ifndef SHELLMENUPARSER_H_
#define SHELLMENUPARSER_H_

#include <string>
#include "../model/FW/Manager/FirmwareManager.h"
#include "../model/HW/Manager/HWManager.h"

using namespace std;

#define HELP_STR "-h"
#define HW_STR "-hw"
#define FW_STR "-fw"
#define LOG_STR "-l"
#define CHECK_STR "-c"
#define REVISION_STR "-n"

/**
 * This class reppresents the menu parser, it's able to execute the right operations on right manager based on
 * shell parameters.
 */
class ShellMenuParser{
public:
	ShellMenuParser();

	/**
	 * This method parse the shell commands and execute the right operations.
	 */
	void parseAndExecute(int argc, char* argv[]);
};




#endif /* SHELLMENUPARSER_H_ */
