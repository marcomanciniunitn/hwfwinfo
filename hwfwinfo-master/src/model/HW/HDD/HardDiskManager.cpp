/*
 * HardDiskManager.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#include "HardDiskManager.h"

/**
 * Properties positions inside the BaseInfo array.
 */
#define MODEL_NUMBER_POSITION 0
#define SERIAL_NUMBER_POSITION 1
#define FIRMWARE_REVISION_POSITION 2

HardDiskManager::HardDiskManager(){
	CommandManager<int>* cmdManager = new CommandManager<int>();

	this->fileName = "HDD Infos.txt";

	this->inFileName = "---HDD INFO---";

	this->onDifferenceName = "HDDs";

	this->numberOfInfos = 3;

	this->numberOfCommands = 3;

	this->numberOfDevicesCommand = new Command();
	this->checkCommand = new Command();

	numberOfDevicesCommand->setCommand("hdparm -I /dev/sda | grep -i 'Model Number: ' | wc -l");
	numberOfDevicesCommand->setFilter("");

	this->numberOfDevices = cmdManager->getInfoFromCommand(this->numberOfDevicesCommand);

	this->devices = new HWDevice*[this->numberOfDevices];
	this->commands = new Command*[this->numberOfCommands];

	this->deviceCreator = new HDDCreator();
}

void HardDiskManager::setCommands(int devicePosition){
	Command* modelNumberCommand = new Command();
	Command* serialNumberCommand = new Command();
	Command* firmwareRevisionCommand  = new Command();

	string filterString = " | sed -n " + to_string(devicePosition) + "p";


	modelNumberCommand->setCommand("hdparm -I /dev/sda | grep -i 'Model Number: '" + filterString);
	modelNumberCommand->setFilter("Model Number: ");

	serialNumberCommand->setCommand("hdparm -I /dev/sda | grep -i 'Serial Number: '" + filterString);
	serialNumberCommand->setFilter("Serial Number: ");

	firmwareRevisionCommand->setCommand("hdparm -I /dev/sda | grep -i 'Firmware Revision: '" + filterString);
	firmwareRevisionCommand->setFilter("Firmware Revision: ");

	this->commands[MODEL_NUMBER_POSITION] = modelNumberCommand;
	this->commands[SERIAL_NUMBER_POSITION] = serialNumberCommand;
	this->commands[FIRMWARE_REVISION_POSITION] = firmwareRevisionCommand;
}

BaseDifference** HardDiskManager::generateLogDifference(){
	BaseDifference** logDifferences;

	logDifferences = new BaseDifference*[this->numberOfInfos];

	logDifferences[0] = new BaseLogDifference<string>();
	logDifferences[0]->setProp("Serial Number");


	logDifferences[1] = new BaseLogDifference<string>();
	logDifferences[1]->setProp("Model Number");

	logDifferences[2] = new BaseLogDifference<string>();
	logDifferences[2]->setProp("Firmware Revision");

	return logDifferences;
}

