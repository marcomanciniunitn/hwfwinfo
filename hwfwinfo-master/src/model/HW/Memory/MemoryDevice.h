/*
 * MemoryDevice.h
 *
 *  Created on: Apr 19, 2016
 *      Author: root
 */

#ifndef MODEL_MEMORYDEVICE_H_
#define MODEL_MEMORYDEVICE_H_


#include <string>
#include <stdlib.h>
#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"

using namespace std;

/**
 * This class represents a generic MemoryDevice
 **/
class MemoryDevice : public HWDevice{
public:
	MemoryDevice(){};

	~MemoryDevice(){
		for(int i = 0; i < 6; i++){
			delete this->deviceInfos[i];
		}
		delete[] this->deviceInfos;
	}

	MemoryDevice(int position){
		this->deviceInfos = new BaseProperty*[6];

		BaseInfo<string>* serialInfo = new BaseInfo<string>();
		serialInfo->setProperty("Serial Number");
		this->deviceInfos[0] = serialInfo;

		BaseInfo<string>* manufacturerInfo = new BaseInfo<string>();
		manufacturerInfo->setProperty("Manufacturer");
		this->deviceInfos[1] = manufacturerInfo;

		BaseInfo<int>* speedInfo = new BaseInfo<int>();
		speedInfo->setProperty("Speed");
		this->deviceInfos[2]= speedInfo;

		BaseInfo<string>* typeInfo = new BaseInfo<string>();
		typeInfo->setProperty("Type");
		this->deviceInfos[3] = typeInfo;

		BaseInfo<int>* sizeInfo = new BaseInfo<int>();
		sizeInfo->setProperty("Size");
		this->deviceInfos[4] = sizeInfo;

		BaseInfo<int>* positionInfo = new BaseInfo<int>();
		positionInfo->setProperty("Position");
		positionInfo->setValue(position);
		this->deviceInfos[5] = positionInfo;
	}
};




#endif /* MODEL_MEMORYDEVICE_H_ */
