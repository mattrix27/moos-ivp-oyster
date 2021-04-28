/************************************************************/
/*    NAME: Carter Fendley                                              */
/*    ORGN: MIT                                             */
/*    FILE: PingResponder.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "PingResponder.h"

using namespace std;

//---------------------------------------------------------
// Constructor

PingResponder::PingResponder()
{
  m_incoming_var = "PING_REQUEST";
  m_outgoing_var = "PING_RESPONSE";
  m_noise = true;
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool PingResponder::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    
    if(key == "NAV_X"){
      m_last_x = msg.GetDouble();
    }else if(key == "NAV_Y"){
      m_last_y = msg.GetDouble();
    }else if(key == m_incoming_var){
      if (m_noise && (rand() % 100) > 50) {
	continue;
      }
      std::string id = tokStringParse(msg.GetString(), "ID", ',', '=');
      m_Comms.Notify(m_outgoing_var, "id="+id+",x="+to_string(m_last_x)+",y="+to_string(m_last_y));
      reportEvent("Recived ping: "+msg.GetString());
    }else if(key != "APPCAST_REQ"){
      reportRunWarning("Unhandled Mail: " + key);
    }

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
  }
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool PingResponder::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool PingResponder::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool PingResponder::OnStartUp()
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
    string param = toupper(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "INCOMING_VAR") {
      m_incoming_var = line;
      handled = true;
    }
    else if(param == "OUTGOING_VAR") {
      m_outgoing_var = line;
      handled = true;
    }
    else if(param == "NOISE"){
      if(line == "true"){
	m_noise = true;
      }
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

void PingResponder::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register(m_incoming_var);

  Register("NAV_X");
  Register("NAV_Y");
}


//------------------------------------------------------------
// Procedure: buildReport()

bool PingResponder::buildReport() 
{
  m_msgs << "Listening for var: " << m_incoming_var << endl;
  m_msgs << "Responding on var: " << m_outgoing_var << endl;

  m_msgs << endl;

  m_msgs << "X: " << m_last_x << endl;
  m_msgs << "Y: " << m_last_y << endl;
  //m_msgs << actab.getFormattedString();

  return(true);
}
