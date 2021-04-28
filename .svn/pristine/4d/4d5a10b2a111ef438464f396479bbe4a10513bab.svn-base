/************************************************************/
/*    NAME: Caileigh Fitzgerald                                              */
/*    ORGN: MIT                                             */
/*    FILE: LEDInterpreter.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "LEDInterpreter.h"
bool debug = true;

using namespace std;

//---------------------------------------------------------
// Constructor

LEDInterpreter::LEDInterpreter()
{
}

//---------------------------------------------------------
// Destructor

LEDInterpreter::~LEDInterpreter()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool LEDInterpreter::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  bool handled = false;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key   = msg.GetKey();
    string state  = msg.GetString(); // true = m_ACTIVE , false = m_OFF

    if (key == m_tagged_var) {// * NEED TO CHANGE CONDITION keys & sval TO MATCH UFLDXX
      m_Comms.Notify(key, state);    
      tag_received = true;        
    } else {
      tag_received = false;
    }

    if (key == m_flag_zone_var) {
      m_Comms.Notify(key, state); 
      flag_zone_received = true;
    } else {
      flag_zone_received = false;
    }
    
    if (key == m_out_of_bounds_var) {
      m_Comms.Notify(key, state); 
      bounds_received = true;
    } else {
      bounds_received = false;
    }

    if (key == m_have_flag_var) {
      m_Comms.Notify(key, state); 
      have_flag_received = true;
    } else {
      have_flag_received = false;
    }

    if (key == m_in_tag_range_var) {
      m_Comms.Notify(key, state);   
      tag_zone_received = true;  
    } else {
      tag_zone_received = false;
    }

    buildReport();

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

bool LEDInterpreter::OnConnectToServer()
{
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool LEDInterpreter::Iterate()
{
  AppCastingMOOSApp::Iterate();
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool LEDInterpreter::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  bool handled = false;
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string orig  = *p;
      string line  = *p;
      string param = toupper(biteStringX(line, '='));
      string value = line;

      if (debug)
        cout << "value=" << value << endl;
      
      if(param == "TAGGED")
      {
        m_tagged_var=value;
        handled = true;
      }
      if (param == "OUT_OF_BOUNDS")
      {
        m_out_of_bounds_var=value;
        handled = true;
      }
      if (param == "HAVE_FLAG") 
      {
        m_have_flag_var=value;
        handled = true;
      }
      if (param == "IN_TAG_RANGE") 
      {
        m_in_tag_range_var=value;
        handled = true;
      }
      if (param == "IN_FLAG_ZONE") 
      {
        m_flag_zone_var=value;
        handled = true;
      }

      if(!handled)
        reportUnhandledConfigWarning(orig);

      handled = false; // reset
    }
  }
  
  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void LEDInterpreter::RegisterVariables()
{
  AppCastingMOOSApp::RegisterVariables();

  Register(m_tagged_var        , 0);
  Register(m_out_of_bounds_var , 0);
  Register(m_have_flag_var     , 0);
  Register(m_in_tag_range_var  , 0);
  Register(m_flag_zone_var     , 0);\
}

bool LEDInterpreter::buildReport()
{
  m_msgs << " Mail values - have we received info on vars    " 
         << boolalpha << endl
         << " ===========================================              \n\n"
         << " " << m_tagged_var << " [" <<  tag_received            << "]\n"
         << " " << m_out_of_bounds_var << " [" << bounds_received   << "]\n"
         << " " << m_have_flag_var << " [" << have_flag_received    << "]\n"
         << " " << m_in_tag_range_var << " [" << tag_zone_received  << "]\n"
         << " " << m_flag_zone_var << " [" << flag_zone_received    << "]\n"
         << endl;

  return(true);
}
