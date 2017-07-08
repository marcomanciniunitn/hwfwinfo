/*
 * HardDiskManager.h
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#ifndef MODEL_HARDDISKMANAGER_H_
#define MODEL_HARDDISKMANAGER_H_

#include <string>
#include <fstream>

#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../HW/Basic/DeviceManager.h"
#include "../../HW/Basic/BaseLogDifference.h"
#include "../../HW/Basic/BaseDifference.h"
#include "HDDCreator.h"
#include "HardDisk.h"

using namespace std;


/*Reppresents an HardDisk manager, it's used to manage all hard disks on the system.*/

class HardDiskManager : public DeviceManager{
public:
	HardDiskManager();
	~HardDiskManager(){};

	HWDevice* generateNewDevice(int position);

	void setCommands(int devicePosition);


	BaseDifference** generateLogDifference();


};






#endif /* MODEL_HARDDISKMANAGER_H_ */
