/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: Reliable.cpp                                    */
/*    DATE: January 26 2019                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "Reliable.h"

using namespace std;

//---------------------------------------------------------
// Constructor

Reliable::Reliable()
{
  m_reliable_state = "TRUE";
  m_action_state="";
}

//---------------------------------------------------------
// Destructor

Reliable::~Reliable()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Reliable::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    if(key == "RELIABLE"){

      string sval  = msg.GetString(); 
      m_reliable_state = sval;
      if(m_reliable_state == "FALSE"){
        //we switch the current action
        if(m_action_state == "" ){
          //state has not been set yet
          continue;
        }
        else {
          //state has been set -- we interrupt

          interruptReliability();
        }
      }

    }
    else if(key == "ACTION") {

      string msrc  = msg.GetSource();
      if(msrc == "pReliable") {
        //this post came from us so ignore switching
        continue;
      }
      //based on reliable we do right thing or not
      string sval  = msg.GetString(); 
      m_action_state = sval;
      if (m_reliable_state == "FALSE") {
        //we interrupt reliability
        interruptReliability();

      }

      
    }
     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Reliable::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Reliable::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Reliable::OnStartUp()
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
    if(param == "foo") {
      handled = true;
    }
    else if(param == "bar") {
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

void Reliable::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("RELIABLE", 0);
  Register("ACTION", 0);
  // Register("FOOBAR", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool Reliable::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "RELIABLE = " << m_reliable_state << endl;
  m_msgs << "============================================ \n";

  // ACTable actab(4);
  // actab << "Alpha | Bravo | Charlie | Delta";
  // actab.addHeaderLines();
  // actab << "one" << "two" << "three" << "four";
  // m_msgs << actab.getFormattedString();

  return(true);
}


void Reliable::interruptReliability()
{
  //given current action state we will flip
  //to something opposite
  if(m_action_state == "ATTACK_LEFT" || m_action_state == "ATTACK_RIGHT" || m_action_state == "ATTACK"){
    Notify("ACTION","DEFEND");
  }
  else if( m_action_state == "TRAIL" || m_action_state == "COVER"){
    Notify("ACTION","STATION");
      }
  else if( m_action_state =="STATION" || m_action_state == "INTERCEPT" || m_action_state == "DEFEND"){
    Notify("ACTION","ATTACK");
  }
}

