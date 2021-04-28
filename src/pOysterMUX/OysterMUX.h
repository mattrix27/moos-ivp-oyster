/************************************************************/
/*    NAME: Matthew Tung                                              */
/*    ORGN: MIT                                             */
/*    FILE: OysterMUX.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef OysterMUX_AYCONTROL_H_
#define OysterMUX_AYCONTROL_H_

#include <string>
#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class OysterMUX : public AppCastingMOOSApp
{
 public:
   		    OysterMUX();
   		    ~OysterMUX() {}
    bool    OnNewMail(MOOSMSG_LIST &NewMail);
    bool    RegisterForMOOSMessages();
    bool    Iterate();
    bool    OnConnectToServer();
    bool    OnStartUp();
    bool    buildReport();

 protected:
    bool    SetParam_INPUT(std::string sVal);

    std::map<std::string, int> m_priority_map;

    std::string m_RC_in;
    std::string m_AUTO_in;
    std::string m_out_name;

    std::string m_curr_out_val;

    int m_p; 
    double m_start_time;
    double m_refresh;
};

#endif 
