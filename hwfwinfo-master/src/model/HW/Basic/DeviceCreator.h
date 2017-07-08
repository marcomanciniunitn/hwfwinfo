/*
 * DeviceCreator.h
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#ifndef DEVICECREATOR_H_
#define DEVICECREATOR_H_

#include "HWDevice.h"

//Default fake values for a generic fake device.
#define DEFAULT_FAKE_STRING "FAKE"
#define DEFAULT_FAKE_INT -1000

/**
 * This is a Factory Interface used from the managers to generate devices
 */
class DeviceCreator{
public:
	virtual ~DeviceCreator(){};

	/**
	 * This method return a generic HWDevice, it will be implemented from the concrete
	 * device Factory classes.
	 */
	virtual HWDevice* createDefaultDevice(int position) = 0;

	/**
	 * This method return a fake device, iw till be implemented from the concrete
	 * device factory classes.
	 */
	virtual HWDevice* createFakeDevice() = 0;
};



#endif /* DEVICECREATOR_H_ */
