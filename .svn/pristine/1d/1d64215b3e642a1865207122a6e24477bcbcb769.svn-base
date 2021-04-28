/************************************************************/
/*    NAME: Oliver MacNeely                                              */
/*    ORGN: MIT                                             */
/*    FILE: ShorePing.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef ShorePing_HEADER
#define ShorePing_HEADER

#include "MOOS/libMOOS/MOOSLib.h"

class ShorePing : public CMOOSApp
{
 public:
   ShorePing();
   ~ShorePing();

   std::string  PING;
   std::string  PING_OUT;
   std::string  PING_IN;
   std::string  robot_name;


 protected:
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
   unsigned int m_iterations;
   double       m_timewarp;
   int          m_pings;
};

#endif 
