/*
 * mapTrigger.h
 *
 *  Created on: Sep 30, 2015
 *      Author: Alon Yaari
 */

#include <iostream>
#include "MOOS/libMOOS/MOOSLib.h"

#ifndef MAPTRIGGER_H_
#define MAPTRIGGER_H_

#ifndef BAD_DOUBLE
#define BAD_DOUBLE -99999.99
#endif

class mapTrigger {
public:
    mapTrigger();
	mapTrigger(MOOS::MOOSAsyncCommClient* pComms, std::string sDef);
	~mapTrigger() {}


	bool StoreValueThenPublish(std::string sVal);
	bool StoreValueThenPublish(double dVal);
	unsigned int CountPublished() { return m_countNotified; }
	std::string GetAppCastMsg();
	bool IsValid() { return m_errorStr.empty(); }
	std::string GetError() { return m_errorStr; }
	std::string GetKey() { return m_inName; }
	std::string GetOut() { return m_outName; }
	std::string GetLastValue() { return m_lastVal; }
	std::string GetAppCastStatusString();

private:
	void        PrepAppCastMsg();
    bool        SetRequiredDef(const std::string key, std::string& storeHere);
    bool        findDef(const std::string key, std::string& storeHere);

	std::string m_lastVal;
	std::string m_inName;
	std::string m_triggerValue;
	std::string m_outName;
	std::string m_outString;
	double      m_outDouble;
	bool        m_bOutIsDouble;
	unsigned int m_countNotified;
	std::string m_appCastPrep;
	std::string m_errorStr;
	std::map<std::string, std::string> m_defMap;


	MOOS::MOOSAsyncCommClient* m_pComms;

};







#endif















//
