/************************************************************/
/*    NAME: Matt Tung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: OysterPID.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "OysterPID.h"

using namespace std;

//---------------------------------------------------------
// Constructor

OysterPID::OysterPID()
{
   m_error_message_name = "RELATIVE_POS";
   m_AutoOutName = "AUTO";
   m_AutoOutVal = "";

   m_kp_y = 0.5;
   m_kd_y = 0;
   m_ki_y = 0;

   m_kp_x = 0.5;
   m_kd_x = 0;
   m_ki_x = 0;
   
   m_alpha_y = 0.25;
   m_alpha_x = 0.25;

   m_error_y  = 0.0;
   m_sum_error_y = 0.0;
   m_d_error_y = 0.0;
   m_filt_d_error_y = 0.0;
   m_error_pre_y = 0.0;

   m_error_x = 0.0;
   m_sum_error_x = 0.0;
   m_d_error_x = 0.0;
   m_filt_d_error_x = 0.0;
   m_error_pre_x = 0.0;

   m_Pcontrol_y = 0.0;
   m_Icontrol_y = 0.0;
   m_Dcontrol_y = 0.0;
   m_thrust_y= 0.0;
   m_flag_y = false;

   m_Pcontrol_x = 0.0;
   m_Icontrol_x = 0.0;
   m_Dcontrol_x = 0.0;
   m_thrust_x = 0.0;
   m_flag_x = false;

   m_error_a = 0.0;

   m_thrust_r = 0.0;
   m_thrust_l = 0.0;

   m_timer = 0.0;
   m_loop_time = 0.0;
  
   m_heartbeat_timer = 10.0;
   m_heartbeat = 0.0;
}

//---------------------------------------------------------
// Destructor

OysterPID::~OysterPID()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool OysterPID::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();


     if(key == m_error_message_name) {
       string sVal = msg.GetString();
       vector<string> keyValues = parseStringQ(sVal, ',');
       vector<string>::iterator it = keyValues.begin();
       for (; it != keyValues.end(); ++it) {
         string keyVal = *it;
         string key = toupper(MOOSChomp(keyVal, "=", true));
         if (key == "X") {
           m_error_pre_x = m_error_x;
           m_error_x = stod(keyVal);
           if (m_error_x == 0) {
             m_sum_error_x = 0;
             m_error_pre_x = 0;
           }
           m_heartbeat = MOOSTime();
         }
         else if (key == "Y") {
           m_error_pre_y = m_error_y;
           m_error_y = stod(keyVal);
           if (m_error_y == 0) {
             m_sum_error_y = 0;
             m_error_pre_y = 0;
           }
         }
         else if (key == "ANGLE") {
           m_error_a = stod(keyVal);
         }
       }      
     } 
     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool OysterPID::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool OysterPID::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!

  m_timer = MOOSTime();

  if (m_loop_time>0){
    m_d_error_y = (m_error_y-m_error_pre_y)/m_loop_time;
  }
  m_filt_d_error_y = m_alpha_y * m_d_error_y + (1 - m_alpha_y) * m_filt_d_error_y; // filtered d_error
  m_sum_error_y = m_error_y*m_loop_time+m_sum_error_y;         // integral of error
  
  m_Pcontrol_y = m_kp_y*m_error_y;      // P control action
  m_Icontrol_y = m_ki_y*m_sum_error_y;      // I control action
  m_Dcontrol_y = m_kd_y*m_d_error_y;      // D control action
  
  m_thrust_y =  m_Pcontrol_y + m_Icontrol_y + m_Dcontrol_y;        // controller output
    
  //Angle controller
  if (m_loop_time>0){
    m_d_error_x = (m_error_x-m_error_pre_x)/m_loop_time;   // derivative of error
  }
  m_filt_d_error_x = m_alpha_x * m_d_error_x + (1 - m_alpha_x) * m_filt_d_error_x;    // filtered d_error
  m_error_pre_x = m_error_x;    // previous error
  m_sum_error_x = m_error_x*m_loop_time+m_sum_error_x;         // integral of error
  
  m_Pcontrol_x = m_kp_x*m_error_x;      // P control action
  m_Icontrol_x = m_ki_x*m_sum_error_x;      // I control action
  m_Dcontrol_x = m_kd_x*m_d_error_x;      // D control action
  
  m_thrust_x =  m_Pcontrol_x + m_Icontrol_x + m_Dcontrol_x;        // controller output
  
  
  //Combine thrust commands
  m_thrust_r=m_thrust_y+m_thrust_x;
  m_thrust_l=m_thrust_y-m_thrust_x;
  
  if (m_thrust_r>1.0){
    m_thrust_r=1.0;
  }
  if (m_thrust_r<-1.0){
    m_thrust_r=-1.0;
  }
  if (m_thrust_l>1.0){
    m_thrust_l=1.0;
  }
  if (m_thrust_l<-1.0){
    m_thrust_l=-1.0;
  }
  
  if (MOOSTime() - m_heartbeat >= m_heartbeat_timer) {
    m_thrust_l = 0.0;
    m_thrust_r = 0.0;
  }

  m_AutoOutVal = "LEFT=" + to_string(m_thrust_l) + "," + "RIGHT=" + to_string(m_thrust_r);
  Notify(m_AutoOutName, m_AutoOutVal);

  m_loop_time = (MOOSTime() - m_timer) / 1000000.0;

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool OysterPID::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = tolower(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "input") {
      m_error_message_name = value;
      handled = true;
    }
    else if(param == "out_msg") {
      m_AutoOutName = value; 
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);
  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void OysterPID::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(m_error_message_name, 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool OysterPID::buildReport() 
{
  m_msgs << "" << endl;

  return(true);
}




