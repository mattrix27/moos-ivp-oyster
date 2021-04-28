/*****************************y*******************************/
/*    NAME: Jonathan Schwartz                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_Defense.cpp                                    */
/*    DATE:                                                 */
/************************************************************/

#ifdef _WIN32
#pragma warning(disable : 4786)
#pragma warning(disable : 4503)
#endif

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_Defense.h"
#include <stdlib.h>
#include <cmath>
#include <string>
#include <iostream>
#include "ZAIC_PEAK.h"
#include <sstream>
#include "OF_Coupler.h"
#include "XYPoint.h"

#define PI 3.14159265358979323846264338327

using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_Defense::BHV_Defense(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  //  IvPBehavior::setParam("name", "defaultname");

  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "course,speed");
  m_descriptor = "defend";
  
  m_flagX = 0;
  m_flagY = 0;
  m_speed = 2;
  m_dist_from_flag = 10;
  m_oppX  = 0;
  m_oppY  = 0;
  m_osX = 0;
  m_osY = 0;
  m_destX = 0;
  m_destY = 0;
  m_attack_angle = 0;
  m_curr_node_report = "";
  m_move = false;
  m_angle = 0;

// Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_X, NAV_Y, NODE_REPORT");
}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_Defense::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  // Get the numerical value of the param argument for convenience once
  double double_val = atof(val.c_str());

  if((param == "flag_x") && isNumber(val)) {
      m_flagX = double_val;
      return(true);
    }
  else if ((param == "flag_y") && isNumber(val)) {
      m_flagY = double_val;
      return(true);
    }
    else if((param == "speed") && isNumber(val)) {
      m_speed = double_val;
      return(true);
    }
    else if((param == "distance_from_flag") && isNumber(val)) {
      m_dist_from_flag = double_val;
      return true;
    }

  // If not handled above, then just return false;
  return(false);
}


//---------------------------------------------------------------
// Procedure: onSetParamComplete()
//   Purpose: Invoked once after all parameters have been handled.
//            Good place to ensure all required params have are set.
//            Or any inter-param relationships like a<b.

void BHV_Defense::onSetParamComplete()
{
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_Defense::onHelmStart()
{
}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_Defense::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_Defense::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_Defense::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_Defense::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_Defense::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: getOppCoords()
//   Purpose: Look at opposing node reports to get their position

void BHV_Defense::getOppCoords(string node)
{ 
  size_t pos = 0;

  string x = node.substr(node.find("X=", pos)+2, node.find(",Y=", pos)-(node.find("X=", pos)+2));
  const char *xChar = x.c_str();
  m_oppX = atof(xChar);
  
    if (!m_oppX)
    {
      postWMessage("BHV_DEFENSE ERROR: Couldn't get x coordinate from opposing node report.");
    }

    string y = node.substr(node.find("Y=", pos)+2, node.find(",SPD", pos)-(node.find("Y=")+2));
  const char *yChar = y.c_str();
  m_oppY = atof(yChar);

   if(!m_oppY)
    {
      postWMessage("BHV_DEFENSE ERROR: Couldn't get y coordinate from opposing node report.");
    }

   return;
}



//------------------------------------------------------------
//Procedure: onRunState()
//    Purpose: To calculate the X and Y values of where the robot should be if it is to be between its flag 
//             and the enemy robot (at a set distance from the flag)

IvPFunction* BHV_Defense::onRunState()
{
  bool check1, check2, check3;
  m_osX = getBufferDoubleVal("NAV_X", check1);
  m_osY = getBufferDoubleVal("NAV_Y", check2);
  
  m_curr_node_report = getBufferStringVal("NODE_REPORT", check3);
  getOppCoords(m_curr_node_report);

  if(!check1 || !check2) {
    postWMessage("BHV_DEFENSE ERROR: No X/Y value in info_buffer!");
    return 0;
  }
  else if(!check3){
    postWMessage("BHV_DEFENSE ERROR: Node_report not found in info_buffer!");
    return 0;
  }
  
  double deltX = m_oppX-m_flagX;
  double deltY = m_oppY-m_flagY;
  m_attack_angle = atan( abs(deltY) / abs(deltX) );

  //m_attack_angle increases counter clockwise, but resets to 0 every 180 degrees
  
  if (deltX*deltY < 0)
    m_attack_angle = PI - m_attack_angle;
  
  if(deltY>0){   
    m_destX = cos(m_attack_angle)*m_dist_from_flag + m_flagX;
    m_destY = sin(m_attack_angle)*m_dist_from_flag + m_flagY;
  }
  
  else{
    m_destX = m_flagX - cos(m_attack_angle)*m_dist_from_flag;
    m_destY = m_flagY - sin(m_attack_angle)*m_dist_from_flag;
  }
  
  double dx = m_destX-m_osX;
  double dy = m_destY-m_osY;

  double dx1 = m_oppX-m_flagX;
  double dy1 = m_oppY-m_flagY;
  
  m_angle = 90-atan(abs(dy)/abs(dx))*180/PI;
  
  
  //convert m_angle so that it the ipf function reads it properly
  //(starts at 0 on the positive y-axis and increases counter-clockwise)


  
  if (dx*dy<0)
    m_angle = 90-m_angle;

  if (dx>0 && dy<0)
    m_angle += 90;
  else if (dx<0 && dy<0)
    m_angle += 180;
  else if (dx<0 && dy>0)
    m_angle += 270;
  
 
      
  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.

  IvPFunction *ipf = 0;

  //determines if defending vehicle is close enough to were it should be
  //if it isn't, m_move is set to true which activates the ipf function

  if (hypot(dx, dy)>5)
    m_move=true;

  if (m_move)
  {
    ipf = buildFunctionWithZAIC();
    m_move=false;
  }
  //otherwise use just enough speed to allow it to turn to face the correct direction
  if(ipf)
    ipf->setPWT(m_priority_wt);

  return(ipf);
}

//---------------------------------------------------------------
// Procedure: buildFunctionWithZAIC()
//     Purpose: Builds and IvP function for the behavior

IvPFunction *BHV_Defense::buildFunctionWithZAIC()
{
  ZAIC_PEAK spd_zaic(m_domain, "speed");
  spd_zaic.setSummit(m_speed);
  spd_zaic.setBaseWidth(0.3);
  spd_zaic.setPeakWidth(0.0);
  spd_zaic.setSummitDelta(0.0);
  IvPFunction *spd_of = spd_zaic.extractIvPFunction();

  ZAIC_PEAK crs_zaic(m_domain, "course");
  crs_zaic.setSummit(m_angle);
  crs_zaic.setBaseWidth(180.0);
  crs_zaic.setValueWrap(true);
  IvPFunction *crs_of = crs_zaic.extractIvPFunction();

  OF_Coupler coupler;
  IvPFunction *ipf = coupler.couple(crs_of, spd_of);

  return(ipf);
}
