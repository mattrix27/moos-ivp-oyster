/*
 * OysterRC.h
 *
 */

#ifndef POYSTERRC_AYCONTROL_H_
#define POYSTERRC_AYCONTROL_H_

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "mapRange.h"
#include "mapTrigger.h"
#include "math.h"
#include "algorithm"

class OysterRC : public AppCastingMOOSApp
{
public:
			OysterRC();
            ~OysterRC() {}
    bool    OnNewMail(MOOSMSG_LIST &NewMail);
    bool    Iterate();
    bool    OnConnectToServer();
    bool    OnStartUp();
    bool    buildReport();

protected:
    void    PublishOutput();
    void    PublishRC();
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
    std::string m_RCOutName;
    std::string m_RCOutVal;
    std::string m_RCOutFlip;
    
    double m_x;
    double m_y;
    double m_angle;
    double m_magnitude;
    double m_dbl_thres;
    bool m_forward;

    std::string m_safety;
    std::string m_flip;
};

#endif







//
