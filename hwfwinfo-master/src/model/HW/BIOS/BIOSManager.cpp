/*
 * BIOSManager.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#include "BIOSManager.h"

/**
 * Properties positions inside the BaseInfo array.
 */
#define VENDOR_POSITION 0
#define VERSION_POSITION 1
#define RELEASE_DATE_POSITION 2
#define ROM_SIZE_POSITION 3
#define REVISION_POSITION 4
#define FW_REVISION_POSITION 5


/**
 * Represents a BIOSManager.
 */
BIOSManager::BIOSManager(){
	CommandManager<int>* cmdManager = new CommandManager<int>();

	this->fileName = "BIOS Infos.txt";

	this->inFileName = "---BIOS INFOs---";

	this->onDifferenceName = "BIOSes";

	this->numberOfInfos = 6;

	this->numberOfCommands = 6;

    this->numberOfDevicesCommand = new Command();
	this->checkCommand = new Command();

	numberOfDevicesCommand->setCommand("dmidecode --type BIOS | grep -i 'BIOS Information' | wc -l");
	numberOfDevicesCommand->setFilter("");

	this->numberOfDevices = cmdManager->getInfoFromCommand(this->numberOfDevicesCommand);

	this->devices = new HWDevice*[this->numberOfDevices];
	this->commands = new Command*[this->numberOfCommands];

	this->deviceCreator = new BiosCreator();

}

void BIOSManager::setCommands(int devicePosition){
    Command* vendorCommand = new Command();
    Command* versionCommand = new Command();
    Command* releaseDateCommand = new Command();
    Command* romSizeCommand = new Command();
    Command* revisionCommand = new Command();
    Command* FWRevisionCommand = new Command();

    string filterString = " | sed -n " + to_string(devicePosition) + "p";

    vendorCommand->setCommand("dmidecode --type BIOS | grep -i 'vendor'" + filterString);
    vendorCommand->setFilter("Vendor: ");

    versionCommand->setCommand("dmidecode --type BIOS | grep -i 'version'" + filterString);
    versionCommand->setFilter("Version: ");

    releaseDateCommand->setCommand("dmidecode --type BIOS | grep -i 'release date'" + filterString);
    releaseDateCommand->setFilter("Release Date: ");

    romSizeCommand->setCommand("dmidecode --type BIOS | grep -i 'ROM size'" + filterString );
    romSizeCommand->setFilter("ROM Size: ");

    revisionCommand->setCommand("dmidecode --type BIOS | grep -i 'BIOS revision'" + filterString );
    revisionCommand->setFilter("BIOS Revision: ");

    FWRevisionCommand->setCommand("dmidecode --type BIOS | grep -i 'firmware revision'" + filterString);
    FWRevisionCommand->setFilter("Firmware Revision: ");


    this->commands[VENDOR_POSITION] = vendorCommand;
    this->commands[VERSION_POSITION] = versionCommand;
    this->commands[RELEASE_DATE_POSITION] = releaseDateCommand;
    this->commands[ROM_SIZE_POSITION] = romSizeCommand;
    this->commands[REVISION_POSITION] = revisionCommand;
    this->commands[FW_REVISION_POSITION] = FWRevisionCommand;
}


BaseDifference** BIOSManager::generateLogDifference(){
	BaseDifference** logDifferences;

	logDifferences = new BaseDifference*[this->numberOfInfos];
	logDifferences[0] = new BaseLogDifference<string>();
	logDifferences[0]->setProp("Vendor");


	logDifferences[1] = new BaseLogDifference<string>();
	logDifferences[1]->setProp("Version");

	logDifferences[2] = new BaseLogDifference<string>();
	logDifferences[2]->setProp("Release date");

	logDifferences[3] = new BaseLogDifference<int>();
	logDifferences[3]->setProp("ROM Size");

	logDifferences[4] = new BaseLogDifference<string>();
	logDifferences[4]->setProp("Revision");

	logDifferences[5] = new BaseLogDifference<string>();
	logDifferences[5]->setProp("FW Revision");

	return logDifferences;
}

