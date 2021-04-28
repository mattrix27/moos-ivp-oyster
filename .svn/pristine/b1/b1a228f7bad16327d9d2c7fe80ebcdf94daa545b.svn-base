/************************************************************/
/*    NAME: Carter Fendley                                              */
/*    ORGN: MIT                                             */
/*    FILE: TimeWatch.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "TimeWatch.h"
#include <time.h>

using namespace std;

//---------------------------------------------------------
// Constructor

TimeWatch::TimeWatch()
{
  m_localtime_offset = 0;
  m_threshhold = 0;
  m_watch_keys.push_back("NODE_REPORT");
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool TimeWatch::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    
    for(int i=0; i<m_watch_keys.size(); i++){
      if(key == m_watch_keys[i]){
	std::string value = msg.GetString();
	
	long time = stol(tokStringParse(value, "TIME",',','='));
	//std::time_t localtime = std::time(nullptr) - m_localtime_offset;
	
	if(std::abs(time - (m_curr_time + m_localtime_offset)) > m_threshhold){
	  reportRunWarning("\"" + key + "\" time is greater then threshhold on: "+ tokStringParse(value,"NAME",',','='));
	  reportEvent("Threshhold exceeded! LocalTime: " + to_string(m_curr_time + m_localtime_offset) + " RemoteTime: " + to_string(time));
	}
	break;
      }
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

bool TimeWatch::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool TimeWatch::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool TimeWatch::OnStartUp()
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
    if(param == "WATCH_VAR") {
      m_watch_keys.push_back(line);
      handled = true;
    }else if(param == "THRESHHOLD"){
      m_threshhold = std::abs(stol(line));
      handled = true;
    }
    else if(param == "LOCAL_OFFSET") {
      m_localtime_offset = stol(line);
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

void TimeWatch::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  
  for(int i=0; i<m_watch_keys.size(); i++){
    Register(m_watch_keys[i], 0);
  }
}


//------------------------------------------------------------
// Procedure: buildReport()

bool TimeWatch::buildReport() 
{
  
  m_msgs << endl;
  for(int i=0; i<m_watch_keys.size(); i++){
    m_msgs << "Watching: " << m_watch_keys[i] << endl;
  }
  m_msgs << "Threshhold: " << m_threshhold << endl;
  m_msgs << "Localtime offset: " << m_localtime_offset << endl;

  return(true);
}




