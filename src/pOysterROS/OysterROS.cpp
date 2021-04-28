/************************************************************/
/*    NAME: Matt Tung                                              */
/*    ORGN: MIT, Cambridge MA                               */
/*    FILE: OysterROS.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "OysterROS.h"

using namespace std;

//---------------------------------------------------------
// Constructor

OysterROS::OysterROS()
{
  m_input_name = "NMEA_RECEIVED";
  m_pos_output_name = "RELATIVE_POS";
  m_flip_output_name = "FLIP_COMMAND";
  m_message = "";
  m_first_received = false;
  m_curr_x = 0.0;
  m_curr_y = 0.0;
  m_prev_x = 0.0;
  m_prev_y = 0.0;
}

//---------------------------------------------------------
// Destructor

OysterROS::~OysterROS()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool OysterROS::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

     if(key == m_input_name) {
       string message = msg.GetString();
       m_message = message;
       string type = biteStringX(message, ',');
       string time = biteStringX(message, ',');
       if (type == "POS") {
          Notify(m_pos_output_name, message);
          float x = stod(biteStringX(message, ','));
          float y = stod(message);

          if (!m_first_received) {
            m_prev_x = m_curr_x;
            m_prev_y = m_curr_y;
          }
          else {
            m_first_received = true;
          }
	  m_curr_x = x;
          m_curr_y = y;
       }
       else if (type == "FLIP") {
          string command = biteStringX(message, ',');
          Notify(m_flip_output_name, command);
       }
     } 
     
     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool OysterROS::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool OysterROS::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  string relative_pos = to_string(m_curr_x) + ',' + to_string(m_curr_y);

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool OysterROS::OnStartUp()
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
      m_input_name = value;
      handled = true;
    }
    else if(param == "flip_output") {
      m_flip_output_name = value;
      handled = true;
    }
    else if(param == "pos_output") {
      m_pos_output_name = value;
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

void OysterROS::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(m_input_name, 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool OysterROS::buildReport() 
{
  m_msgs << "============================================" << endl;
  m_msgs << "File:                                       " << endl;
  m_msgs << "============================================" << endl;

  m_msgs << "MESSAGE: " << m_message << endl;
  return(true);
}




