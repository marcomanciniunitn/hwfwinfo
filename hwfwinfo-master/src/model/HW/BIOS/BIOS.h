/*
 * BIOS.h
 *
 *  Created on: Apr 12, 2016
 *      Author: root
 */

#ifndef MODEL_BIOS_H_
#define MODEL_BIOS_H_

#include <string>

#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../HW/Basic/Command.h"
#include "../../HW/Basic/BaseInfo.h"

using namespace std;

/**
 *  Rappresents a BIOS
 *
 **/
class BIOS : public HWDevice{

public:
	BIOS(){};

	~BIOS(){
		for(int i = 0; i < 7; i++){
			delete this->deviceInfos[i];
		}
		delete[] this->deviceInfos;
	}
	//DEFAULT CONSTRUCTOR
	BIOS(int position){
		this->deviceInfos = new BaseProperty*[7];

		BaseInfo<string>* vendorInfo = new BaseInfo<string>();
		vendorInfo->setProperty("Vendor");
		this->deviceInfos[0] = vendorInfo;

		BaseInfo<string>* versionInfo = new BaseInfo<string>();
		versionInfo->setProperty("Version");
		this->deviceInfos[1] = versionInfo;

		BaseInfo<string>* releaseDateInfo = new BaseInfo<string>();
		releaseDateInfo->setProperty("Release date");
		this->deviceInfos[2]= releaseDateInfo;

		BaseInfo<int>* ROMSizeInfo = new BaseInfo<int>();
		ROMSizeInfo->setProperty("ROM Size");
		this->deviceInfos[3] = ROMSizeInfo;

		BaseInfo<string>* revisionInfo = new BaseInfo<string>();
		revisionInfo->setProperty("Revision");
		this->deviceInfos[4] = revisionInfo;

		BaseInfo<string>* FWrevisionInfo = new BaseInfo<string>();
		FWrevisionInfo->setProperty("FW Revision");
		this->deviceInfos[5] = FWrevisionInfo;

		BaseInfo<int>* positionInfo = new BaseInfo<int>();
		positionInfo->setProperty("Position");
		positionInfo->setValue(position);
		this->deviceInfos[6] = positionInfo;
	}
};




#endif /* MODEL_BIOS_H_ */
