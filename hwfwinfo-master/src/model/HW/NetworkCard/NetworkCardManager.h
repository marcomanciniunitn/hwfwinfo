/*
 * NetworkCardManager.h
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#ifndef MODEL_NETWORKCARDMANAGER_H_
#define MODEL_NETWORKCARDMANAGER_H_

#include <string>
#include <fstream>
#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../HW/Basic/DeviceManager.h"
#include "../../HW/Basic/BaseLogDifference.h"
#include "../../HW/Basic/BaseDifference.h"
#include "NetworkCardCreator.h"
#include "NetworkCard.h"

#define SERIAL_POSITION 0
#define PRODUCT_POSITION 1
#define VENDOR_POSITION 2
#define DESCRIPTION_POSITION 3



using namespace std;

/**
 * Reppresents a Network card manager, it's used to manage all network cards on the system.
 **/
class NetworkCardManager : public DeviceManager{
public:
	NetworkCardManager();
	~NetworkCardManager(){};

	void setCommands(int devicePosition);

	/**
	 * This method has been overwritten because using the lshw command caused problems with properties.
	 */
	void setAllInfos(int position);

	BaseDifference** generateLogDifference();

};




#endif /* MODEL_NETWORKCARDMANAGER_H_ */
