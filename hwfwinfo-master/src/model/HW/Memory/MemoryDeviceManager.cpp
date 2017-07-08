/*
 * MemoryDeviceManager.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#include "MemoryDeviceManager.h"


MemoryDeviceManager::MemoryDeviceManager(){
	CommandManager<int>* cmdManager = new CommandManager<int>();

	this->fileName = "Memory Module Infos.txt";

	this->inFileName = "---MEMORY INFOs---";

	this->onDifferenceName = "Memory devices";

	this->numberOfInfos = 5;

	this->numberOfCommands = 5;

	this->numberOfDevicesCommand = new Command();
	this->checkCommand = new Command();

	numberOfDevicesCommand->setCommand("sudo dmidecode --type 17 | grep -i 'Memory Device' | wc -l");
	numberOfDevicesCommand->setFilter("");

	this->numberOfDevices = cmdManager->getInfoFromCommand(this->numberOfDevicesCommand);

	this->devices = new HWDevice*[this->numberOfDevices];
	this->commands = new Command*[this->numberOfCommands];

	this->deviceCreator = new MemoryCreator();
}
void MemoryDeviceManager::setCommands(int position){
	Command* serialNumberCommand = new Command();
	Command* sizeCommand = new Command();
	Command* speedCommand = new Command();
	Command* typeCommand = new Command();
	Command* manufacturerCommand = new Command();
	string filterString = " | sed -n " + to_string(position) + "p";

	serialNumberCommand->setCommand("dmidecode --type 17 | grep -i 'Serial Number: '" + filterString);
	serialNumberCommand->setFilter("Serial Number: ");

	sizeCommand->setCommand("dmidecode --type 17 | grep -i 'Size: '" + filterString);
	sizeCommand->setFilter("Size: ");

	speedCommand->setCommand("dmidecode --type 17 | grep -i 'Speed: '" + filterString);
	speedCommand->setFilter("Speed: ");

	typeCommand->setCommand("dmidecode --type 17 | grep -i 'Type: '" + filterString);
	typeCommand->setFilter("Type: ");

	manufacturerCommand->setCommand("dmidecode --type 17 | grep -i 'Manufacturer: '" + filterString);
	manufacturerCommand->setFilter("Manufacturer: ");

	this->commands[SERIAL_POSITION] = serialNumberCommand;
	this->commands[SIZE_POSITION] = sizeCommand;
	this->commands[MANUFACTURER_POSITION] = manufacturerCommand;
	this->commands[SPEED_POSITION] = 	speedCommand;
	this->commands[TYPE_POSITION] = 	typeCommand;
}

BaseDifference** MemoryDeviceManager::generateLogDifference(){
	BaseDifference** logDifferences;

	logDifferences = new BaseDifference*[this->numberOfInfos];

	logDifferences[0] = new BaseLogDifference<string>();
	logDifferences[0]->setProp("Serial Number");


	logDifferences[1] = new BaseLogDifference<string>();
	logDifferences[1]->setProp("Manufacturer");

	logDifferences[2] = new BaseLogDifference<int>();
	logDifferences[2]->setProp("Speed");

	logDifferences[3] = new BaseLogDifference<string>();
	logDifferences[3]->setProp("Type");

	logDifferences[4] = new BaseLogDifference<int>();
	logDifferences[4]->setProp("Size");

	return logDifferences;
}

