/*
 * NetworkCardCreator.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#include "NetworkCardCreator.h"

HWDevice* NetworkCardCreator::createDefaultDevice(int position){
	return new NetworkCard(position);
}

HWDevice* NetworkCardCreator::createFakeDevice(){
	HWDevice* fakeNetworkCard = new NetworkCard();

	fakeNetworkCard->deviceInfos = new BaseProperty*[4];

	BaseInfo<string>* serialInfo = new BaseInfo<string>();
	serialInfo->setProperty("Serial");
	serialInfo->setValue(DEFAULT_FAKE_STRING);
	fakeNetworkCard->deviceInfos[0] = serialInfo;

	BaseInfo<string>* productInfo = new BaseInfo<string>();
	productInfo->setProperty("Product");
	productInfo->setValue(DEFAULT_FAKE_STRING);
	fakeNetworkCard->deviceInfos[1] = productInfo;

	BaseInfo<string>* vendorInfo = new BaseInfo<string>();
	vendorInfo->setProperty("Vendor");
	vendorInfo->setValue(DEFAULT_FAKE_STRING);
	fakeNetworkCard->deviceInfos[2]= vendorInfo;

	BaseInfo<string>* descriptionInfo = new BaseInfo<string>();
	descriptionInfo->setProperty("Description");
	descriptionInfo->setValue(DEFAULT_FAKE_STRING);
	fakeNetworkCard->deviceInfos[3] = descriptionInfo;

	return fakeNetworkCard;
}

