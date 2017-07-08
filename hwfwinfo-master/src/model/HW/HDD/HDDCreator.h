/*
 * HDDCreator.h
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#ifndef HDDCREATOR_H_
#define HDDCREATOR_H_


#include "../Basic/DeviceCreator.h"
#include "../Basic/BaseInfo.h"
#include "HardDisk.h"
#include "../Basic/BaseProperty.h"

class HDDCreator : public DeviceCreator{
public:
	 HWDevice* createDefaultDevice(int position);
	 HWDevice* createFakeDevice();

};




#endif /* HDDCREATOR_H_ */
