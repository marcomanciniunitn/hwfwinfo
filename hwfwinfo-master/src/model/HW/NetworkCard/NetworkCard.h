/*
 * NetworkCard.h
 *
 *  Created on: Apr 21, 2016
 *      Author: root
 */

#ifndef MODEL_NETWORKCARD_H_
#define MODEL_NETWORKCARD_H_

#include <string>
#include <sstream>
#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"

using namespace std;

/**
 * This class represents a generic Network Card
 * */
class NetworkCard : public HWDevice{
public:
	NetworkCard(){};

	~NetworkCard(){
		for(int i = 0; i < 5; i++){
			delete this->deviceInfos[i];
		}
		delete[] this->deviceInfos;
	}
	NetworkCard(int position)
	{
		this->deviceInfos = new BaseProperty*[5];
		BaseInfo<string>* serialInfo = new BaseInfo<string>();
		serialInfo->setProperty("Serial");
		this->deviceInfos[0] = serialInfo;

		BaseInfo<string>* productInfo = new BaseInfo<string>();
		productInfo->setProperty("Product");
		this->deviceInfos[1] = productInfo;

		BaseInfo<string>* vendorInfo = new BaseInfo<string>();
		vendorInfo->setProperty("Vendor");
		this->deviceInfos[2]= vendorInfo;

		BaseInfo<string>* descriptionInfo = new BaseInfo<string>();
		descriptionInfo->setProperty("Description");
		this->deviceInfos[3] = descriptionInfo;

		BaseInfo<int>* positionInfo = new BaseInfo<int>();
		positionInfo->setProperty("Position");
		positionInfo->setValue(position);
		this->deviceInfos[4] = positionInfo;
	}



};




#endif /* MODEL_NETWORKCARD_H_ */
