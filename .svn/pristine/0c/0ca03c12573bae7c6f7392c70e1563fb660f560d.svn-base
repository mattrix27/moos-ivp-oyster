/************************************************************/
/*    NAME: Carter Fendley                                              */
/*    ORGN: MIT                                             */
/*    FILE: TimeWatch.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef TimeWatch_HEADER
#define TimeWatch_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class TimeWatch : public AppCastingMOOSApp
{
 public:
   TimeWatch();
   ~TimeWatch() {};

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables
   std::vector<std::string> m_watch_keys;
   long m_localtime_offset;
   long m_threshhold;
 private: // State variables
};

#endif 
