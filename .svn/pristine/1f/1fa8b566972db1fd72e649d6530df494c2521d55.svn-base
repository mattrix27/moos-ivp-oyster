/************************************************************/
/*    NAME: Hugh Dougherty                                              */
/*    ORGN: MIT                                             */
/*    FILE: Blinkstick.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef Blinkstick_HEADER
#define Blinkstick_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class Blinkstick : public AppCastingMOOSApp
{
 public:
   Blinkstick();
   ~Blinkstick();

 protected:
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   void RegisterVariables();
   bool buildReport();

 private: // Configuration variables

 private: // State variables
   unsigned int m_iterations;
   double       m_timewarp;
   int          m_good_message_count;
   int          m_bad_message_count;
   std::string  m_cmd;
};

#endif 
