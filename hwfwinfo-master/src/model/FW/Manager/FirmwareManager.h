/*
 * FirmwareManager.h
 *
 *  Created on: Jun 1, 2016
 *      Author: root
 */

#ifndef FIRMWAREMANAGER_H_
#define FIRMWAREMANAGER_H_



#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <list>


#include "../Basic/Firmware.h"
#include "../../HW/Basic/Command.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../Basic/FWDifference.h"


class Firmware;

using namespace std;

/**
 * This class is used to manage all firmwares
 */
class FirmwareManager{
private:
	//Log file path
	string filePath;

	//the logFileName
	string fileName;

	//default string to identify an @Firmware in a logfile
	string inFileName;

	//firmwares retrieved on the system
	std::list<Firmware*> firmwares;

	/**
	 * This method scan a directory and fill the firmware list
	 *
	 * @param basedir the directory to scan
	 * @param recursive (TRUE = scan all subdirectories
	 */
	void listFiles(string baseDir, bool recursive);


	/**
	 * This method generate the log directory
	 */
	void generateLogDir();

	/**
	 * Retrieve all firmwares from a log file
	 *
	 * @param path the log file path
	 * @param err (0 = OK, -1 = no firmwares found)
	 * @return a list of firmwares retrieved from the path
	 */
	list<Firmware*> retrieveFromFile(string path, int& err);

	/**
	 * Check current firmwares with a log file
	 *
	 * @param path the log file path
	 * @param err (0 = OK, -1 = no firmwares found on system or log file, -2 = no firmwares found on log file)
	 * @return the differences
	 */
	list<FWDifference*> checkFWFromFile(string path, int &err);


public:
	~FirmwareManager();
	FirmwareManager();

	/**
	 * Return the log file path
	 */
	string getFilePath();

	/**
	 * Set the file path
	 *
	 * @param path the file path
	 */
	void setFilePath(string path);

	/**
	 * This method populate the firmware list
	 */
	void findFirmware();

	/**
	 * This method print all infos about firmware retrieved under main fw directory
	 */
	void printAllFWInfos();

	/**
	 * This method generate a log file under the log path
	 */
	void generateLog();

	/**
	 * This method print the differences presents in the difference list passed by param
	 *
	 * @param differences the difference list
	 */
	void printChecks(list<FWDifference*> differences);

	/**
	 * This method check firmware installed on the system with the firmware contained
	 * in a log file passed by param and print the result
	 *
	 * @param path the log file path
	 */
	void checkWithFile(string path);

	/**
	 * This method check firmware installed on the system with firmwares contained
	 * in the log file and print the results.
	 */
	void checkWithLogDirectory();

};



#endif /* FIRMWAREMANAGER_H_ */
