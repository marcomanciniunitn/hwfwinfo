/*
 * ShellMenuParser.cpp
 *
 *  Created on: Jun 20, 2016
 *      Author: root
 */

#include "ShellMenuParser.h"


ShellMenuParser::ShellMenuParser(){};

void ShellMenuParser::parseAndExecute(int argc, char** argv){
	HWManager* hwManager = new HWManager();
	FirmwareManager* fwManager = new FirmwareManager();
	bool cmdFound = false;

	if(argc < 2 || argc > 6){
		 cout << "Use hwfwinfo -h to see commands" << endl;
	 }else if(argc == 2){
		 if (std::string(argv[1]) == "-h"){
			 cout << "Usage: hwfwinfo [OPTIONS]" << endl;
			 cout << "Options are:" << endl;
			 cout << "-h,				Display all possible commands" << endl;
			 cout << "-hw,				Display all infos about BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system" << endl;
			 cout << "-hw -l,				Generate a log under /var/log/hwfwinfo/HW with infos BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system" << endl;
			 cout << "-hw -l 'Path',			Generate a log under the path specified with infos BIOS, Graphic Cards, Hard Disks, RAM and Network Cards installed on your system" << endl;
			 cout << "-hw -c,		  		Check your system infos with logged infos under /var/log/hwinfo/HW/" << endl;
			 cout << "-hw -c -n,		  	Check your system infos with logged infos under /var/log/hwinfo/HW/, the -n param specifies the revision number to use" << endl;
			 cout << "-hw -c 'Path',		  	Check your system infos with logged infos under the directory specified" << endl;
			 cout << "-hw -c 'Path' -n ,		Check your system infos with logged infos under the directory specified, the -n param specifies the revision number" << endl;
			 cout << "-fw,				Display all infos about FW installed under your /lib/firmware/ directory" << endl;
			 cout << "-fw -l,				Generate a log under /var/log/hwfwinfo/FW with infos about your current firmwares" << endl;
			 cout << "-fw -l 'Path',			Generate a log under the path specified with infos about your current firmwares" << endl;
			 cout << "-fw -c,				Check your current firmware infos with logged infos under /var/log/hwfwinfo/FW" << endl;
			 cout << "-fw -c 'Path',			Check your current firmware infos with a firmware log" << endl;
		 }else if(std::string(argv[1]) == HW_STR){
			 hwManager->populateAllManagers();
			 hwManager->populateAllDevices();
			 hwManager->printAllInfos();
			 cmdFound = true;
		 }else if(std::string(argv[1]) == FW_STR){
			 fwManager->findFirmware();
			 fwManager->printAllFWInfos();
			 cmdFound = true;
		 }
	 }else if(argc == 3){
		 if(std::string(argv[1]) == HW_STR && std::string(argv[2]) == LOG_STR){
			 hwManager->populateAllManagers();
			 hwManager->populateAllDevices();
			 hwManager->generateAllLogs(hwManager->getLogPath());
			 cmdFound = true;
		 }else if(std::string(argv[1]) == HW_STR && std::string(argv[2]) == CHECK_STR){
			 hwManager->populateAllManagers();
			 hwManager->populateAllDevices();
			 hwManager->checkWithDirectory(1);
			 cmdFound = true;

		 }else if(std::string(argv[1]) == FW_STR && std::string(argv[2]) == LOG_STR){
			 fwManager->findFirmware();
			 fwManager->generateLog();
			 cmdFound = true;
		 }else if(std::string(argv[1]) == FW_STR && std::string(argv[2]) == CHECK_STR){
			 fwManager->findFirmware();
			 fwManager->checkWithLogDirectory();
			 cmdFound = true;
		 }
	 }else if(argc == 4){
		 if(std::string(argv[1]) == HW_STR && std::string(argv[2]) == LOG_STR ){
			 hwManager->populateAllManagers();
			 hwManager->populateAllDevices();
			 hwManager->setLogPath(argv[3]);
			 hwManager->generateAllLogs(hwManager->getLogPath());
			 cmdFound = true;
		 }else if(std::string(argv[1]) == FW_STR && std::string(argv[2]) == CHECK_STR){
			 fwManager->findFirmware();
			 fwManager->checkWithFile(argv[3]);
			 cmdFound = true;
		 }else if(std::string(argv[1]) == HW_STR && std::string(argv[2]) == CHECK_STR ){
			 hwManager->populateAllManagers();
			 hwManager->populateAllDevices();
			 hwManager->setLogPath(argv[3]);
			 hwManager->checkWithDirectory(1);
			 cmdFound = true;
		 }else if(std::string(argv[1]) == FW_STR && std::string(argv[2]) == LOG_STR ){
			 fwManager->findFirmware();
			 fwManager->setFilePath(argv[3]);
			 fwManager->generateLog();
			 cmdFound = true;
		 }
	 }else if(argc == 5){
		 if(std::string(argv[1]) == HW_STR && std::string(argv[2]) == CHECK_STR &&  std::string(argv[3]) == REVISION_STR){
			 hwManager->populateAllManagers();
			 hwManager->populateAllDevices();
			 hwManager->checkWithDirectory(stoi(argv[4]));
			 cmdFound = true;
		 }
	 }else if(argc == 6){
		 if(std::string(argv[1]) == HW_STR && std::string(argv[2]) == CHECK_STR &&  std::string(argv[4]) == REVISION_STR){
			 hwManager->populateAllManagers();
			 hwManager->populateAllDevices();
			 hwManager->setLogPath(argv[3]);
			 hwManager->checkWithDirectory(stoi(argv[5]));
			 cmdFound = true;
		 }
	 }

	if(cmdFound == false){
		cout << "Command not found, use -h parameter to see all available commands" << endl;
	}
	delete fwManager;
	delete hwManager;
}
