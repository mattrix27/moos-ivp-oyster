/*****************************************************************/
/*    NAME: M.Benjamin, H.Schmidt, J. Leonard                    */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: BHV_SimpleWaypoint.cpp                               */
/*    DATE: July 1st 2008  (For purposes of simple illustration) */
/*                                                               */
/* This program is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU General Public License   */
/* as published by the Free Software Foundation; either version  */
/* 2 of the License, or (at your option) any later version.      */
/*                                                               */
/* This program is distributed in the hope that it will be       */
/* useful, but WITHOUT ANY WARRANTY; without even the implied    */
/* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR       */
/* PURPOSE. See the GNU General Public License for more details. */
/*                                                               */
/* You should have received a copy of the GNU General Public     */
/* License along with this program; if not, write to the Free    */
/* Software Foundation, Inc., 59 Temple Place - Suite 330,       */
/* Boston, MA 02111-1307, USA.                                   */
/*****************************************************************/

#include <cstdlib>
#include <math.h>
#include "BHV_SimpleDefend.h"
#include "MBUtils.h"
#include "AngleUtils.h"
#include "BuildUtils.h"
#include "ZAIC_PEAK.h"
#include "OF_Coupler.h"
#include "OF_Reflector.h"
#include "AOF_SimpleDefend.h"
#include "NodeRecordUtils.h"

using namespace std;

//-----------------------------------------------------------
// Procedure: Constructor

BHV_SimpleDefend::BHV_SimpleDefend(IvPDomain gdomain) : 
  IvPBehavior(gdomain)
{
  IvPBehavior::setParam("name", "simple_defend");
  m_domain = subDomain(m_domain, "course,speed");

  // All distances are in meters, all speed in meters per second
  // Default values for configuration parameters 
  m_desired_speed  = 0; 
  m_arrival_radius = 10;
  m_ipf_type       = "zaic";

  // Default values for behavior state variables
  m_osx  = 0;
  m_osy  = 0;

  addInfoVars("NAV_X, NAV_Y");
  addInfoVars("NODE_REPORT");
  addInfoVars("NODE_REPORT_LOCAL");
}

//---------------------------------------------------------------
// Procedure: setParam - handle behavior configuration parameters

bool BHV_SimpleDefend::setParam(string param, string val) 
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  double double_val = atof(val.c_str());
  if((param == "ptx")  && (isNumber(val))) {
    m_nextpt.set_vx(double_val);
    return(true);
  }
  else if((param == "pty") && (isNumber(val))) {
    m_nextpt.set_vy(double_val);
    return(true);
  }
  else if((param == "ay") && (isNumber(val))) {
    m_target_pt.set_vy(double_val);
    return(true);
  }
  else if((param == "ax") && (isNumber(val))) {
    m_target_pt.set_vx(double_val);
    return(true);
  }
  else if((param == "speed") && (double_val > 0) && (isNumber(val))) {
    m_desired_speed = double_val;
    return(true);
  }
  else if((param == "radius") && (double_val > 0) && (isNumber(val))) {
    m_arrival_radius = double_val;
    return(true);
  }
  else if((param == "max_defend_radius") && (double_val > 0) && (isNumber(val))) {
    m_max_defend_radius = double_val;
    return(true);
 }
  else if((param == "defend_ratio") && (double_val > 0) && (isNumber(val))) {
    ratio = double_val;
    return(true);
 }
  else if(param == "ipf_type") {
    val = tolower(val);    
    if((val == "zaic") || (val == "reflector")) {
      m_ipf_type = val;
      return(true);
    }
  }
  return(false);
}

//-----------------------------------------------------------
// Procedure: onIdleState

void BHV_SimpleDefend::onIdleState() 
{
  postViewPoint(false);
}

//-----------------------------------------------------------
// Procedure: postViewPoint

void BHV_SimpleDefend::postViewPoint(bool viewable) 
{
  m_nextpt.set_label(m_us_name + "'s next waypoint");
  
  string point_spec;
  if(viewable)
    point_spec = m_nextpt.get_spec("active=true");
  else
    point_spec = m_nextpt.get_spec("active=false");
  postMessage("VIEW_POINT", point_spec);
}

//-----------------------------------------------------------
// Procedure: onRunState

IvPFunction *BHV_SimpleDefend::onRunState() 
{
  // Part 1: Get vehicle position from InfoBuffer and post a 
  // warning if problem is encountered
  bool ok1, ok2;
  m_osx = getBufferDoubleVal("NAV_X", ok1);
  m_osy = getBufferDoubleVal("NAV_Y", ok2);
  if(!ok1 || !ok2) {
    postWMessage("No ownship X/Y info in info_buffer.");
    return(0);
  }

  //Part : Let's check our own NODE_REPORT local to get our own 
  //Community/Group name which will make sure we only
  //reason about other team's players
  bool ok3;
  std::string own_node_record = getBufferStringVal("NODE_REPORT_LOCAL",ok3);

  if(!ok3){

    NodeRecord new_node_record = string2NodeRecord(own_node_record);
    
    string vname = new_node_record.getName();
    string vgroup = new_node_record.getGroup();
    if(vgroup == "") {//no group name
    }
    else {
      m_own_group = vgroup;
    }


  }

  //Part 2: Let's check all node_reports to find the closest contact
  //will this be a list of NODE_REPORTS?
  //bool ok3

  //Part 2: We want to determine the vehicle's goto point
  //For this we need information about the point we are protecting
  //and the target vehicle's x,y
  double ratioX = ( m_nextpt.x() - m_target_pt.x())*ratio;
  double ratioY = (  m_nextpt.y() - m_target_pt.y())*ratio;
  double ratioDist = hypot(ratioX,ratioY);
  if(ratioDist > m_max_defend_radius) {
    //vehicle will exceed our max radius from defending point
    //so keep it within that radius
    double angleTargetToNext = atan2( m_nextpt.x() - m_target_pt.x(),  m_nextpt.y() - m_target_pt.y());
    m_goToPt.set_vx( m_max_defend_radius *cos(angleTargetToNext));
    m_goToPt.set_vy( m_max_defend_radius *sin(angleTargetToNext));
  }
  else {
    m_goToPt.set_vx( ratioX + m_nextpt.x());
    m_goToPt.set_vy( ratioY + m_nextpt.y());
  }

  // Part 2: Determine if the vehicle has reached the destination 
  // point and if so, declare completion.
  //#ifdef WIN32
  //double dist = _hypot((m_nextpt.x()-m_osx), (m_nextpt.y()-m_osy));
  //#else
  //double dist = hypot((m_nextpt.x()-m_osx), (m_nextpt.y()-m_osy));
  //#endif
  //if(dist <= m_arrival_radius) {
  // setComplete();
  // postViewPoint(false);
  // return(0);
  //}

  // Part 3: Post the waypoint as a string for consumption by 
  // a viewer application.
  postViewPoint(true);

  // Part 4: Build the IvP function with either the ZAIC tool 
  // or the Reflector tool.
  IvPFunction *ipf = 0;
  if(m_ipf_type == "zaic")
    ipf = buildFunctionWithZAIC();
  else
    ipf = buildFunctionWithReflector();
  if(ipf == 0) 
    postWMessage("Problem Creating the IvP Function");

  if(ipf)
    ipf->setPWT(m_priority_wt);
  
  return(ipf);
}

//-----------------------------------------------------------
// Procedure: buildFunctionWithZAIC

IvPFunction *BHV_SimpleDefend::buildFunctionWithZAIC() 
{
  ZAIC_PEAK spd_zaic(m_domain, "speed");
  spd_zaic.setSummit(m_desired_speed);
  spd_zaic.setPeakWidth(0.5);
  spd_zaic.setBaseWidth(1.0);
  spd_zaic.setSummitDelta(0.8);  
  if(spd_zaic.stateOK() == false) {
    string warnings = "Speed ZAIC problems " + spd_zaic.getWarnings();
    postWMessage(warnings);
    return(0);
  }
  
  double rel_ang_to_wpt = relAng(m_osx, m_osy, m_goToPt.x(), m_goToPt.y());
  ZAIC_PEAK crs_zaic(m_domain, "course");
  crs_zaic.setSummit(rel_ang_to_wpt);
  crs_zaic.setPeakWidth(0);
  crs_zaic.setBaseWidth(180.0);
  crs_zaic.setSummitDelta(0);  
  crs_zaic.setValueWrap(true);
  if(crs_zaic.stateOK() == false) {
    string warnings = "Course ZAIC problems " + crs_zaic.getWarnings();
    postWMessage(warnings);
    return(0);
  }

  IvPFunction *spd_ipf = spd_zaic.extractIvPFunction();
  IvPFunction *crs_ipf = crs_zaic.extractIvPFunction();

  OF_Coupler coupler;
  IvPFunction *ivp_function = coupler.couple(crs_ipf, spd_ipf, 50, 50);

  return(ivp_function);
}

//-----------------------------------------------------------
// Procedure: buildFunctionWithReflector

IvPFunction *BHV_SimpleDefend::buildFunctionWithReflector() 
{
  IvPFunction *ivp_function;

  bool ok = true;
  AOF_SimpleDefend aof_wpt(m_domain);
  ok = ok && aof_wpt.setParam("desired_speed", m_desired_speed);
  ok = ok && aof_wpt.setParam("osx", m_osx);
  ok = ok && aof_wpt.setParam("osy", m_osy);
  ok = ok && aof_wpt.setParam("ptx", m_nextpt.x());
  ok = ok && aof_wpt.setParam("pty", m_nextpt.y());
  ok = ok && aof_wpt.initialize();
  if(ok) {
    OF_Reflector reflector(&aof_wpt);
    reflector.create(600, 500);
    ivp_function = reflector.extractIvPFunction();
  }

  return(ivp_function);
}
