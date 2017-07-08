/*
 * MemoryCreator.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#include "MemoryCreator.h"

HWDevice* MemoryCreator::createDefaultDevice(int position){
	return new MemoryDevice(position);
}

HWDevice* MemoryCreator::createFakeDevice(){
	HWDevice* fakeMemory = new MemoryDevice();

	fakeMemory->deviceInfos = new BaseProperty*[5];

	BaseInfo<string>* serialInfo = new BaseInfo<string>();
	serialInfo->setProperty("Serial Number");
	serialInfo->setValue(DEFAULT_FAKE_STRING);
	fakeMemory->deviceInfos[0] = serialInfo;

	BaseInfo<string>* manufacturerInfo = new BaseInfo<string>();
	manufacturerInfo->setProperty("Manufacturer");
	manufacturerInfo->setValue(DEFAULT_FAKE_STRING);
	fakeMemory->deviceInfos[1] = manufacturerInfo;

	BaseInfo<int>* speedInfo = new BaseInfo<int>();
	speedInfo->setProperty("Speed");
	speedInfo->setValue(DEFAULT_FAKE_INT);
	fakeMemory->deviceInfos[2]= speedInfo;

	BaseInfo<string>* typeInfo = new BaseInfo<string>();
	typeInfo->setProperty("Type");
	typeInfo->setValue(DEFAULT_FAKE_STRING);
	fakeMemory->deviceInfos[3] = typeInfo;

	BaseInfo<int>* sizeInfo = new BaseInfo<int>();
	sizeInfo->setProperty("Size");
	sizeInfo->setValue(DEFAULT_FAKE_INT);
	fakeMemory->deviceInfos[4] = sizeInfo;

	return fakeMemory;
}

