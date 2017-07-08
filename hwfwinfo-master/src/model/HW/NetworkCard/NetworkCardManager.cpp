/*
 * NetworkCardManager.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#include "NetworkCardManager.h"

#define RETRIEVE_COMMAND_POSITION 0

NetworkCardManager::NetworkCardManager(){
	CommandManager<int>* cmdManager = new CommandManager<int>();

	this->fileName = "Network Card Infos.txt";

	this->inFileName = "---NETWORK CARD INFO---";

	this->onDifferenceName = "Network Cards";

	this->numberOfInfos = 4;

	this->numberOfCommands = 1;

	this->numberOfDevicesCommand = new Command();
	this->checkCommand = new Command();

	numberOfDevicesCommand->setCommand("lshw -class network -disable USB -disable SCSI -disable PCI -disable isapnp | grep -i '*-network' | wc -l");
	numberOfDevicesCommand->setFilter("");
	this->numberOfDevices = cmdManager->getInfoFromCommand(this->numberOfDevicesCommand);

	this->devices = new HWDevice*[this->numberOfDevices];
	this->commands = new Command*[this->numberOfCommands];

	this->deviceCreator = new NetworkCardCreator();
}


void NetworkCardManager::setAllInfos(int position){
	BaseInfoVisitor setInfoVisitor;

	this->setCommands(position);
	CommandManager<string>* strCmdManager = new CommandManager<string>();
	StringManager* strManager = new StringManager();

	string result = strCmdManager->getInfoFromCommand(this->commands[RETRIEVE_COMMAND_POSITION]);

	string description = strManager->getProperty(result, "description");
	this->devices[position - 1]->getProperty(DESCRIPTION_POSITION)->visitToAssign(setInfoVisitor, description);

	string product = strManager->getProperty(result, "product");
	this->devices[position - 1]->getProperty(PRODUCT_POSITION)->visitToAssign(setInfoVisitor, product);

	string serial = strManager->getProperty(result, "serial");
	this->devices[position - 1]->getProperty(SERIAL_POSITION)->visitToAssign(setInfoVisitor, serial);

	string vendor = strManager->getProperty(result, "vendor");
	this->devices[position - 1]->getProperty(VENDOR_POSITION)->visitToAssign(setInfoVisitor, vendor);

}

void NetworkCardManager::setCommands(int devicePosition) {

	CommandManager<int>* intCmdManager = new CommandManager<int>();

	Command* startingPositionCommand = new Command();
	Command* endingPositionCommand = new Command();
	Command* retrieveAllInfosCommand = new Command();
	int start, end;
	string result;

	startingPositionCommand->setCommand("lshw -class network -disable USB -disable SCSI -disable PCI -disable isapnp | grep -n *-network | cut -d ':' -f 1 | sed -n "
		+ to_string(devicePosition) + "p");
	startingPositionCommand->setFilter("");

	start = intCmdManager->getInfoFromCommand(startingPositionCommand) + 1;

	if(devicePosition == numberOfDevices){
		endingPositionCommand->setCommand("lshw -class network -disable USB -disable SCSI -disable PCI -disable isapnp| wc -l");
		endingPositionCommand->setFilter("");
		end = intCmdManager->getInfoFromCommand(endingPositionCommand) - start + 1 ;
	}else{
		endingPositionCommand->setCommand("lshw -class network -disable USB -disable SCSI -disable PCI -disable isapnp | grep -n *-network | cut -d ':' -f 1 | sed -n "+
				to_string(devicePosition + 1) +"p");
		endingPositionCommand->setFilter("");
		end = intCmdManager->getInfoFromCommand(endingPositionCommand) - start;
	}


	retrieveAllInfosCommand->setCommand("lshw -class network -disable SCSI -disable PCI -disable isapnp | tail -n +" + to_string(start)+ " | head -n " + to_string(end));
	retrieveAllInfosCommand->setFilter("");

	this->commands[RETRIEVE_COMMAND_POSITION] = retrieveAllInfosCommand;

}

BaseDifference** NetworkCardManager::generateLogDifference(){
	BaseDifference** logDifferences;

	logDifferences = new BaseDifference*[this->numberOfInfos];

	logDifferences[0] = new BaseLogDifference<string>();
	logDifferences[0]->setProp("Serial Number");


	logDifferences[1] = new BaseLogDifference<string>();
	logDifferences[1]->setProp("Product");

	logDifferences[2] = new BaseLogDifference<string>();
	logDifferences[2]->setProp("Vendor");

	logDifferences[3] = new BaseLogDifference<string>();
	logDifferences[3]->setProp("Description");

	return logDifferences;
}


