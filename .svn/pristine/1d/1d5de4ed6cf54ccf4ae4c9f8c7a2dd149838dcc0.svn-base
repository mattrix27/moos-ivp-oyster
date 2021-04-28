/*
 * mapValues.h
 *
 *  Created on: Sep 30, 2015
 *      Author: Alon Yaari
 */

#ifndef PMAPVALUES_AYCONTROL_H_
#define PMAPVALUES_AYCONTROL_H_

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "mapRange.h"
#include "mapTrigger.h"

class mapValues : public AppCastingMOOSApp
{
public:
			mapValues();
            ~mapValues() {}
    bool    OnNewMail(MOOSMSG_LIST &NewMail);
    bool    Iterate();
    bool    OnConnectToServer();
    bool    OnStartUp();
    bool    buildReport();

protected:
    void    PublishOutput();
    bool    RegisterForMOOSMessages();
    bool    SetParam_RANGE(std::string sVal);
    bool    SetParam_TRIGGER(std::string sVal);
    bool    SetParam_DEBUG_AXIS0(std::string sVal);
    bool    SetParam_DEBUG_AXIS1(std::string sVal);
    std::map<std::string, mapRange> m_ranges;
    std::map<std::string, mapTrigger> m_triggers;
    std::string m_appCastAxisTriggers;

    bool m_debugMode;
    std::string m_strDebug0;
    std::string m_strDebug1;
};

#endif







//
