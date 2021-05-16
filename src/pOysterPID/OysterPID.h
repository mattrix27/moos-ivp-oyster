/************************************************************/
/*    NAME: Matt Tung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: OysterPID.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef OysterPID_HEADER
#define OysterPID_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class OysterPID : public AppCastingMOOSApp
{
 public:
   OysterPID();
   ~OysterPID();

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
   std::string m_error_message_name;
   std::string m_AutoOutName;

   double m_kp_y;
   double m_kd_y;
   double m_ki_y;

   double m_kp_x;
   double m_kd_x;
   double m_ki_x;
   
   double m_alpha_y;    // low pass filter constant
   double m_alpha_x;

   double m_heartbeat_timer;

 private: // State variables
   std::string m_AutoOutVal;

   double m_error_y  = 0.0;
   double m_sum_error_y = 0.0;
   double m_d_error_y = 0.0;
   double m_filt_d_error_y = 0.0;
   double m_error_pre_y=0.0;

   double m_error_x  = 0.0;
   double m_sum_error_x = 0.0;
   double m_d_error_x = 0.0;
   double m_filt_d_error_x = 0.0;
   double m_error_pre_x;

   double m_Pcontrol_y;
   double m_Icontrol_y;
   double m_Dcontrol_y;
   double m_thrust_y=0;
   double m_flag_y=false;

   double m_Pcontrol_x;
   double m_Icontrol_x;
   double m_Dcontrol_x;
   double m_thrust_x=0;
   bool m_flag_x=false;

   double m_error_a;

   double m_thrust_r;
   double m_thrust_l;

   double m_timer;
   double m_loop_time;

   double m_heartbeat;
};

#endif 
