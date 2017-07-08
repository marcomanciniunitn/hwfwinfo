/*
 * GraphicCardCreator.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#include "GraphicCardCreator.h"

HWDevice* GraphicCardCreator::createDefaultDevice(int position){
	return new GraphicCard(position);
}

HWDevice* GraphicCardCreator::createFakeDevice(){
	HWDevice* fakeCard = new GraphicCard();

	fakeCard->deviceInfos = new BaseProperty*[4];

	BaseInfo<string>* productInfo = new BaseInfo<string>();
	productInfo->setProperty("Product");
	productInfo->setValue(DEFAULT_FAKE_STRING);
	fakeCard->deviceInfos[0] = productInfo;

	BaseInfo<string>* vendorInfo = new BaseInfo<string>();
	vendorInfo->setProperty("Vendor");
	vendorInfo->setValue(DEFAULT_FAKE_STRING);
	fakeCard->deviceInfos[1] = vendorInfo;

	BaseInfo<int>* physicalIDInfo = new BaseInfo<int>();
	physicalIDInfo->setProperty("Physical ID");
	physicalIDInfo->setValue(DEFAULT_FAKE_INT);
	fakeCard->deviceInfos[2]= physicalIDInfo;

	BaseInfo<int>* clockInfo = new BaseInfo<int>();
	clockInfo->setProperty("Clock");
	clockInfo->setValue(DEFAULT_FAKE_INT);
	fakeCard->deviceInfos[3] = clockInfo;

	return fakeCard;
}

