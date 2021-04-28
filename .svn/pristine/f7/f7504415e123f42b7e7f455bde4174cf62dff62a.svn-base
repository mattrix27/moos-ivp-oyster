/************************************************************/
/*    NAME: Oliver MacNeely                                              */
/*    ORGN: MIT                                             */
/*    FILE: ShorePing.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ShorePing.h"


using namespace std;

//---------------------------------------------------------
// Constructor

ShorePing::ShorePing()
{
  m_iterations = 0;
  m_timewarp   = 1;
  m_pings      = 0;
}

//---------------------------------------------------------
// Destructor

ShorePing::~ShorePing()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool ShorePing::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key = msg.GetKey();
    string sval = msg.GetString();

#if 0 // Keep these around just for template
    string key   = msg.GetKey();
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

bool ShorePing::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
	
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool ShorePing::Iterate()
{

  string ping_value = "ID=" + to_string(m_iterations);

  m_Comms.Notify("PING", ping_value);

  m_iterations++;
  
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool ShorePing::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      robot_name   = stripBlankEnds(*p);

    }
  }
  
  m_timewarp = GetMOOSTimeWarp();

  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void ShorePing::RegisterVariables()
{
}

