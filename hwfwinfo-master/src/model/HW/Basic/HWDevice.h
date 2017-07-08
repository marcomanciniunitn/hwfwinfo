/*
 * HWDevice.h
 *
 *  Created on: Apr 14, 2016
 *      Author: Marco Mancini
 */

#ifndef MODEL_HWDEVICE_H_
#define MODEL_HWDEVICE_H_

#include <string>
#include "Command.h"
#include "BaseInfo.h"


using namespace std;

/**
 * This class represents an Hardware Device
 * */
class HWDevice{
public:
	//Array of devices informations, each specific @HWDevice will set his default informations
	BaseProperty** deviceInfos;

	/**
	 * Return a specific property
	 *
	 * @param propertyPosition the property position
	 * @return a specific property
	 */
	BaseProperty* getProperty(int propertyPosition){ return this->deviceInfos[propertyPosition]; }


};





#endif /* MODEL_HWDEVICE_H_ */
