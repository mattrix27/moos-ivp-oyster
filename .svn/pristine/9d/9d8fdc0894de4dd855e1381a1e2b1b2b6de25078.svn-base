/************************************************************/
/*    NAME: Mohamed Saad Ibn Seddik                         */
/*    ORGN: MIT                                             */
/*    FILE: ZoneEvent.cpp                                   */
/*    DATE:                                                 */
/************************************************************/

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "ZoneEvent.h"
#include "XYFormatUtilsPoly.h"
#include "NodeRecordUtils.h"
#include "ColorParse.h"

using namespace std;

//---------------------------------------------------------
// Constructor

ZoneEvent::ZoneEvent()
{
  p_events_w_lock = new CMOOSLock();
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool ZoneEvent::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  return UpdateMOOSVariables(NewMail);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool ZoneEvent::OnConnectToServer()
{
  registerVariables();

  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void ZoneEvent::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();

  Register("NODE_REPORT", 0);
  Register("NODE_REPORT_LOCAL", 0);
  AddMOOSVariable("dbtime", "DB_UPTIME", "NaN", 0);

  RegisterMOOSVariables();
}

bool ZoneEvent::postZonesPoly()
{
  map<string, XYPolygon>::iterator p;
  for (p = m_zones.begin(); p != m_zones.end(); ++p){
    string var_name = p->first;
    XYPolygon poly = p->second;

    string spec = poly.get_spec();
    Notify("VIEW_POLYGON", spec);
  }
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool ZoneEvent::Iterate()
{
  AppCastingMOOSApp::Iterate();

  PublishFreshMOOSVariables();

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool ZoneEvent::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams)){
    reportConfigWarning("No config block found for " + GetAppName());
  } else {
    STRING_LIST::iterator p;

    for (p=sParams.begin(); p != sParams.end(); p++) {
      string orig  = *p;
      string line  = *p;
      string param = tolower(biteStringX(line, '='));
      string value = line;
      bool handled = false;

      if (param == "zone_info")
        handled = handleConfigZone(value);
      if (!handled)
        reportUnhandledConfigWarning(orig);
    }
  }

  if(m_zones_group.size() == 0){
    reportConfigWarning("No group was set for the zones! Going down...");
    return(false);
  }

  AddActiveQueue("node_reports", this, &ZoneEvent::onNodeReport);
  AddMessageRouteToActiveQueue("node_reports", "NODE_REPORT_LOCAL");
  AddMessageRouteToActiveQueue("node_reports", "NODE_REPORT");

  postZonesPoly();

  registerVariables();

  return(true);
}

bool ZoneEvent::handleConfigZone(const string& str)
{
  string name = tokStringParse(str, "name", '#', '=');
  if (name == ""){
    reportConfigWarning("\"zone_info\" declared w/o name!");
    return(false);
  }

  // creation of inputs in different maps
  m_zones[name];
  m_zones_view[name]=true; // default value
  m_zones_varval[name];

  string pts = tokStringParse(str, "pts", '#', '=');
  if (pts != "")
    if (!handleConfigPolyZone(name, "pts="+pts)) {
      reportConfigWarning("failed to read \"pts\"");
      return(false);
    }

  string poly = tokStringParse(str, "polygon", '#', '=');
  if (poly != "")
    if (!handleConfigPolyZone(name, poly)) {
      reportConfigWarning("failed to read \"polygon\"");
      return(false);
    }

  string varval = tokStringParse(str, "post_var", '#', '=');
  if (varval != "")
    if (!handleConfigPostVarZone(name, varval)) {
      reportConfigWarning("failed to read \"post_var\"");
      return(false);
    }

  string view = tokStringParse(str, "viewable", '#', '=');
  if (view != "")
    if (!handleConfigViewZone(name, view)) {
      reportConfigWarning("failed to read \"viewable\"");
      return(false);
    }

  string color = tokStringParse(str, "color", '#', '=');
  if (color != "")
    if (!handleConfigColorZone(name, color)) {
      reportConfigWarning("failed to read \"color\"");
      return(false);
    }

  string group = tokStringParse(str, "group", '#', '=');
  if (group != "")
    if (!handleConfigGroupZone(name, group)) {
      reportConfigWarning("failed to read \"group\"");
      return(false);
    }


  return(true);
}

string ZoneEvent::tokStringParse(const string& str, const string& left,
                                  char gsep, char lsep)
{
  vector<string> svector1 = parseStringQ(str, gsep);
  for(vector<string>::size_type i=0; i<svector1.size(); i++) {
    vector<string> svector2 = parseString(svector1[i], lsep);
    if(svector2.size() < 2)
      return("");
    svector2[0] = stripBlankEnds(svector2[0]);
    if(svector2[0] == left){
      vector<string> subvector2(svector2.begin()+1,svector2.end());
      string rstr = svectorToString(subvector2, '=');

      return(stripBlankEnds(rstr));
    }
  }
  return("");
}

bool ZoneEvent::handleConfigViewZone(const string& name, const string& str)
{
  string s = tolower(str);
  if(s=="false") {
    m_zones_view[name] = false;
    return(true);
  }
  else if (s=="true"){
    m_zones_view[name] = true;
    return(true);
  }

  return(false);
}

bool ZoneEvent::handleConfigPolyZone(const string& name, const string& str)
{
  m_zones[name] = string2Poly(str);
  if(m_zones[name].size() == 0){
    reportUnhandledConfigWarning("Bad polygon: " + str);
    return(false);
  }
  m_zones[name].set_edge_size(1);
  m_zones[name].set_vertex_size(1);
  m_zones[name].set_transparency(0.5);

  // m_zones[name].set_color("vertex", "orange"); // default
  // m_zones[name].set_color("edge", "orange"); // default
  // m_zones[name].set_color("fill", "orange"); // default
  m_zones[name].set_label("uFldZoneEvent_" + name);

  return(true);
}

bool ZoneEvent::handleConfigColorZone(const string& name, const string& color)
{
  reportConfigWarning("Setting \"color\" is still experimental and might not work all time.");

  m_zones[name].set_color("vertex", color);
  m_zones[name].set_color("edge", color);
  m_zones[name].set_color("fill", color);

  return(true);
}

bool ZoneEvent::handleConfigGroupZone(const string& name, const string& group)
{
  if (group == "")
    return(false);

  m_zones_group[name] = group;

  return(true);
}

bool ZoneEvent::handleConfigPostVarZone(const string& name, const string& varval)
{
  if (varval == "")
    return(false);

  m_zones_varval[name].push_back(varval);

  return(true);
}

bool ZoneEvent::onNodeReport(CMOOSMsg& node_report_msg)
{
  NodeRecord new_node_record = string2NodeRecord(node_report_msg.GetString());

  string vname = new_node_record.getName();
  string vgroup = new_node_record.getGroup();
  if(vgroup == "") {
    string msg = "Node report for " + vname + " w/ no group.";
    p_events_w_lock->Lock();
    m_events.push_back(msg);
    p_events_w_lock->UnLock();
    return(false);
  }

  map<string, string>::iterator p;
  for(p = m_zones_group.begin(); p != m_zones_group.end(); ++p){
    if(p->second == vgroup) {
      checkNodeInZone(p->first, new_node_record);
    }
  }

  return(true);
}

bool ZoneEvent::checkNodeInZone(const string& name, NodeRecord& node_record)
{
  double dbtime = GetMOOSVar("dbtime")->GetDoubleVal();

  string vname = node_record.getName();
  string vgroup = node_record.getGroup();
  double vx = node_record.getX();
  double vy = node_record.getY();

  if(!m_zones[name].contains(vx, vy)){
    //  delete element from map: erase needs a iterator returned by find
    map<string, NodeRecord>::iterator p = m_all_noderecords.find(vname);
    if (p != m_all_noderecords.end())
      m_all_noderecords.erase(p);
    return(false);
  }

  vector<string>::iterator p;
  for (p = m_zones_varval[name].begin(); p != m_zones_varval[name].end(); ++p){
    string varval = *p;

    varval = findReplace(varval, "$[VNAME]", vname);
    varval = findReplace(varval, "$[GROUP]", vgroup);
    varval = findReplace(varval, "$[TIME]", doubleToString(dbtime));
    varval = findReplace(varval, "$[VX]", doubleToString(vx));
    varval = findReplace(varval, "$[VY]", doubleToString(vy));

    string var = biteStringX(varval, '=');

    Notify(var, varval);
  }

  m_all_noderecords[vname] = node_record;

  return(true);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool ZoneEvent::buildReport()
{
  double dbtime = GetMOOSVar("dbtime")->GetDoubleVal();

  m_msgs << endl;

  ACTable zones_varval(3);
  zones_varval << "Zone | Group | VAR=VAL";
  zones_varval.addHeaderLines();
  map<string, XYPolygon>::iterator p;
  for (p = m_zones.begin(); p != m_zones.end(); ++p) {
    vector<string>::iterator itvarval;
    for (itvarval = m_zones_varval[p->first].begin();
          itvarval != m_zones_varval[p->first].end(); ++itvarval) {
      zones_varval << p->first << m_zones_group[p->first] << *itvarval;
    }
  }
  m_msgs << zones_varval.getFormattedString();

  m_msgs << endl;
  m_msgs << endl;

  ACTable actab(5);
  actab << "Time | Vehicle Name | Group | POS_X | POS_Y";
  actab.addHeaderLines();

  map<string, NodeRecord>::iterator pNR;
  for (pNR = m_all_noderecords.begin(); pNR != m_all_noderecords.end(); ++pNR){
    actab << dbtime << pNR->second.getName() << pNR->second.getGroup();
    actab << pNR->second.getX() << pNR->second.getY();
  }
  m_msgs << actab.getFormattedString();

  m_msgs << endl;
  m_msgs << endl;
  m_msgs << endl;
  m_msgs << "Events:\n";
  m_msgs << "============================================\n";

  p_events_w_lock->Lock();
  vector<string>::iterator it;
  for (it = m_events.begin() ; it != m_events.end(); ++it)
    m_msgs << dbtime << ": " << *it << endl;
  m_events.clear();
  p_events_w_lock->UnLock();


  return(true);
}
