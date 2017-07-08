/*
 * DeviceManager.h
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#ifndef MODEL_DEVICEMANAGER_H_
#define MODEL_DEVICEMANAGER_H_

#include "HWDevice.h"
#include <string>
#include <fstream>
#include <time.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

/*#include "../Visitors/BaseInfoVisitor.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../../utils/BaseInfoComparator.h"
#include "BaseDifference.h"
#include "BaseLogDifference.h"
*/
#include "../../../utils/BaseInfoComparator.h"
#include "BaseDifference.h"
#include "DeviceCreator.h"

#define ID_STRING "---Scan Date"



using namespace std;

/**
 * Abstract class used to manage completely a group of specific @HWDevices
 *
 */
class DeviceManager{
	friend class HWManager;
protected:
	//Creator used to instaniate objects
	DeviceCreator* deviceCreator;

	//default path for log files
	string fileName;

	//default string to identify an @HWDevice in a logfile
	string inFileName;

	//string to identify a difference on a log.
	string onDifferenceName;

	//number of an @HWDevice properties
	int numberOfInfos;

	//Command to retrieve the device's number retrieved on the system
	Command* numberOfDevicesCommand;

	//number of devices found on the system
	int numberOfDevices;

	//devices retrieved on the system
	HWDevice** devices;

	//@Command array and his size used to retrieve informations about devices
	Command** commands;
	int numberOfCommands;

	//Command to check the existence of the HW device
	Command* checkCommand;

	/**
	 * Method used to backup a file content.
	 *
	 * @param path the file path
	 * @return a string list populed with backuped lines
	 */
	list<string> saveFileContent(string path){
		list<string> lines;
		std::ifstream infile(path.c_str());
		string line;
		while(std::getline(infile,line)){
			lines.push_back(line);
		}
		return lines;
	}


	/**
	 * This abstract method will produce a Fake (Specified by the concrete classes) Device
	 * that will be used later to compare devices
	 */
	HWDevice* generateFakeDevice(){
		return this->deviceCreator->createFakeDevice();
	}

	/**
	 * Generate and return a new device in a specific position.
	 *
	 * @param position used by the device
	 * @return the generated device
	 */
	HWDevice* generateNewDevice(int position){
		return this->deviceCreator->createDefaultDevice(position);
	}


	/**
	 * This method check two different @HWDevice between them and return a difference log.
	 */
	BaseDifference** checkDevices(HWDevice* orig, HWDevice* toCheck){
		//Generate a log difference specific for each implementation of a DeviceManager.
		BaseDifference** logDifference = this->generateLogDifference();

		//Cicle all informations and use the BaseInfoComparator to compare each info and populate the logdifference.
		for(int i = 0; i < this->numberOfInfos; i++){
			BaseInfoComparator* comparator = new BaseInfoComparator();
			comparator->compare(orig->getProperty(i), toCheck->getProperty(i), logDifference[i]);
		}

		return logDifference;
	}

	/**
	 * Check the existences of a specific device.
	 *
	 * @return true if some device exists, false otherwise
	 */
	virtual bool checkDevicesExistence(){
		helper_cmdManager* commandManager = new helper_cmdManager();

		//If the execution of the checkcommand is not empty, then something is being found.
		if((commandManager->GetStdoutFromCommand(this->checkCommand)) != ""){
			return true;
		}
		return false;
	}

	/**
	 * Generate and populate the devices array.
	 * This method will be overwritten from the specific classes (BIOSManager, HDDManager, ecc..)
	 */
	void generateAllDevices(){
		for(int i = 0; i < this->numberOfDevices; i++){
			this->devices[i] = this->deviceCreator->createDefaultDevice(i);
		}
	}
	/**
	 * Set all commands used to retrieve infos.
	 * This method will be overwritten from the specific classes (BIOS, HDD, ecc...)
	 *
	 * @param devicePosition the device position in the devices array
	 */
	virtual void setCommands(int devicePosition) = 0;


	/**
	 * Set all devices informations, by default this method set all properties using the
	 * commands array and pass it, with a visitor, to the property
	 *
	 * @param position the device position in the device array
	 */
	virtual void setAllInfos(int position){
		BaseInfoVisitor setInfoVisitor;

		//Setting commands for the specific device taken in analysis.
		this->setCommands(position);

		//Cicle all commands and set realive info. Generally the execution of a command is related to an informations,
		//in other cases the specific devicemanager could overwrite this method and use another algorithm to set all informations
		for(int j = 0; j < this->numberOfCommands; j++){
			//Taking the property and visit with the BaseInfoVisitor to set his value.
			BaseProperty* property = this->devices[position-1]->getProperty(j);
			property->visitValueWithBaseCommand(setInfoVisitor, this->commands[j]);
		}
	}

	/**
	 * Return the number of devices retrieved in a logFile.
	 *
	 * @param path the log file path
	 * @param scanNumber the scan number to use
	 * @return number of devices retrieved in a file
	 */
	int countDevicesFromFile(string path, int scanNumber){
		int numbeOfDevices = 0;
		//index used to identify the scan number
		int index = 0;
		StringManager* strManager = new StringManager();

		std::ifstream infile(path.c_str());
		string line;

		while(std::getline(infile,line)){
			//If the line is a line containing the timestamp (the timestamp identify a block containing the scan informations)
			//then increment the current index.
			if(strManager->getSubString(line, ":", true ).compare(ID_STRING) == 0){
				index++;
				//The algotithm finished because all the scan informations has been retrieved.
				if(index == scanNumber + 1){
					return numberOfDevices;
				}
				//If we are scanning the desired scan number and we found a line containing the filename it means
				//that there is a block of informations for a specific device then there is device => increment the number of devices present.
			}if(index == scanNumber){
				if(line.compare(this->inFileName) == 0){
					numbeOfDevices++;
				}
			}

		}
		return numbeOfDevices;
	}

	/**
	 * Return an HWDevice* array from a log file passed as parameter.
	 *
	 * @param path the log file path
	 * @param err errors[ 0 = OK, 1 = NO DEVICES FOUND]
	 * @param size the output array size
	 * @param scanNumber the scan id to use
	 * @return HWDevice* array
	 */
	HWDevice** retrieveFromFile(string path, int& err, int& size, int scanNumber){
			StringManager* stringManager = new StringManager();
			BaseInfoVisitor setInfoVisitor;
			HWDevice** devicesRetrieved;

			//Same scanIndex used in method countDevicesFromFile
			int scanIndex = 0;

			//Count devices from file.
			int numberOfDevices = countDevicesFromFile(path, scanNumber);
			size = -1;

			//Property counter used to set the specific information.
			int counterInfos = 0;

			if(numberOfDevices == 0){
				//No devices found...
				err = 1;
			}else{
				//Devices found!
				err = 0;
				devicesRetrieved = new HWDevice*[numberOfDevices];
				std::ifstream infile(path.c_str());
				string line;

				while(std::getline(infile, line)){
					//If the line is a line containing the timestamp (the timestamp identify a block containing the scan informations)
					//then increment the current index.
					if(stringManager->getSubString(line, ":" ,true).compare(ID_STRING) == 0){
						scanIndex++;
						//The algotithm finished because all the scan informations has been retrieved.
						if(scanIndex == scanNumber+1){
							size = size+1;
							return devicesRetrieved;
						}
						//We are scanning lines belonging to the desired scan block
					}else if(scanIndex == scanNumber){
						//If the line is containing the line that identifies a device in the log file then increment the index of the the
						//device array to return, generate a new device in the index position and reset the proprerty counter.
						if(line.compare(this->inFileName) == 0){
							size = size +1;
							devicesRetrieved[size] = generateNewDevice(size);
							counterInfos = 0;
						}else{
							string property,value;
							//Take the property name from the line scanned.
							property = stringManager->getSubString(line,":",true);

							//Take the property value from the line scanned.
							value = stringManager->getSubString(line,":", false);
							//Visit the device property and set his value.
							if(property.compare(this->devices[0]->getProperty(counterInfos)->getProperty()) == 0) {
								devicesRetrieved[size]->getProperty(counterInfos)->visitToAssign(setInfoVisitor, value);
								counterInfos++;
							}
						}
					}

				}

				size = size+1;
			}
			return devicesRetrieved;
		}

		/**
		 * This abstract method will produce a BaseDifference, it will be used to compare different
		 * @HWDevice between them.
		 *
		 * @result the differences to populate
		 */
		virtual BaseDifference** generateLogDifference() = 0;



public:

	DeviceManager(){
	};

	virtual ~DeviceManager(){
		for(int i = 0; i < this->numberOfDevices; i++){
			delete this->devices[i];
		}
		delete[] this->devices;

		for(int i = 0; i < this->numberOfCommands; i++){
			delete this->commands[i];
		}
		delete[] this->commands;

		delete numberOfDevicesCommand;
		delete this->deviceCreator;
	}

	/**
	 * Return the number of devices
	 *
	 * @return number of devices
	 */
	int getNumberOfDevices(){
		return this->numberOfDevices;
	}

	/**
	 * Return the devices array
	 *
	 * @return devices array
	 */
	HWDevice** getDevices(){
		return this->devices;
	}


	/**
	 * Return the file path
	 */
	string getFileName(){
		return this->fileName;
	}


	/**
	 * Print all infos about devices with the following format:
	 * PROPERTY : VALUE
	 */
	void printAllInfos(){
		BaseInfoVisitor setInfoVisitor;
		for(int i = 0; i < numberOfDevices; i++){
			cout << "\t[" << i+1 << "]" << this->inFileName << endl;

			for(int j = 0; j < numberOfInfos; j++){
				this->devices[i]->getProperty(j)->visitToPrint(setInfoVisitor);
			}
		}
	}


	/**
	 * Find all devices in the system and set it the devices array of the class
	 */
	virtual void findDevices(){
		//Generate the device array using the correct size.
		this->generateAllDevices();
		//Scan the system and populate the array.
		for(int i = 1; i <= this->numberOfDevices; i++) {
			this->devices[i-1] = this->generateNewDevice(i);
			this->setAllInfos(i);
		}
	}

	/**
	 * Generate a log under the fileName path. This method iterate for each device and visit each
	 * information with a visitor able to log them.
	 */
	virtual void generateLog(string path){
		BaseInfoVisitor printVisitor;
		StringManager* strManager = new StringManager();

		//Create che complete path.
		string completePath = path.append(this->fileName);

		//Backup all lines.
		list<string> backupLines = saveFileContent(completePath);
		remove (completePath.c_str());
		FILE* pFile = fopen(completePath.c_str(), "w");

		string id = strManager->generateTimeStamp();

		//Printing the timestamp and cycling all devices to print their informations using the BaseInfoVisitor.
		fprintf(pFile, id.c_str());
		for(int i = 0; i < numberOfDevices; i++){
			fprintf(pFile, "%s\n", inFileName.c_str());
			for(int j = 0; j < this->numberOfInfos; j++){
				this->devices[i]->getProperty(j)->visitToLog(printVisitor, pFile);
			}
		}

		//Print all backupped lines and close the file.
		list<string>::iterator iterator;
		for(iterator=backupLines.begin(); iterator!=backupLines.end(); iterator++){
			fprintf(pFile, (*iterator).c_str());
			fprintf(pFile, "\n");
		}
		fclose(pFile);

	}



	/**
	 * This method checks devices retrieved on the machine with a well-formed log passed by param.
	 * Use only after method findDevices is been used.
	 *
	 * @param path log file path
	 * @param err error message (0 = OK, -1 = SOMETHING WENT WRONG)
	 * @param size difference log size
	 * @param added number of devices apparently added
	 * @param removed number of devices apparently removed
	 */
	BaseDifference*** checkDevicesFromFile(string path, int &err, int& size,int& added, int& removed, int scanId){
			//difference log to return
			BaseDifference*** log;

			//Devices retrieved from the filepath
			HWDevice** fromFileDevices;

			//error message from file retriving phase
			int errorFromFile;

			int sizeFromFile;

			err = 0;
			size = 0;
			added = 0;
			removed = 0;

			//Retrieve all devices from file.
			fromFileDevices = this->retrieveFromFile(path, errorFromFile, sizeFromFile, scanId);

			size = max(this->numberOfDevices, sizeFromFile);
			if(size == 0){
				//SOMETHING WENT WRONG
				err = -1;
			}else{
				log = new BaseDifference**[size];
				int min = std::min(this->numberOfDevices, sizeFromFile);
				int i = 0;
				HWDevice* fakeDevice;

				//Check firsts devices, to be equals they have to be in the same position and with the same properties.
				for(i = 0; i < min; i++){
					log[i] = this->checkDevices(this->devices[i], fromFileDevices[i]);
				}
				//Something has been added!
				if(this->numberOfDevices > sizeFromFile){
					fakeDevice = this->generateFakeDevice();
					for(int j = i; j < this->numberOfDevices; j++){
						log[j] = this->checkDevices(fakeDevice,this->devices[j]);
						added++;
					}
					//Something has been removed
				}else if(sizeFromFile > this->numberOfDevices){
					fakeDevice = this->generateFakeDevice();
					for(int k = i; k < sizeFromFile; k++){
						log[k] = this->checkDevices(fakeDevice, fromFileDevices[k]);
						removed++;
					}
				}
			}
			return log;
		}

};





#endif /* MODEL_DEVICEMANAGER_H_ */
