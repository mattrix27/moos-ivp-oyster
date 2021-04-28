/************************************************************/
/*    NAME: Arjun Gupta                                              */
/*    ORGN: MIT                                             */
/*    FILE: NodeReportParse.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "NodeReportParse.h"

using namespace std;

//---------------------------------------------------------
// Constructor

NodeReportParse::NodeReportParse()
{
}

//---------------------------------------------------------
// Destructor

NodeReportParse::~NodeReportParse()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool NodeReportParse::OnNewMail(MOOSMSG_LIST &NewMail)
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
    if(key == "NODE_REPORT")
      ProcessNodeReport(sval);
    else
      reportRunWarning("Unhandled Mail: " + key);
   }	
   return(true);
}

//---------------------------------------------------------
//Procedure: ProcessNodeReport
//Function: Takes in a node report and then sends it back out with the source name appended

void NodeReportParse::ProcessNodeReport(string report)
{
  string val= report;
  string name= parseStringQ(val,',')[0];
  biteStringX(name,'=');
  for(int i = 0; i < name.size(); i++) {
    name.at(i) = toupper(name.at(i));
  }
  string notifier= "NODE_REPORT_"+name;
  Notify(notifier, report);
}
//---------------------------------------------------------
// Procedure: OnConnectToServer

bool NodeReportParse::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool NodeReportParse::Iterate()
{
  AppCastingMOOSApp::Iterate();
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool NodeReportParse::OnStartUp()
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
    if(param == "FOO") {
      handled = true;
    }
    else if(param == "BAR") {
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

void NodeReportParse::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("NODE_REPORT", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool NodeReportParse::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "File:                                        \n";
  m_msgs << "============================================ \n";

  ACTable actab(4);
  actab << "Alpha | Bravo | Charlie | Delta";
  actab.addHeaderLines();
  actab << "one" << "two" << "three" << "four";
  m_msgs << actab.getFormattedString();

  return(true);
}




