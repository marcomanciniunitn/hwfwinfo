/*
 * BiosCreator.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#include "BiosCreator.h"

HWDevice* BiosCreator::createDefaultDevice(int position){
	return new BIOS(position);
}

HWDevice* BiosCreator::createFakeDevice(){
	HWDevice* fakeDevice = new BIOS();

	fakeDevice->deviceInfos = new BaseProperty*[7];

	BaseInfo<string>* vendorInfo = new BaseInfo<string>();
	vendorInfo->setProperty("Vendor");
	vendorInfo->setValue(DEFAULT_FAKE_STRING);
	fakeDevice->deviceInfos[0] = vendorInfo;

	BaseInfo<string>* versionInfo = new BaseInfo<string>();
	versionInfo->setProperty("Version");
	versionInfo->setValue(DEFAULT_FAKE_STRING);
	fakeDevice->deviceInfos[1] = versionInfo;

	BaseInfo<string>* releaseDateInfo = new BaseInfo<string>();
	releaseDateInfo->setProperty("Release date");
	releaseDateInfo->setValue(DEFAULT_FAKE_STRING);
	fakeDevice->deviceInfos[2]= releaseDateInfo;

	BaseInfo<int>* ROMSizeInfo = new BaseInfo<int>();
	ROMSizeInfo->setProperty("ROM Size");
	ROMSizeInfo->setValue(DEFAULT_FAKE_INT);
	fakeDevice->deviceInfos[3] = ROMSizeInfo;

	BaseInfo<string>* revisionInfo = new BaseInfo<string>();
	revisionInfo->setProperty("Revision");
	revisionInfo->setValue(DEFAULT_FAKE_STRING);
	fakeDevice->deviceInfos[4] = revisionInfo;

	BaseInfo<string>* FWrevisionInfo = new BaseInfo<string>();
	FWrevisionInfo->setProperty("FW Revision");
	FWrevisionInfo->setValue(DEFAULT_FAKE_STRING);
	fakeDevice->deviceInfos[5] = FWrevisionInfo;

	return fakeDevice;
}


