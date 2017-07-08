/*
 * NetworkCardCreator.h
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#ifndef NETWORKCARDCREATOR_H_
#define NETWORKCARDCREATOR_H_

#include "../Basic/DeviceCreator.h"
#include "../Basic/BaseInfo.h"
#include "NetworkCard.h"
#include "../Basic/BaseProperty.h"

/**
 * This class represents a network card creator.
 */
class NetworkCardCreator : public DeviceCreator{
public:
	 HWDevice* createDefaultDevice(int position);
	 HWDevice* createFakeDevice();

};






#endif /* NETWORKCARDCREATOR_H_ */
