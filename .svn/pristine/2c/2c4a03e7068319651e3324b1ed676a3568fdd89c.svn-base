/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: Authority.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "Authority.h"

using namespace std;

//---------------------------------------------------------
// Constructor

Authority::Authority()
{
  m_internal_aggressive_state="FALSE";
  m_authority_active = false;
}

//---------------------------------------------------------
// Destructor

Authority::~Authority()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Authority::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

     if(key == "FOO") 
       cout << "great!";
     else if(key=="AGGRESSIVE"){
       //we will be bombarded with updates to AGGRESSIVE
       std::string sval = msg.GetString();
       handleAggressivePost(sval);
     }
     else if(key=="SELF_AUTHORIZE"){
       std::string sval = msg.GetString();
       if(sval == "TRUE"){
         m_authority_active = true;
       }
       else if(sval =="FALSE"){
         m_authority_active = false;
       }
     }

     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Authority::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Authority::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Authority::OnStartUp()
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

void Authority::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("AGGRESSIVE",0);
  Register("SELF_AUTHORIZE",0);
  // Register("FOOBAR", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool Authority::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "Internal Aggressive State " << m_internal_aggressive_state << endl;
  m_msgs << "============================================ \n";
  m_msgs << "Self Authorize: " << m_authority_active << endl;

  return(true);
}

//------------------------------------------------------------
// Procedure: handleAggressivePost()

void Authority::handleAggressivePost(std::string value) 
{

  //we will be bombarded with AGGRESSIVE == TRUE and FALSE
  //let us only post when the first TRUE comes in
  if(m_internal_aggressive_state == "FALSE" && value == "TRUE"){
    //this is transition from internally being FALSE to outside being true
  //when triggered do these notifications

    if(m_authority_active == true){
      Notify("ACTION","DEFEND");
      string triggerAudio = "src_node=" + m_host_community +",dest_node=blue_one,var_name=SAY_MOOS,string_val=file=sounds/defend_because_on_our_side.wav";
      Notify("NODE_MESSAGE_LOCAL",triggerAudio);
    }
  }
  m_internal_aggressive_state = value;

}



