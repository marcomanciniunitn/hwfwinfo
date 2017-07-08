/*
 * HWManager.h
 *
 *  Created on: Apr 22, 2016
 *      Author: root
 */

#ifndef MODEL_HW_MANAGER_HWMANAGER_H_
#define MODEL_HW_MANAGER_HWMANAGER_H_

#include <string>
#include <time.h>

#include "../../HW/Basic/HWDevice.h"

#include "../../HW/Basic/DeviceManager.h"
#include "../../HW/NetworkCard/NetworkCardManager.h"
#include "../../HW/Memory/MemoryDeviceManager.h"
#include "../../HW/BIOS/BIOS.h"
#include "../../HW/GraphicCard/GraphicCardManager.h"
#include "../../HW/HDD/HardDiskManager.h"
#include "../../HW/BIOS/BIOSManager.h"

#include "../../HW/Basic/BaseDifference.h"
#include "../../HW/Visitors/BaseInfoVisitor.h"

#define BIOS_MANAGER_POSITION 0
#define GCARD_MANAGER_POSITION 1
#define MEMORY_MANAGER_POSITION 2
#define NET_MANAGER_POSITION 3
#define HDD_MANAGER_POSITION 4

#define MANAGERS_COUNT 5


#include <sys/stat.h>
#include <fstream>

using namespace std;
/**
 * Enum used to select and manage the right managers.
 */
enum checkChoise { bios, gcard, memory , ncard, hdd };

/**
 * This class represents the HardwareManager, it contains all @DeviceManager used to manage all @HWDevice on the
 * system and offers different public method to manage all the managers.
 */
class HWManager{
private:
	//Number of devices retrieved on the system
	int numberOfDevices;

	//Number of managers
	int numberOfManagers;

	//Array of managers used to manage all devices
	DeviceManager** deviceManagers;

	//Path used to log.
	string logPath;


	/**
	 * This method generate a log directory under the path passed by param
	 *
	 * @param path the path dir
	 */
	string generateLogDir(string path);

	/**
	 * This method return the number of devices retrieved on the system
	 */
	int getNumberOfDevices();

	/**
	 * This method populate a specific class of devices
	 *
	 * @param choise the class to populate
	 */
	void populateDevices(checkChoise choise);




public:
	HWManager();
	~HWManager();

	void setLogPath(string path);

	/**
	 * This method return the log path.
	 */
	string getLogPath();

	/**
	 * This method instantiate the choosed manager
	 *
	 * @param choise the user's choice
	 */
	void populateManager(checkChoise choise);

	/**
	 * This method populate all managers
	 */
	void populateAllManagers();


	/**
	 * This method populate all manager's devices
	 */
	void populateAllDevices();


	/**
	 * This method generate all logs under the path passed by param.
	 *
	 * @param path the path used to generate the log
	 */
	void generateAllLogs(string path);


	/**
	 * This method show all devices logged in a file
	 *
	 * @param path path of log file
	 */
	void retrieveDevicesFromFile(string path);

	/**
	 * This method print all infos about devices retrieved
	 */
	void printAllInfos();

	/**
	 * This method check current devices with devices stored in the log dir setted
	 *
	 * @param scanId number of scan to use to check
	 */
	void checkWithDirectory(int scanId);


	/**
	 * This method check current devices with devices stored in a log file passed by param
	 *
	 * @param path the log file path
	 * @param choise the devicemanager choise
	 * @param scanId the revision log number
	 *
	 */
	void checkWithFile(string path, checkChoise choise, int scanId);


};

#endif /* MODEL_HW_MANAGER_HWMANAGER_H_ */
