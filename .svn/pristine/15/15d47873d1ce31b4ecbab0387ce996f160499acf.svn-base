/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: Reliable.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef Reliable_HEADER
#define Reliable_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class Reliable : public AppCastingMOOSApp
{
 public:
   Reliable();
   ~Reliable();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

  void interruptReliability();
 private: // Configuration variables

 private: // State variables
  std::string m_reliable_state;
  std::string m_action_state;
};

#endif 
