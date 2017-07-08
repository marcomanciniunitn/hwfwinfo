/*
 * GraphicCardManager.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#include "GraphicCardManager.h"

/**
 * Properties positions inside the BaseInfo array.
 */
#define PRODUCT_POSITION 0
#define VENDOR_POSITION 1
#define ID_POSITION 2
#define CLOCK_POSITION 3



GraphicCardManager::GraphicCardManager(){
	CommandManager<int>* cmdManager = new CommandManager<int>();

	this->fileName = "Graphic Card Infos.txt";

	this->inFileName = "---GRAPHIC CARD INFO---";

	this->onDifferenceName = "Graphic Cards";

	this->numberOfInfos = 4;

	this->numberOfCommands = 4;

	this->numberOfDevicesCommand = new Command();
	this->checkCommand = new Command();

	numberOfDevicesCommand->setCommand("lshw -c video -disable USB -disable SCSI -disable PCI -disable isapnp | grep -i 'description' | wc -l");
	numberOfDevicesCommand->setFilter("");
	this->numberOfDevices = cmdManager->getInfoFromCommand(this->numberOfDevicesCommand);

	this->devices = new HWDevice*[this->numberOfDevices];
	this->commands = new Command*[this->numberOfCommands];

	this->deviceCreator = new GraphicCardCreator();
}

void GraphicCardManager::setCommands(int devicePosition) {
	Command* productCommand = new Command();
	Command* vendorCommand = new Command();
	Command* physicalIDCommand = new Command();
	Command* clockCommand = new Command();

	string filterString = " | sed -n " + to_string(devicePosition) + "p";

	productCommand->setCommand("sudo lshw -c video -disable USB -disable SCSI -disable PCI -disable isapnp  | grep -i 'product: '" + filterString);
	productCommand->setFilter("product: ");

	vendorCommand->setCommand("sudo lshw -c video -disable USB -disable SCSI -disable PCI -disable isapnp  | grep -i 'vendor: '" + filterString);
	vendorCommand->setFilter("vendor: ");

	physicalIDCommand->setCommand("sudo lshw -c video -disable USB -disable SCSI -disable PCI -disable isapnp  | grep -i 'physical id: '" + filterString);
	physicalIDCommand->setFilter("physical id: ");

	clockCommand->setCommand("sudo lshw -c video -disable USB -disable SCSI -disable PCI -disable isapnp  | grep -i 'clock: '" + filterString);
	clockCommand->setFilter("clock: ");
	clockCommand->setSecondFilter("M");

	this->commands[PRODUCT_POSITION] = productCommand;
	this->commands[VENDOR_POSITION] = vendorCommand;
	this->commands[ID_POSITION] = 	physicalIDCommand;
	this->commands[CLOCK_POSITION] = 	clockCommand;
}

BaseDifference** GraphicCardManager::generateLogDifference(){
	BaseDifference** logDifferences;

	logDifferences = new BaseDifference*[this->numberOfInfos];

	logDifferences[0] = new BaseLogDifference<string>();
	logDifferences[0]->setProp("Product");


	logDifferences[1] = new BaseLogDifference<string>();
	logDifferences[1]->setProp("Vendor");

	logDifferences[2] = new BaseLogDifference<int>();
	logDifferences[2]->setProp("Physical ID");

	logDifferences[3] = new BaseLogDifference<int>();
	logDifferences[3]->setProp("Clock");

	return logDifferences;

}


