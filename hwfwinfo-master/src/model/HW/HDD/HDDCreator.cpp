/*
 * HDDCreator.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#include "HDDCreator.h"

HWDevice* HDDCreator::createDefaultDevice(int position){
	return new HardDisk(position);
}

HWDevice* HDDCreator::createFakeDevice(){
	HWDevice* fakeHDD = new HardDisk();

	fakeHDD->deviceInfos = new BaseProperty*[3];

	BaseInfo<string>* serialInfo = new BaseInfo<string>();
	serialInfo->setProperty("Serial Number");
	serialInfo->setValue(DEFAULT_FAKE_STRING);
	fakeHDD->deviceInfos[0] = serialInfo;

	BaseInfo<string>* modelInfo = new BaseInfo<string>();
	modelInfo->setProperty("Model Number");
	modelInfo->setValue(DEFAULT_FAKE_STRING);
	fakeHDD->deviceInfos[1] = modelInfo;

	BaseInfo<string>* firmwareInfo = new BaseInfo<string>();
	firmwareInfo->setProperty("Firmware Revision ID");
	firmwareInfo->setValue(DEFAULT_FAKE_STRING);
	fakeHDD->deviceInfos[2]= firmwareInfo;

	return fakeHDD;
}



