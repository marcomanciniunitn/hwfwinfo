/*
 * MemoryDeviceManager.h
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#ifndef MODEL_MEMORYDEVICEMANAGER_H_
#define MODEL_MEMORYDEVICEMANAGER_H_

#include <string>
#include <fstream>
#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../HW/Basic/DeviceManager.h"
#include "../../HW/Basic/BaseLogDifference.h"
#include "../../HW/Basic/BaseDifference.h"
#include "MemoryCreator.h"
#include "MemoryDevice.h"


#define SERIAL_POSITION 0
#define SIZE_POSITION 4
#define TYPE_POSITION 3
#define SPEED_POSITION 2
#define MANUFACTURER_POSITION 1


using namespace std;

/**
 * Reppresents a Memory device manager, it's used to manage all memory devices .
 **/
class MemoryDeviceManager : public DeviceManager{
public:
	MemoryDeviceManager();
	~MemoryDeviceManager(){};

	void setCommands(int devicePosition);

	BaseDifference** generateLogDifference();


};





#endif /* MODEL_MEMORYDEVICEMANAGER_H_ */
