/*
 * GraphicCardCreator.h
 *
 *  Created on: Jun 12, 2016
 *      Author: root
 */

#ifndef GRAPHICCARDCREATOR_H_
#define GRAPHICCARDCREATOR_H_

#include "../Basic/DeviceCreator.h"
#include "../Basic/BaseInfo.h"
#include "GraphicCard.h"
#include "../Basic/BaseProperty.h"

/**
 * Represents a gcard creator used by the deviceManager.
 */
class GraphicCardCreator : public DeviceCreator{
public:
	 HWDevice* createDefaultDevice(int position);
	 HWDevice* createFakeDevice();

};




#endif /* GRAPHICCARDCREATOR_H_ */
