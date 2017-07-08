/*
 * BIOSManager.h
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#ifndef MODEL_HW_BIOS_BIOSMANAGER_H_
#define MODEL_HW_BIOS_BIOSMANAGER_H_

#include <string>
#include <fstream>

#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../HW/Basic/DeviceManager.h"
#include "../../HW/Basic/BaseLogDifference.h"
#include "../../HW/Basic/BaseDifference.h"
#include "BiosCreator.h"
#include "BIOS.h"

using namespace std;

/**
 *  This class represents a generic BIOSManager. It's used to manage all BIOSes presents on the system.
 **/
class BIOSManager : public DeviceManager{
public:
    BIOSManager();
	~BIOSManager(){};

	void setCommands(int devicePosition);

	BaseDifference** generateLogDifference();


};


#endif


