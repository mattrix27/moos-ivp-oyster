/*
 * mapRange.h
 *
 *  Created on: Sep 30, 2015
 *      Author: Alon Yaari
 */

#ifndef POYSTERRC_MAPRANGE_H_
#define POYSTERRC_MAPRANGE_H_

#include <iostream>
#include "MOOS/libMOOS/MOOSLib.h"

#ifndef BAD_DOUBLE
#define BAD_DOUBLE   -999999.99
#define NO_DEPENDENT BAD_DOUBLE
#endif

#define DEBUG_MODE

// Input range [inMin, inMax]
// Output range [outMin, outMax]
// Input value dIn
// Output mapped value dOut
//
//                  (dIn - inMin) x (maxOut - minOut)
// dOut = outMin +  ---------------------------------
//                         (maxIn - minIn)
//

class mapRange {
public:
                mapRange();
                mapRange(const std::string sDef);
                ~mapRange() {}

    void        SetInputValue(const double dIn);
    void        SetInputValues(const std::string sIn);


    bool        IsValid()                       { return m_errorStr.empty(); }
    std::string GetErrorString()                { return m_errorStr; }
    std::string GetSubscribeName()              { return m_inName; }
    std::string GetPublishName()                { return m_outName; }
    std::string GetDependentName()              { return m_depName; }
    std::string GetAppCastSetupString()         { return m_appcastStatic; }
    double      GetOutputMappedValue()          { return m_curOutValue; }
    double      GetNormalizedValue()            { return m_curNorm; }
    double      GetInputValue()                 { return m_curInValue; }
    double      GetInMax()                      { return m_inMax; }
    double      GetOutMax()                     { return m_outMax; }
    double      GetOutMin()                     { return m_outMin; }
    double      GetSaturation()                 { return m_sat; }
    double      GetDeadZone()                   { return m_dead; }
    std::string GetAppCastStatusString();

#ifdef ASYNCHRONOUS_CLIENT
    void        ConditionalPublish(MOOS::MOOSAsyncCommClient* mComms);
#else
    void        ConditionalPublish(CMOOSCommClient* m_Comms);
#endif

    bool        HasTrigger()                    { return !m_trigger.empty(); }
    std::string GetTriggerMessageName()         { return m_trigger; }
    std::string GetTriggerOnValue()             { return m_triggerVal; }
    void        SetTriggerValue(const std::string sVal);

private:
    double      ConstrainDouble(const double in);
    void        SetInputValues(const double rawIn, const double depRawIn);
    double      MapToNorm(const double d);
    bool        findDef(const std::string key, std::string& storeHere);

    // Setup Methods
    bool        SetRequiredDef(const std::string key, std::string& storeHere);
    bool        SetRequiredDef(const std::string key, double& storeHere);
    void        SetOptionalDef(const std::string key, std::string& storeHere);
    void        SetOptionalDef(const std::string key, double& storeHere);



    // Setup params
    std::string m_inDef;
    std::string m_inName;               // Input MOOS message name
    double      m_inMin;                // Input minimum expected value
    double      m_inMax;                // Input maximum expected value
    double      m_inConstrainMin;       // Input lower constraint (in case min and max are reversed)
    double      m_inConstrainMax;       // Input upper constraint (in case min and max are reversed)
    double      m_normMin;              // Normalized minimum
    double      m_normMax;              // Normalized maximum
    std::string m_outName;              // Output MOOS message name
    double      m_outMin;               // Output minimum value output can be mapped to
    double      m_outMax;               // Output maximum value output can be mapped to
    double      m_dead;                 // Percent of dead zone, stored in range [0, 100]. No dead zone = 0.0
    double      m_sat;                  // Percent of end saturation, stored in range [0, 100]. No saturation = 0.0
    std::map<std::string, std::string> m_defMap;

    // Current values
    double      m_curInValue;           // Latest incoming value, BAD_DOUBLE before first input
    double      m_curNorm;              // Latest input value normalized to [-1, 1]. BAD_DOUBLE before first input
    double      m_curDepValue;          // Latest dependent value to the input
    double      m_curDepNorm;           // Latest dependent value normalized to [-1, 1], BAD_DOUBLE before first input and if no dependent
    double      m_curOutValue;          // Latest output value

    // Dependents
    bool        m_hasDep;               // True when a dependent map was assigned
    std::string m_depName;              // Name of dependent mapping, empty string if not applicable

    // Triggering
    std::string m_trigger;              // Trigger message name
    std::string m_triggerVal;           // Trigger on this input on the trigger message
    std::string m_curTriggerVal;        // Latest value received on the trigger message
    bool        m_bTriggered;           // TRUE when latest value triggers, FALSE otherwise

    // AppCasting
    unsigned int m_countIn;             // Number of received inputs
    unsigned int m_countOut;            // Number of published outputs
    std::string m_errorStr;             // Stores error message to pass when definition is bad
    std::string m_appcastStatic;        // Created once, info about setup for appcasting.
};



#endif










//
