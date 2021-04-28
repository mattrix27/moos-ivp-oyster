/************************************************************/
/*    NAME: Hugh Dougherty                                  */
/*    ORGN: MIT                                             */
/*    FILE: Blinkstick.cpp                                  */
/*    DATE: January 7, 2016                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "Blinkstick.h"
#include <stdlib.h>
#include <string>

using namespace std;

//---------------------------------------------------------
// Constructor

Blinkstick::Blinkstick()
{
  m_iterations = 0;
  m_timewarp   = 1;
}

//---------------------------------------------------------
// Destructor

Blinkstick::~Blinkstick()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Blinkstick::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();


  //iBlink C++ for MOOS                                                      
    if (key == "BLINK")
      {
	string test;
	//	test = "blinkstick --pulse red --repeats=5";
		test = "blinkstick ";
		test = test + sval;
	system(test.c_str());
	return 0;
      }
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Blinkstick::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);
	
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool Blinkstick::Iterate()
{
  AppCastingMOOSApp::Iterate();

  m_iterations++;
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Blinkstick::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);
      
      if(param == "FOO") {
        //handled
      }
      else if(param == "BAR") {
        //handled
      }
    }
  }
  
  m_timewarp = GetMOOSTimeWarp();

  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void Blinkstick::RegisterVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  Register("BLINK", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()
//   Example:
// 
// Configuration Parameters:
// -------------------------
//     Default Voice: alex
//      Default Rate: 200
//   Max Utter Queue: 1000
//   Min Utter Inter: 1
//
// Status:
// -------------------------
//   Utter Queue Size: 0
//             Filter: none    (ignore, hold)
//
// Source           Time  Time  Utterance
//                  Recd  Post  Utterance
// --------         ----  ----------------------------------
// archie:pHelmIvP  3.22  15.1  Returning
// betty:pHelmIvP   14.2  14.1  Deployed

bool Blinkstick::buildReport()
{
  m_msgs << "The # of good messages: " << m_good_message_count    << endl;
  m_msgs << "The # of bad  messages: " << m_bad_message_count     << endl;
  
  string test;
  m_msgs << endl;
  m_msgs << "Usage: blinkstick [options] [color]" << endl;
  m_msgs << "Your Command: " << system(test.c_str()) << m_cmd     << endl; 

  return(true);
}
