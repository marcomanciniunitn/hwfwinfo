/*
 * FWDifference.h
 *
 *  Created on: Jun 3, 2016
 *      Author: root
 */

#ifndef FWDIFFERENCE_H_
#define FWDIFFERENCE_H_

#include <string>
#include "Firmware.h"


/**
 * This class represents a generic Firmware difference
 */
class FWDifference{
public:
	/*
	 * The state of a difference could be:
	 * same = not changed-> firmware infos contained on orig field
	 * different = changed -> orig field contains original FW and diff field contains the different firmware found
	 * added = firmware added -> firmware infos contained on orig field
	 * removed = firmware removed -> firmware infos contained on orig field
	 */
	enum stateDifference { same, different, added, removed };

	FWDifference(){
		this->check = same;
		this->orig = new Firmware();
		this->diff = new Firmware();

	}
	~FWDifference(){
		delete this->orig;
		delete this->diff;
	}

	/**
	 * Setters
	 */
	void setCheck(stateDifference check){ this->check = check; }
	void setDifferent(Firmware* different){ this->diff = different; }
	void setOrigin(Firmware* origin){ this->orig = origin; }

	/**
	 * Getters
	 */
	stateDifference getCheck(){ return this->check; }
	Firmware* getDifferent(){ return this->diff; }
	Firmware* getOrigin(){ return this->orig; }

private:
	//Difference state
	stateDifference check;

	//Firmware checked
	Firmware* orig;

	//Firmware changed
	Firmware* diff;

};




#endif /* FWDIFFERENCE_H_ */
