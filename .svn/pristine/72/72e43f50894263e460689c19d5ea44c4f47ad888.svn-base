/************************************************************/
/*    NAME: Carter Fendley                                              */
/*    ORGN: MIT                                             */
/*    FILE: PingResponder.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef PingResponder_HEADER
#define PingResponder_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class PingResponder : public AppCastingMOOSApp
{
 public:
   PingResponder();
   ~PingResponder() {};

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
   std::string m_incoming_var;
   std::string m_outgoing_var;

   bool m_noise;

 private: // State variables
   double m_last_y;
   double m_last_x;
};

#endif 
