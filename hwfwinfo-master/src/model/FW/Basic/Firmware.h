/*
 * Firmware.h
 *
 *  Created on: Jun 1, 2016
 *      Author: root
 */

#ifndef FIRMWARE_H_
#define FIRMWARE_H_

#include <string>

using namespace std;

/**
 * This class represents a generic firmware
 */
class Firmware{
private:
	// The firmware name
	string file_name;

	// The firmware sha256 checksum
	string sha256;

	// The firmware directory
	string directory;

public:
	Firmware(){};
	~Firmware(){};

	/**
	 * Setters
	 */
	void setFileName(string file_name){ this->file_name = file_name; }
	void setSHA256(string sha256){ this->sha256 = sha256; }
	void setDirectory(string directory){ this->directory = directory; }

	/**
	 * Getters
	 */
	string getFileName(){ return this->file_name; }
	string getSHA256(){ return this->sha256; }
	string getDirectory(){ return this->directory; }
};



#endif /* FIRMWARE_H_ */
