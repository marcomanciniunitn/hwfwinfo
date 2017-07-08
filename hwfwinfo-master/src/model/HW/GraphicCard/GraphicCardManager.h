/*
 * GraphicCardManager.h
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#ifndef MODEL_GRAPHICCARDMANAGER_H_
#define MODEL_GRAPHICCARDMANAGER_H_

#include <string>
#include <fstream>

#include "../../HW/Basic/HWDevice.h"
#include "../../../utils/CommandManager.h"
#include "../../../utils/StringManager.h"
#include "../../HW/Basic/DeviceManager.h"
#include "../../HW/Basic/BaseLogDifference.h"
#include "../../HW/Basic/BaseDifference.h"
#include "GraphicCardCreator.h"
#include "GraphicCard.h"

using namespace std;

/*Reppresents a graphiccard manager, it's used to manage all graphic cards on the system.*/
class GraphicCardManager : public DeviceManager{
public:
	GraphicCardManager();
	~GraphicCardManager(){};

	void setCommands(int devicePosition);

	BaseDifference** generateLogDifference();

};

#endif /* MODEL_GRAPHICCARDMANAGER_H_ */
