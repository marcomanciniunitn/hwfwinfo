/*
 * HWManager.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#include "HWManager.h"

#define NETWORKMANAGER_POSITION 0
#define MEMORYDEVICEMANAGER_POSITION 1
#define GRAPHICCARDMANAGER_POSITION 2
#define HDDMANAGER_POSITION 3
#define BIOSMANAGER_POSITION 4

const char BIOS_STR[] = "BIOSes";
const char GCARD_STR[] = "Graphic cards";
const char HDD_STR[] = "HDDs";
const char MEM_STR[] = "Memory devices";
const char NET_STR[] = "Network cards";


HWManager::HWManager(){
	this->numberOfDevices = 0;
	this->numberOfManagers = MANAGERS_COUNT;
	this->deviceManagers = new DeviceManager*[MANAGERS_COUNT];
	this->logPath = "/var/log/hwfwinfo/HW/";
}

HWManager::~HWManager(){
	for(int i = 0; i < this->numberOfManagers; i++){
		this->deviceManagers[i]->~DeviceManager();
	}

}

void HWManager::setLogPath(string path){
	this->logPath = path;
}

string HWManager::getLogPath(){
	return this->logPath;
}

void HWManager::populateManager(checkChoise choise){
	switch(choise){
		case bios:
		{
			this->deviceManagers[BIOS_MANAGER_POSITION] = new BIOSManager();
			break;
		}
		case gcard:
		{
			this->deviceManagers[GCARD_MANAGER_POSITION] = new GraphicCardManager();
			break;
		}
		case hdd:
		{
			this->deviceManagers[HDD_MANAGER_POSITION] = new HardDiskManager();
			break;
		}
		case memory:
		{
			this->deviceManagers[MEMORY_MANAGER_POSITION] = new MemoryDeviceManager();
			break;
		}
		case ncard:
		{
			this->deviceManagers[NET_MANAGER_POSITION] = new NetworkCardManager();
			break;
		}
	}

}
void HWManager::populateAllManagers(){

	this->populateManager(bios);

	this->populateManager(gcard);

	this->populateManager(hdd);

	this->populateManager(hdd);

	this->populateManager(memory);

	this->populateManager(ncard);
}

void HWManager::populateDevices(checkChoise choise){
	this->deviceManagers[choise]->findDevices();
}

void HWManager::populateAllDevices(){
	this->numberOfDevices = 0;

	for(int i = 0; i < this->numberOfManagers; i++){
		this->deviceManagers[i]->findDevices();
		this->numberOfDevices += this->deviceManagers[i]->getNumberOfDevices();
	}

}

int HWManager::getNumberOfDevices(){
	return this->numberOfDevices;
}


string HWManager::generateLogDir(string path){

	if(path.find("/HW") == std::string::npos){
		path.append("HW/");
	}
	mkdir(path.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	return path;
}


void HWManager::generateAllLogs(string path){
	string completePath = this->generateLogDir(path);
	for(int i = 0; i < this->numberOfManagers; i++){
		this->deviceManagers[i]->generateLog(completePath);
	}
}


void HWManager::printAllInfos(){
	cout << "Number of devices retrieved: " << this->numberOfDevices << endl;
	for(int i = 0; i < this->numberOfManagers; i++){
		this->deviceManagers[i]->printAllInfos();
		cout << endl;
	}
}

void HWManager::checkWithDirectory(int scanId){
	for(int i = 0; i < this->numberOfManagers; i++){
		string completePath = this->logPath;
		completePath.append(this->deviceManagers[i]->getFileName());
		this->checkWithFile(completePath, static_cast<checkChoise>(i), scanId);
	}
}


void HWManager::checkWithFile(string path, checkChoise choise, int scanId){
	int errors, size, added, removed;
	BaseInfoVisitor visitor;

	//Retrieve all differences from the devicemanager used (parameter choise)
	BaseDifference*** logDifference = this->deviceManagers[choise]->checkDevicesFromFile(path,
			errors, size, added, removed, scanId);

	//Print the result given from the compare procedure.
	if(errors == 0){
		cout << "\t" << this->deviceManagers[choise]->onDifferenceName << " Checks" << endl << endl;

		if(added > 0){
			cout << "It would seem that " << added << " " << this->deviceManagers[choise]->onDifferenceName
					<< " were added" << endl << endl;
		}
		if(removed > 0) {
			cout << "It would seem that " << removed << " " << this->deviceManagers[choise]->onDifferenceName
					<< " were removed" << endl << endl;
		}

		for(int i = 0; i < size; i++){
			if(i == size - removed){
				cout << "WARNING! These " << this->deviceManagers[choise]->onDifferenceName << " seems to be removed from the last scan!" << endl;
			}
			if( i == size - added){
				cout << "WARNING! These " << this->deviceManagers[choise]->onDifferenceName << " seems to be added from the last scan!" << endl;
			}
			for(int j = 0; j < this->deviceManagers[choise]->numberOfInfos; j++){

				cout << "[" << i << "] ";
				logDifference[i][j]->visitToPrint(visitor);
			}
			cout << endl;
		}
		cout << endl;
	}else{
		cout <<" File not detected or not containing informations" << endl << endl;
	}
}

