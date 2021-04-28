/*
 * mapRange.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: Alon Yaari
 */

#include "math.h"       // fabs(), sqrt()
#include "MBUtils.h"
#include "mapRange.h"

using namespace std;

// Input range [inMin, inMax]
// Output range [outMin, outMax]
// Input value dIn
// Output mapped value dOut
//
//                  (dIn - inMin) x (maxOut - minOut)
// dOut = outMin +  ---------------------------------
//                         (maxIn - minIn)
//


mapRange::mapRange()
{
    // Setup params
    m_inDef             = "";
    m_inName            = "";
    m_inMin             = BAD_DOUBLE;
    m_inMax             = BAD_DOUBLE;
    m_inConstrainMin    = BAD_DOUBLE;
    m_inConstrainMax    = BAD_DOUBLE;
    m_normMin           = -1.0;
    m_normMax           = 1.0;
    m_outName           = "";
    m_outMin            = BAD_DOUBLE;
    m_outMax            = BAD_DOUBLE;
    m_dead              = 0.0;
    m_sat               = 0.0;

    // Current values
    m_curInValue        = BAD_DOUBLE;
    m_curNorm           = BAD_DOUBLE;
    m_curDepValue       = BAD_DOUBLE;
    m_curDepNorm        = BAD_DOUBLE;
    m_curOutValue       = BAD_DOUBLE;

    // Dependents
    m_hasDep            = false;
    m_depName           = "";

    // Triggering
    m_trigger           = "";
    m_triggerVal        = "";
    m_curTriggerVal     = "";
    m_bTriggered        = false;

    // AppCasting
    m_countIn           = 0u;
    m_countOut          = 0u;
    m_errorStr          = "";
    m_appcastStatic     = "Undefined mapping.";
}

mapRange::mapRange(const std::string sDef)
{
    if (sDef.empty()) {
        m_errorStr = "Mapping definition cannot be blank.";
        return; }
    m_normMin           = -1.0;
    m_normMax           = 1.0;

    vector<string> keyValues = parseStringQ(sDef, ',');
    vector<string>::iterator it = keyValues.begin();
    for (; it != keyValues.end(); ++it) {
        string keyVal = *it;
        string key = toupper(MOOSChomp(keyVal, "=", true));
        m_defMap[key] = keyVal; }

    bool bGood = true;
    bGood &= SetRequiredDef("IN_MSG",  m_inName);
    bGood &= SetRequiredDef("IN_MIN",  m_inMin);
    bGood &= SetRequiredDef("IN_MAX",  m_inMax);
    bGood &= SetRequiredDef("OUT_MSG", m_outName);
    bGood &= SetRequiredDef("OUT_MIN", m_outMin);
    bGood &= SetRequiredDef("OUT_MAX", m_outMax);
    if (!bGood) return;

    SetOptionalDef("DEAD", m_dead);
    if (m_dead < 0.0 || m_dead >= 100.0) {
        m_errorStr = "DEAD (dead zone) must be 0 or a positive number < 100.";
        return; }
    m_dead /= 100.0;
    SetOptionalDef("SAT", m_sat);
    if (m_sat < 0.0 || m_sat >= 100.0) {
        m_errorStr = "SAT (saturation) must be 0 or a positive number < 100.";
        return; }
    m_sat /= 100.0;
    SetOptionalDef("NORM_MIN",  m_normMin);
    if (m_normMin < -1.0 || m_normMin > 1.0) {
        m_errorStr = "NORM_MIN must be in range [-1.0, 1.0].";
        return; }
    SetOptionalDef("NORM_MAX",  m_normMax);
    if (m_normMax < -1.0 || m_normMax > 1.0) {
        m_errorStr = "NORM_MAX must be in range [-1.0, 1.0].";
        return; }
    SetOptionalDef("DEP",       m_depName);
    m_hasDep = !m_depName.empty();
    bool bHasTrigger = findDef("TRIG_MSG", m_trigger);
    if (bHasTrigger) {
        SetOptionalDef("TRIG_VAL",   m_triggerVal);
        bHasTrigger = !m_triggerVal.empty();
        if (!bHasTrigger) {
            m_errorStr = "For triggering, TRIG_MSG and TRIG_VAL must be defined together.";
            return; } }
    else
        m_trigger = "";

    // Set constraints (in case min and max are reversed)
    //m_inConstrainMin = (m_inMin < m_inMax) ? m_inMin : m_inMax;
    //m_inConstrainMax = (m_inMin < m_inMax) ? m_inMax : m_inMin;
    m_inConstrainMin = m_inMin;
    m_inConstrainMax = m_inMax;

    // Create the appcast string detaling setup
    stringstream ss;
    ss <<     "        Msg In:   " << m_inName  << "    [" << m_inMin   << ", " << m_inMax   << "]" << endl;
    ss <<     "        Msg Out:  " << m_outName << "    [" << m_outMin  << ", " << m_outMax  << "]" << endl;
    ss <<     "        Norm:     [" << m_normMin << ", " << m_normMax << "]" << endl;
    ss <<     "        Dead:     " << m_dead * 100.0 << "%" << endl;
    ss <<     "        Sat:      " << m_sat  * 100.0 << "%" << endl;
    if (bHasTrigger)
        ss << "        Trigger:  " << m_trigger << " == " << m_triggerVal << endl;
    else
        ss << "        Trigger:  None (always publish)" << endl;
    m_appcastStatic = ss.str();
}

bool mapRange::findDef(const string key, string& storeHere)
{
    unsigned long int found = m_defMap.count(key);
    if (found)
        storeHere = m_defMap[key];
    return found;
}

void mapRange::SetOptionalDef(const string key, string& storeHere)
{
    findDef(key, storeHere);
}

void mapRange::SetOptionalDef(const string key, double& storeHere)
{
    string sVal;
    bool bGood = findDef(key, sVal);
    if (bGood)
        storeHere = strtod(sVal.c_str(), 0);
}

bool mapRange::SetRequiredDef(const string key, double& storeHere)
{
    string sVal;
    bool bGood = SetRequiredDef(key, sVal);
    if (bGood)
        storeHere = strtod(sVal.c_str(), 0);
    return bGood;
}

bool mapRange::SetRequiredDef(const string key, string& storeHere)
{
    bool bGood = findDef(key, storeHere);
    if (!bGood) {
        m_errorStr += "Missing definition for required element ";
        m_errorStr.append(key);
        m_errorStr.append(".");
        return false; }
    return true;
}

void mapRange::SetTriggerValue(const string sVal)
{
    m_curTriggerVal = sVal;
    m_bTriggered    = (m_triggerVal == m_curTriggerVal);
}

string mapRange::GetAppCastStatusString()
{
    stringstream ss;
    ss << "   " << m_inName << endl;
    ss << "   In:        " << m_curInValue   << " (" << m_countIn << " received)" << endl;
    ss << "   Norm:      " << m_curNorm      << endl;
    ss << "   Mapped:    " << m_curOutValue  << endl;
    if (HasTrigger()) {
        if (m_bTriggered)
            ss << "   Trigger:   Triggered on " << m_trigger << " == " << m_triggerVal << endl;
        else
            ss << "   Trigger:   Not publishing (" << m_trigger << ": \"" << m_triggerVal << "\" != \"" << m_curTriggerVal << "\")" <<endl; }
    ss << "   Published: " << m_countOut << "" << endl;
    return ss.str();
}

double mapRange::ConstrainDouble(const double in)
{
    if (in < m_inConstrainMin)      return m_inConstrainMin;
    else if (in > m_inConstrainMax) return m_inConstrainMax;
    return in;
}

void mapRange::SetInputValue(double dIn)
{
    SetInputValues(dIn, BAD_DOUBLE);
}

void mapRange::SetInputValues(string sIn)
{
    if (sIn.empty()) return;
    vector<string> sVec = parseString(sIn, ',');
    if (sVec.size() != 2) return;
    double inVal = strtod(sVec[0].c_str(), 0);
    double inDep = strtod(sVec[1].c_str(), 0);
    SetInputValues(inVal, inDep);
}

void mapRange::SetInputValues(double rawIn, double depRawIn)
{
    m_countIn++;

    // Normalize input axis
    m_curInValue    = ConstrainDouble(rawIn);
    m_curNorm       = MapToNorm(m_curInValue);
    
}

double mapRange::MapToNorm(double d)
{
    return -1.0 + (d - m_inMin) * (2.0) / (m_inMax - m_inMin);
}

#ifdef ASYNCHRONOUS_CLIENT
void mapRange::ConditionalPublish(MOOS::MOOSAsyncCommClient* mComms)
#else
void mapRange::ConditionalPublish(CMOOSCommClient* m_Comms)
#endif
{
    m_bTriggered = true;

    // Only publish when triggering allows
    if (HasTrigger())
        m_bTriggered = (m_triggerVal == m_curTriggerVal);

    if (m_bTriggered) {
        mComms->Notify(m_outName, m_curOutValue);
        m_countOut++; }
}












//
