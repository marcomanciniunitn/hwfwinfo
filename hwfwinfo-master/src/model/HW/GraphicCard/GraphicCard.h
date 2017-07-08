/*
 * GraphicCard.h
 *
 *  Created on: Apr 20, 2016
 *      Author: root
 */

#ifndef MODEL_GRAPHICCARD_H_
#define MODEL_GRAPHICCARD_H_

#include <string>
#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"

using namespace std;
/**
 * Represents a GraphicCard
 */
class GraphicCard : public HWDevice{
public:
	GraphicCard(){};
	~GraphicCard(){
		for(int i = 0; i < 5; i++){
			delete this->deviceInfos[i];
		}
		delete[] this->deviceInfos;
	}
	GraphicCard(int position){
		this->deviceInfos = new BaseProperty*[5];
		BaseInfo<string>* productInfo = new BaseInfo<string>();
		productInfo->setProperty("Product");
		this->deviceInfos[0] = productInfo;

		BaseInfo<string>* vendorInfo = new BaseInfo<string>();
		vendorInfo->setProperty("Vendor");
		this->deviceInfos[1] = vendorInfo;

		BaseInfo<int>* physicalIDInfo = new BaseInfo<int>();
		physicalIDInfo->setProperty("Physical ID");
		this->deviceInfos[2]= physicalIDInfo;

		BaseInfo<int>* clockInfo = new BaseInfo<int>();
		clockInfo->setProperty("Clock");
		this->deviceInfos[3] = clockInfo;

		BaseInfo<int>* positionInfo = new BaseInfo<int>();
		positionInfo->setProperty("Position");
		positionInfo->setValue(position);
		this->deviceInfos[4] = positionInfo;
	}


};




#endif /* MODEL_GRAPHICCARD_H_ */
