/*
 * MemoryCreator.h
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#ifndef MEMORYCREATOR_H_
#define MEMORYCREATOR_H_


#include "../Basic/DeviceCreator.h"
#include "../Basic/BaseInfo.h"
#include "MemoryDevice.h"
#include "../Basic/BaseProperty.h"

/**
 * This class represents a MemoryDevice creator.
 */
class MemoryCreator : public DeviceCreator{
public:
	 HWDevice* createDefaultDevice(int position);
	 HWDevice* createFakeDevice();

};



#endif /* MEMORYCREATOR_H_ */
