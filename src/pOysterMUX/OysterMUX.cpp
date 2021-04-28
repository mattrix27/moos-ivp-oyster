/************************************************************/
/*    NAME: Matthew Tung                                              */
/*    ORGN: MIT                                             */
/*    FILE: OysterMUX.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <sstream>
#include <iterator>
#include "MBUtils.h"
#include "OysterMUX.h"

using namespace std;

//---------------------------------------------------------
// Constructor

OysterMUX::OysterMUX()
{
  m_p = 9999;
  m_refresh = 0.5;
  m_start_time = 0;
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool OysterMUX::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string msgKey = msg.GetKey();

    if (m_priority_map.count(msgKey)) {
      int n_p = m_priority_map[msgKey];

      if ((m_start_time == 0) || ((msg.GetTime()-m_start_time) > m_refresh) || (n_p <= m_p)) {
        m_p = n_p;
        m_start_time = msg.GetTime();

        m_curr_out_val = msg.GetString();
        Notify(m_out_name, m_curr_out_val);
      }
      else {
        stringstream ss;
        ss << "START TIME: " << m_start_time << " DIFF: " << (msg.GetTime() - m_start_time) << " MOOSTIME: " << MOOSTime();
        Notify("DEBUG", ss.str());
      }
    }
  }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool OysterMUX::OnConnectToServer()
{
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool OysterMUX::Iterate()
{
  // Notify(m_out_name, m_curr_out_val);

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool OysterMUX::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    bool bhandled = true;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string orig  = *p;
      string line  = *p;
      string param = tolower(biteStringX(line, '='));
      string value = line;
      if (value.empty()) {
        // reportConfigWarning("sVal is blank.");
        cout << "sad" << endl;
      }
      else {
        if(param == "input") {
          bhandled = SetParam_INPUT(value);
        }
        else if(param == "out") {
          m_out_name = value;
        }
        else if(param == "refresh") {
          m_refresh = stod(value);
        }
      }
    }
  }

  RegisterMOOSVariables();
  RegisterVariables();

  return(true);
}


bool OysterMUX::SetParam_INPUT(string sVal) {
  vector<string> keyValues = parseStringQ(sVal, ',');
  vector<string>::iterator it = keyValues.begin();
  int priority = 9999;
  string in_msg;
  for (; it != keyValues.end(); ++it) {
    string keyVal = *it;
    string key = toupper(MOOSChomp(keyVal, "=", true));
    if (key == "PRIORITY") {
      priority = atoi(keyVal.c_str());
    }
    else if (key == "IN_MSG") {
      in_msg = keyVal;
    }
  }

  cout << "IN_MSG: " << in_msg << " PRIORITY: " << priority << endl;
  m_priority_map[in_msg] = priority;
  Register(in_msg, 0.0);

  return(true);
}


bool OysterMUX::buildReport()
{
    m_msgs << "CURRENT PRIORITY: " << m_p << endl;
    m_msgs << "DRIVE COMMMAND: " << m_curr_out_val << endl;

    return true;
}
