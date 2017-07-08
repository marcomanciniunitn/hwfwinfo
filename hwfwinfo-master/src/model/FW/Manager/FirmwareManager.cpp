/*
 * FirmwareManager.cpp
 *
 *  Created on: Jun 1, 2016
 *      Author: root
 */

#include "FirmwareManager.h"




FirmwareManager::~FirmwareManager(){
	list<Firmware*>::iterator iterator;
	for(iterator = this->firmwares.begin(); iterator != this->firmwares.end(); iterator++){
		//this->firmwares.remove((*iterator));
		delete (*iterator);
	}
	//delete this->firmwares;

}

FirmwareManager::FirmwareManager(){
	this->filePath = "/var/log/hwfwinfo/FW/";
	this->fileName = "Firmwares Infos.txt";
	this->inFileName = "---FIRMWARE---";
}


bool isDir(string dir)
{
    struct stat fileInfo;
    stat(dir.c_str(), &fileInfo);
    if (S_ISDIR(fileInfo.st_mode)) {
        return true;
    } else {
        return false;
    }
}

string FirmwareManager::getFilePath(){
	return this->filePath;
}

void FirmwareManager::setFilePath(string path){
	this->filePath = path;
}
void FirmwareManager::listFiles(string baseDir, bool recursive)
{
	CommandManager<string>* cmdManager = new CommandManager<string>();
	StringManager* strManager = new StringManager();
	Command* retrieveCommand = new Command();
    DIR *dp;
    struct dirent *dirp;
    if ((dp = opendir(baseDir.c_str())) == NULL) {
        cout << "[ERROR: " << errno << " ] Couldn't open " << baseDir << "." << endl;
        return;
    } else {
        while ((dirp = readdir(dp)) != NULL) {
            if (dirp->d_name != string(".") && dirp->d_name != string("..")) {
                if (isDir(baseDir + dirp->d_name) == true && recursive == true) {
                    listFiles(baseDir + dirp->d_name + "/", true);
                } else {
                	//creating command to retrieve the sha256
                    string sha256cmd = "sha256sum ";
                    sha256cmd.append(baseDir);
                    sha256cmd.append(dirp->d_name);

                    //setting the command
                    retrieveCommand->setCommand(sha256cmd);
                    retrieveCommand->setFilter("");
                    string sha256 = cmdManager->getInfoFromCommand(retrieveCommand);
                    sha256 = strManager->getSubString(sha256, " ", true);

                    Firmware* fw = new Firmware();
                    fw->setFileName(dirp->d_name);
                    fw->setSHA256(strManager->getSubString(sha256, " ", true));
                    fw->setDirectory(baseDir);

                    this->firmwares.push_back(fw);

                }
            }
        }
        closedir(dp);
        delete cmdManager;
        delete retrieveCommand;
    }
}
void FirmwareManager::findFirmware(){
	this->listFiles("/lib/firmware/", true);
}

void FirmwareManager::printAllFWInfos(){
	list<Firmware*>::iterator iterator;
	for(iterator=this->firmwares.begin(); iterator!=this->firmwares.end(); iterator++){
		cout << this->inFileName << endl;
		cout << "Firmware file: " << (*iterator)->getFileName() << endl;
		cout << "Firmware directory: " << (*iterator)->getDirectory() << endl;
		cout << "Firmware SHA256: " << (*iterator)->getSHA256() << endl;
	}
}

void FirmwareManager::generateLogDir(){
	if(this->filePath.find("FW") == std::string::npos){
		this->filePath.append("FW/");
	}
	mkdir(this->filePath.c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

}

void FirmwareManager::generateLog(){
	remove(this->filePath.c_str());
	this->generateLogDir();

	list<Firmware*>::iterator iterator;
	string completePath = this->filePath.append(this->fileName);
	FILE* pFile = fopen(completePath.c_str(), "w");
	for(iterator=this->firmwares.begin(); iterator!=this->firmwares.end(); iterator++){
		fprintf(pFile, "%s\n", inFileName.c_str());
		fprintf(pFile, "%s: %s\n", "Firmware file", (*iterator)->getFileName().c_str());
		fprintf(pFile, "%s: %s\n", "Firmware directory", (*iterator)->getDirectory().c_str());
		fprintf(pFile, "%s: %s\n", "Firmware SHA256", (*iterator)->getSHA256().c_str());
	}
	fclose(pFile);
}

list<Firmware*> FirmwareManager:: retrieveFromFile(string path, int& err){
	list<Firmware*> retrievedFirmwares;
	StringManager* stringManager = new StringManager();
	std::ifstream infile(path.c_str());
	Firmware* retrieved;
	err = -1;

	string line;
	while(std::getline(infile,line)){
		if(line.compare(this->inFileName) == 0){
			retrieved = new Firmware();
			err = 0;
		}else if((stringManager->getSubString(line, ":", true)).compare("Firmware file") == 0){
			retrieved->setFileName(stringManager->getSubString(line, ":", false));
		}else if((stringManager->getSubString(line, ":", true)).compare("Firmware directory") == 0){
			retrieved->setDirectory(stringManager->getSubString(line, ":", false));
		}else if((stringManager->getSubString(line, ":", true)).compare("Firmware SHA256") == 0){
			retrieved->setSHA256(stringManager->getSubString(line, ":", false));
			retrievedFirmwares.push_back(retrieved);
		}
	}
	return retrievedFirmwares;
}

list<FWDifference*> FirmwareManager::checkFWFromFile(string path, int &err){
	list<FWDifference*> differences;
	FWDifference* log;
	list<Firmware*>::iterator myFWInterator;
	list<Firmware*>::iterator retrievedFWIterator;

	list<Firmware*> fromFileFirmware;
	int errorFromFile;

	err = 0;
	int size = 0;


	fromFileFirmware = this->retrieveFromFile(path, errorFromFile);

	size = max(fromFileFirmware.size(), this->firmwares.size());
	if(size == 0) {
		err = -1;
	}else if(errorFromFile == -1){
		err = -2;
	}else{
		myFWInterator = this->firmwares.begin();
		while(myFWInterator != this->firmwares.end()){
			bool found = false;
			retrievedFWIterator = fromFileFirmware.begin();
			while(found == false && retrievedFWIterator != fromFileFirmware.end() ){
				//If it's present with the same name in the same directory
				if((*myFWInterator)->getFileName().compare((*retrievedFWIterator)->getFileName()) == 0
						&& (*myFWInterator)->getDirectory().compare((*retrievedFWIterator)->getDirectory()) == 0 ){
					//if got the same sha256 set the difference as same and stop the iteration
					if((*myFWInterator)->getSHA256().compare((*retrievedFWIterator)->getSHA256()) == 0){
						log = new FWDifference();
						log->setCheck(FWDifference::same);
						log->setOrigin((*myFWInterator));
						differences.push_back(log);
						found = true;
					}else{
						log = new FWDifference();
						log->setCheck(FWDifference::different);
						log->setOrigin((*myFWInterator));
						log->setDifferent((*retrievedFWIterator));
						differences.push_back(log);
						found = true;
					}
				}
				retrievedFWIterator++;
			}
			if(found == false){
				log = new FWDifference();
				log->setCheck(FWDifference::added);
				log->setOrigin((*myFWInterator));
				differences.push_back(log);
			}
			myFWInterator++;
		}
		retrievedFWIterator = fromFileFirmware.begin();
		while(retrievedFWIterator != fromFileFirmware.end()){
			bool found = false;
			myFWInterator=this->firmwares.begin();
			while(found == false && myFWInterator != this->firmwares.end() ){
				if((*myFWInterator)->getFileName().compare((*retrievedFWIterator)->getFileName()) == 0
						&& (*myFWInterator)->getDirectory().compare((*retrievedFWIterator)->getDirectory()) == 0 ){
					found = true;
				}
				myFWInterator++;
			}
			//If cycled all and not found anything then something has been removed
			if(found == false){
				log = new FWDifference();
				log->setCheck(FWDifference::removed);
				log->setOrigin((*retrievedFWIterator));
				differences.push_back(log);
			}
			retrievedFWIterator++;
		}
	}

	return differences;
}

void FirmwareManager::printChecks(list<FWDifference*> differences){
	list<FWDifference*>::iterator myIterator;
	int diffCounters = 0;
	for(myIterator=differences.begin(); myIterator != differences.end(); myIterator++){
		if((*myIterator)->getCheck() == FWDifference::different){
			cout << "---FW CHECKS---" << endl;
			cout << "Firmware name: " << (*myIterator)->getOrigin()->getFileName() <<
					" In directory: " << (*myIterator)->getOrigin()->getDirectory() <<
					" Seems to be changed!"<< endl;
			cout << "His old SHA256 was: " << (*myIterator)->getDifferent()->getSHA256() << endl;
			cout << "His new SHA256 is: " <<  (*myIterator)->getOrigin()->getSHA256() << endl;
			diffCounters++;
		}else if((*myIterator)->getCheck() == FWDifference::added){
			cout << "---FW CHECKS---" << endl;
			cout << "Firmware name: " << (*myIterator)->getOrigin()->getFileName() << endl;
			cout << "Firmware directory: " << (*myIterator)->getOrigin()->getDirectory() << endl;
			cout << "Firmware SHA256: " << (*myIterator)->getOrigin()->getSHA256() << endl;
			cout << "Seems to be added!" << endl;
			diffCounters++;
		}else if((*myIterator)->getCheck() == FWDifference::removed){
			cout << "---FW CHECKS---" << endl;
			cout << "Firmware name: " << (*myIterator)->getOrigin()->getFileName() << endl;
			cout << "Firmware directory: " << (*myIterator)->getOrigin()->getDirectory() << endl;
			cout << "Firmware SHA256: " << (*myIterator)->getOrigin()->getSHA256() << endl;
			cout << "Seems to be removed!" << endl;
			diffCounters++;
		}
	}
	if(diffCounters == 0){
		cout << "No differences found! It seems to be all right!" << endl;
	}
}
void FirmwareManager::checkWithFile(string path){
	int err;
	list<FWDifference*> differences = this->checkFWFromFile(path, err);
	if(err == -1){
		cout << "No firmwares found" << endl;
	}else if(err == -2){
		cout << "No firmwares found in log file!" << endl;
	}else{
		this->printChecks(differences);
	}
}
void FirmwareManager::checkWithLogDirectory(){
	int err;
	string completePath = this->filePath.append(this->fileName);
	list<FWDifference*> differences = this->checkFWFromFile(completePath, err);
	if(err == -1){
		cout << "Errors occured" << endl;
	}else if(err == -2){
		cout << "No firmwares found in log file!" << endl;
	}else{
		this->printChecks(differences);
	}

}
