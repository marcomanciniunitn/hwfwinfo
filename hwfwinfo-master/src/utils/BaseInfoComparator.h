/*
 * BaseInfoComparator.h
 *
 *  Created on: May 31, 2016
 *      Author: root
 */

#ifndef BASEINFOCOMPARATOR_H_
#define BASEINFOCOMPARATOR_H_

#include <string>
#include "../model/HW/Basic/BaseProperty.h"
#include "../model/HW/Basic/BaseDifference.h"
#include "../model/HW/Visitors/BaseInfoVisitor.h"
#include <typeinfo>


/**
 * This comparator compare two different BaseProperties and set a log difference
 * to the correct value. Contains two different implementations (int and string) for the comparisons
 */
class BaseInfoComparator{
private:

	/**
	 * Compare two BaseInfo<int> and set the log difference passed by param.
	 *
	 * @param orig the original property
	 * @param toCheck the second property to compare
	 * @param log the log to populate
	 * @return true if the properties are equal, false otherwise.
	 */
	bool visitToCompare(BaseInfo<int>* orig, BaseInfo<int>* toCheck,  BaseDifference* log){
		BaseInfoVisitor visitor;
		if(orig->getValue() == toCheck->getValue()){
			return true;
		}else{
			log->setCheck(true);
			log->visitToAssign(visitor, to_string(toCheck->getValue()));
			return false;
		}

	}

	/**
	 * Compare two BaseInfo<string> and set the log difference passed by param.
	 *
	 * @param orig the original property
	 * @param toCheck the second property to compare
	 * @param log the log to populate
	 * @return true if the properties are equal, false otherwise.
	 */
	bool visitToCompare(BaseInfo<string>* orig, BaseInfo<string>* toCheck,  BaseDifference* log){
		BaseInfoVisitor visitor;
		if(orig->getValue().compare(toCheck->getValue()) == 0){
			return true;
		}else{
			log->setCheck(true);
			log->visitToAssign(visitor, toCheck->getValue());
			return false;
		}
	}
public:
	/**
	 * Compare two BaseProperties and set the log difference passed by param.
	 *
	 * @param orig the original property
	 * @param toCheck the second property to compare
	 * @param log the log to populate
	 * @return true if the properties are equal, false otherwise.
	 */
	bool compare(BaseProperty* orig, BaseProperty* toCheck, BaseDifference* log){
		BaseInfo<string>* stringInfo = new BaseInfo<string>();
		BaseInfo<int>* intInfo = new BaseInfo<int>();

		//Run-time check to check if the BaseProperty is a BaseInfo<int> or a BaseInfo<string> and call the right visitToCompare method with right
		// parameters.
		if(typeid(*orig).name()  == typeid(*stringInfo).name()
				&& typeid(*toCheck).name() == typeid(*stringInfo).name() ){
			//INT CASE
			BaseInfo<string>* val1 = (BaseInfo<string>*) orig;
			BaseInfo<string>* val2 = (BaseInfo<string>*) toCheck;

			return visitToCompare(val1, val2,log);

		}else if(typeid(*orig).name() == typeid(*intInfo).name()
				&& typeid(*toCheck).name() == typeid(*intInfo).name() ){
			//STRING CASE
			BaseInfo<int>* val1 = (BaseInfo<int>*) orig;
			BaseInfo<int>* val2 = (BaseInfo<int>*) toCheck;
			return visitToCompare(val1, val2,log);
		}else {
			return false;
		}
	}

};



#endif /* BASEINFOCOMPARATOR_H_ */
