/*
 * BiosCreator.h
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#ifndef BIOSCREATOR_H_
#define BIOSCREATOR_H_

#include "../Basic/DeviceCreator.h"
#include "../Basic/BaseInfo.h"
#include "BIOS.h"
#include "../Basic/BaseProperty.h"

/**
 * Reppresent a BIOS creator.
 */
class BiosCreator : public DeviceCreator{
public:
	 HWDevice* createDefaultDevice(int position);
	 HWDevice* createFakeDevice();

};



#endif /* BIOSCREATOR_H_ */
