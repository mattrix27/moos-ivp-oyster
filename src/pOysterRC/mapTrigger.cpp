/*
 * mapTrigger.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: Alon Yaari
 */

#include "MBUtils.h"
#include "mapTrigger.h"

using namespace std;

mapTrigger::mapTrigger()
{
    m_errorStr = "No definition for this mapping.";
	m_countNotified = 0;
	m_lastVal = "";
    m_inName = "";
    m_triggerValue = "";
    m_outName = "";
    m_outString = "";
    m_outDouble = BAD_DOUBLE;
    m_bOutIsDouble = true;
    m_pComms = 0;
}

mapTrigger::mapTrigger(MOOS::MOOSAsyncCommClient* pComms, string sDef)
{
    m_errorStr = "";
    m_pComms = pComms;
    string sVal = "";

    vector<string> keyValues = parseStringQ(sDef, ',');
    vector<string>::iterator it = keyValues.begin();
    for (; it != keyValues.end(); ++it) {
        string keyVal = *it;
        string key = toupper(MOOSChomp(keyVal, "=", true));
        m_defMap[key] = keyVal; }

    bool bGood = true;
    bGood &= SetRequiredDef("IN_MSG",  m_inName);
    bGood &= SetRequiredDef("TRIGGER",  m_triggerValue);
    bGood &= SetRequiredDef("OUT_MSG", m_outName);
    bGood &= SetRequiredDef("OUT_VAL", m_outString);
    if (!bGood) {
        m_errorStr = "Bad trigger definition: " + sDef;
        return; }
    m_outDouble = strtod(m_outString.c_str(), 0);    // Always convert, even if string val will simply be 0.0

    // Is the outVal a string or a double?
    //      - If it has any quote characters, it's a string
    //      - If it registers as a pure number, it's a double
    if (m_outString.find('\"') != string::npos)
        m_bOutIsDouble = false;
    else
        m_bOutIsDouble = isNumber(m_outString, true);

    PrepAppCastMsg();
    m_pComms->Register(m_inName, 0.0);
    PrepAppCastMsg();
}

bool mapTrigger::SetRequiredDef(const string key, string& storeHere)
{
    bool bGood = findDef(key, storeHere);
    if (!bGood) {
        m_errorStr += "Missing definition for required element ";
        m_errorStr.append(key);
        m_errorStr.append(".");
        return false; }
    return true;
}

bool mapTrigger::findDef(const string key, string& storeHere)
{
    unsigned long int found = m_defMap.count(key);
    if (found)
        storeHere = m_defMap[key];
    return found;
}

bool mapTrigger::StoreValueThenPublish(double dVal)
{
	return StoreValueThenPublish(doubleToString(dVal, 6));
}

bool mapTrigger::StoreValueThenPublish(std::string sVal)
{
	// Ignore when new input is the same as last time;
	if (sVal == m_lastVal) return true;
	m_lastVal = sVal;

	// Ignore when new input is not the trigger value
	if (sVal != m_triggerValue) {
		return true; }

	// Reaching here means input value changed into the trigger
	m_countNotified++;

	if (m_bOutIsDouble)
		return m_pComms->Notify(m_outName, m_outDouble);
	return m_pComms->Notify(m_outName, m_outString);
}

void mapTrigger::PrepAppCastMsg()
{
	stringstream ss;
	ss << "      In:         " << m_inName << endl;
	ss << "       Trigger on: " << m_triggerValue << endl;
	ss << "       Out:        " << m_outName << endl;
	ss << "       Value:      " << m_outString;
    if (m_bOutIsDouble)
    	ss << " (as double).";
    else
    	ss << " (as string).";
    ss << endl;
	m_appCastPrep = ss.str();
}


string mapTrigger::GetAppCastMsg()
{
    return m_appCastPrep;
}

string mapTrigger::GetAppCastStatusString()
{
    stringstream ss;
    ss << "   " << m_inName << endl;
    ss << "      Last in value: " << m_lastVal << endl;
    ss << "   Published: " << m_countNotified << "" << endl;
    return ss.str();
}














//
