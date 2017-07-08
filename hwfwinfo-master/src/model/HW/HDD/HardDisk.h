/*
 * HardDisk.h
 *
 *  Created on: Apr 20, 2016
 *      Author: root
 */

#ifndef MODEL_HARDDISK_H_
#define MODEL_HARDDISK_H_
#include <string>

#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../HW/Basic/Command.h"
#include "../../HW/Basic/BaseInfo.h"


/*This class reppresents a generic HardDisk*/
class HardDisk : public HWDevice{
public:
	HardDisk(){};

	~HardDisk(){
		for(int i = 0; i < 4; i++){
			delete this->deviceInfos[i];
		}
		delete[] this->deviceInfos;
	}

	HardDisk(int position){
		this->deviceInfos = new BaseProperty*[4];

		BaseInfo<string>* serialInfo = new BaseInfo<string>();
		serialInfo->setProperty("Serial Number");
		this->deviceInfos[0] = serialInfo;

		BaseInfo<string>* modelInfo = new BaseInfo<string>();
		modelInfo->setProperty("Model Number");
		this->deviceInfos[1] = modelInfo;

		BaseInfo<string>* firmwareInfo = new BaseInfo<string>();
		firmwareInfo->setProperty("Firmware Revision");
		this->deviceInfos[2]= firmwareInfo;

		BaseInfo<int>* positionInfo = new BaseInfo<int>();
		positionInfo->setProperty("Position");
		positionInfo->setValue(position);
		this->deviceInfos[3] = positionInfo;
	}



};




#endif /* MODEL_HARDDISK_H_ */
