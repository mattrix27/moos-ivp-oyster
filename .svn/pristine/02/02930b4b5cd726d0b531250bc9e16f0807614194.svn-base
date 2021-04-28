/************************************************************/
/*    NAME: Mohamed Saad Ibn Seddik                                            */
/*    ORGN: MIT                                             */
/*    FILE: RangeEvent.cpp                                        */
/*    DATE: 2016/03/15                                      */
/************************************************************/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "RangeEvent.h"
#include "NodeRecordUtils.h"
#include "ColorParse.h"


using namespace std;

//---------------------------------------------------------
// Constructor

RangeEvent::RangeEvent()
{
  m_vx = 0.;
  m_vy = 0.;
  m_speed = 0.;
  m_heading = 0.;

  m_dbtime = 0.;

  m_min_range = 0.;
  m_max_range = 10.;
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool RangeEvent::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

    string key  = msg.GetKey();
    string sval = msg.GetString();

    bool handled = false;
    if(key == "NODE_REPORT")
      handled = onNodeReport(sval);
    else if(key == "NODE_REPORT_LOCAL")
      handled = onNodeReportLocal(sval);
    else if(key == "DB_UPTIME"){
      m_dbtime = msg.GetDouble();
      handled = true;
    }
    if(!handled)
      reportRunWarning("Unhandled Mail: " + key);
  }

  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool RangeEvent::OnConnectToServer()
{
#if 0 // Keep this for messages that do not require a callback but just a simple read
  AddMOOSVariable("bar_msg", "BAR_IN", "BAR_OUT", 0);
  // incoming BAR_IN is automatically updated thru UpdateMOOSVariables();
  // to get the latest value of BAR_OUT, call :
  // double d = GetMOOSVar("bar_msg")->GetDoubleVal(); // if value is double
  // string s = GetMOOSVar("bar_msg")->GetStringVal(); // if value is string
#endif

#if 0 // Keep this as an example for callbacks
  AddMOOSVariable("foo_msg", "FOO_IN", "FOO_OUT", 0); // foo_msg is a local name
  AddActiveQueue("foo_callback", this, &RangeEvent::onMessageFoo);
  AddMessageRouteToActiveQueue("foo_callback", "FOO_IN");
#endif

  registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void RangeEvent::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();

  Register("NODE_REPORT",0);
  Register("NODE_REPORT_LOCAL",0);
  Register("DB_UPTIME",0);

}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool RangeEvent::Iterate()
{
  AppCastingMOOSApp::Iterate();

  publishEvents();

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: publishEvents()

void RangeEvent::publishEvents()
{
  map<string, NodeRecord>::iterator it_nr;
  for(it_nr = m_map_v_records.begin(); it_nr != m_map_v_records.end(); ++it_nr){
    string vname = it_nr->first;
    NodeRecord nr = it_nr->second;

    map<string, string>::iterator it_varval;
    for(it_varval = m_map_var_val.begin(); it_varval != m_map_var_val.end();
	++it_varval){
      string var_name = it_varval->first;
      string val = it_varval->second;

      val = findReplace(val, "$[SELFVNAME]", m_host_community);
      val = findReplace(val, "$[SELFVX]", doubleToString(m_vx));
      val = findReplace(val, "$[SELFVY]", doubleToString(m_vy));
      val = findReplace(val, "$[SELFSPEED]", doubleToString(m_speed));
      val = findReplace(val, "$[SELFHEADING]", doubleToString(m_heading));

      val = findReplace(val, "$[TARGVNAME]", vname);
      val = findReplace(val, "$[TARGVX]", doubleToString(nr.getX()));
      val = findReplace(val, "$[TARGVY]", doubleToString(nr.getY()));
      val = findReplace(val, "$[TARGSPEED]", doubleToString(nr.getSpeed()));
      val = findReplace(val, "$[TARGHEADING]", doubleToString(nr.getHeading()));

      double range = hypot(m_vx-nr.getX(),m_vy-nr.getY());
      val = findReplace(val, "$[RANGE]", doubleToString(range));
      val = findReplace(val, "$[TIME]", doubleToString(m_dbtime));

      Notify(var_name, val);
    }
  }
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool RangeEvent::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());
  else {
    STRING_LIST::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string orig  = *p;
      string line  = *p;
      string param = toupper(biteStringX(line, '='));
      string value = line;

      bool handled = false;
      if(param == "MIN_RANGE")
        handled = handleConfigMinRange(value);
      else if(param == "MAX_RANGE")
        handled = handleConfigMinRange(value, false);
      else if(param == "EVENT_VAR")
        handled = handleConfigEventVar(value);
      else if(param == "IGNORE_GROUP")
        handled = handleConfigGroupVar(value);

      if(!handled)
        reportUnhandledConfigWarning(orig);
    }
  }

  registerVariables();
  return(true);
}

bool RangeEvent::handleConfigMinRange(string str, bool min)
{
  if (min)
    m_min_range = atof(str.c_str());
  else
    m_max_range = atof(str.c_str());

  return(true);
}

bool RangeEvent::handleConfigEventVar(const string& str)
{
  if((str == "") || (!strContains(str,'=')))
    return(false);

  string val = str;
  string var = biteStringX(val,'=');

  m_map_var_val[var] = val;

  return(true);
}

bool RangeEvent::handleConfigGroupVar(const string& str)
{
  if(str == "")
    return(false);

  m_ignored_group = str;
  return(true);
}

#if 0 // Keep this as an example for callbacks
//------------------------------------------------------------
// Procedure: onMessageFoo() callback

bool RangeEvent:onMessageFoo(CMOOSMsg& foo)
{
  // do something with foo

  // update outgoing message (FOO_OUT in this case)
  // SetMOOSVar("foo_msg", new_value, m_curr_time);
}
#endif

//------------------------------------------------------------
// Procedure: onNodeReport() callback

bool RangeEvent::onNodeReport(const string& node_report)
{
  NodeRecord new_node_record = string2NodeRecord(node_report);

  string vname = new_node_record.getName();
  if(m_host_community == vname) // Sanity check
    return(true);

  // if vehicle belongs to the group that needs to be ignored
  string vgroup = new_node_record.getGroup();
  if(m_ignored_group == vgroup)
    return(true);

  double vx = new_node_record.getX();
  double vy = new_node_record.getY();

  double range = hypot(m_vx-vx, m_vy-vy);

  // if the Vehicle is within specified range, record its info for later processing
  if( (range <= m_max_range) && (range >= m_min_range)){
    m_map_v_records[vname] = new_node_record;
  } else { // the vehicle is out of range => remove it from the map
    if(m_map_v_records.count(vname))
      m_map_v_records.erase(vname);
    //map<string, NodeRecord>::iterator p = m_map_v_records.find(vname);
    //if (p != m_map_v_records.end())
    //  m_map_v_records.erase(p);

  }

  return(true);
}

//------------------------------------------------------------
// Procedure: onNodeReportLocal() callback

bool RangeEvent::onNodeReportLocal(const string& node_report)
{
  NodeRecord new_node_record = string2NodeRecord(node_report);

  string vname = new_node_record.getName();
  if(m_host_community != vname) // Sanity check
    return(false);

  m_vx = new_node_record.getX();
  m_vy = new_node_record.getY();
  m_speed = new_node_record.getSpeed();
  m_heading = new_node_record.getHeading();

  return(true);
}

//------------------------------------------------------------
// Procedure: buildReport()

bool RangeEvent::buildReport()
{
  m_msgs << "pRangeEvent Report\n";
  m_msgs << "============================================ \n";

  m_msgs << endl;
  m_msgs << "Configuration Parameters:" << endl;
  m_msgs << "\tMIN_RANGE = " << m_min_range << endl;
  m_msgs << "\tMAX_RANGE = " << m_max_range << endl;
  m_msgs << "\tRegistred variables to be published:" << endl;

  map<string, string>::iterator it_varval;
  for(it_varval = m_map_var_val.begin(); it_varval != m_map_var_val.end(); ++it_varval){
    string var_name = it_varval->first;
    string val = it_varval->second;

    m_msgs << "\t\t> " << var_name << " : ";
    m_msgs << val << endl;
  }

  m_msgs << endl;
  ACTable actab(5);
  actab << "Time | Vehicle | Range | POS_X | POS_Y";
  actab.addHeaderLines();
  map<string, NodeRecord>::iterator it_nr;
  for(it_nr = m_map_v_records.begin(); it_nr != m_map_v_records.end(); ++it_nr){
    actab << m_dbtime << it_nr->first;
    double vx = it_nr->second.getX();
    double vy = it_nr->second.getY();
    double range = hypot(m_vx-vx, m_vy-vy);
    actab << range;
    actab << vx << vy;
  }
  m_msgs << actab.getFormattedString();

  return(true);
}
