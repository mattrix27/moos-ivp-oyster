/************************************************************/
/*    NAME: Matt Tung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: OysterROS.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef OysterROS_HEADER
#define OysterROS_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class OysterROS : public AppCastingMOOSApp
{
 public:
   OysterROS();
   ~OysterROS();

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
   std::string m_input_name;
   std::string m_flip_output_name;
   std::string m_pos_output_name;

 private: // State variables
   std::string m_message;
   bool m_first_received;
   float m_curr_x;
   float m_curr_y;
   float m_prev_x;
   float m_prev_y;
};

#endif 
