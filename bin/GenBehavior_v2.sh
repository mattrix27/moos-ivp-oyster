#!/bin/bash

if [ -z "$1" ] ; then
    echo "GenBehavior: usage: $0 [behavior-name] [your-name]"
    exit 0
fi

if [ -z "$2" ] ; then
    echo "GenBehavior: usage: $0 [behavior-name] [your-name]"
    exit 0
fi

DATE=`date +%Y/%m/%d`

cat >> BHV_${1}.h <<EOF
/************************************************************/
/*    NAME: $2                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_${1}.h                                      */
/*    DATE: $DATE                                      */
/************************************************************/

#ifndef ${1}_HEADER
#define ${1}_HEADER

#include <string>
#include "IvPBehavior.h"

class BHV_${1} : public IvPBehavior {
public:
  BHV_${1}(IvPDomain);
  ~BHV_${1}() {};

  bool         setParam(std::string, std::string);
  void         onSetParamComplete();
  void         onCompleteState();
  void         onIdleState();
  void         onHelmStart();
  void         postConfigStatus();
  void         onRunToIdleState();
  void         onIdleToRunState();
  IvPFunction* onRunState();

protected: // Local Utility functions

protected: // Configuration parameters

protected: // State variables
};

#define IVP_EXPORT_FUNCTION

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain)
  {return new BHV_${1}(domain);}
}
#endif
EOF


cat >> BHV_${1}.cpp <<EOF
/************************************************************/
/*    NAME: $2                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_${1}.cpp                                    */
/*    DATE: $DATE                                      */
/************************************************************/

#include <iterator>
#include <cstdlib>
#include "MBUtils.h"
#include "BuildUtils.h"
#include "BHV_${1}.h"

using namespace std;

//---------------------------------------------------------------
// Constructor

BHV_${1}::BHV_${1}(IvPDomain domain) :
  IvPBehavior(domain)
{
  // Provide a default behavior name
  IvPBehavior::setParam("name", "defaultname");

  // Declare the behavior decision space
  m_domain = subDomain(m_domain, "course,speed");

  // Add any variables this behavior needs to subscribe for
  addInfoVars("NAV_X, NAV_Y");
}

//---------------------------------------------------------------
// Procedure: setParam()

bool BHV_${1}::setParam(string param, string val)
{
  // Convert the parameter to lower case for more general matching
  param = tolower(param);

  // Get the numerical value of the param argument for convenience once
  double double_val = atof(val.c_str());

  if((param == "foo") && isNumber(val)) {
    // Set local member variables here
    return(true);
  }
  else if (param == "bar") {
    // return(setBooleanOnString(m_my_bool, val));
  }

  // If not handled above, then just return false;
  return(false);
}

//---------------------------------------------------------------
// Procedure: onSetParamComplete()
//   Purpose: Invoked once after all parameters have been handled.
//            Good place to ensure all required params have are set.
//            Or any inter-param relationships like a<b.

void BHV_${1}::onSetParamComplete()
{
}

//---------------------------------------------------------------
// Procedure: onHelmStart()
//   Purpose: Invoked once upon helm start, even if this behavior
//            is a template and not spawned at startup

void BHV_${1}::onHelmStart()
{
}

//---------------------------------------------------------------
// Procedure: onIdleState()
//   Purpose: Invoked on each helm iteration if conditions not met.

void BHV_${1}::onIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onCompleteState()

void BHV_${1}::onCompleteState()
{
}

//---------------------------------------------------------------
// Procedure: postConfigStatus()
//   Purpose: Invoked each time a param is dynamically changed

void BHV_${1}::postConfigStatus()
{
}

//---------------------------------------------------------------
// Procedure: onIdleToRunState()
//   Purpose: Invoked once upon each transition from idle to run state

void BHV_${1}::onIdleToRunState()
{
}

//---------------------------------------------------------------
// Procedure: onRunToIdleState()
//   Purpose: Invoked once upon each transition from run to idle state

void BHV_${1}::onRunToIdleState()
{
}

//---------------------------------------------------------------
// Procedure: onRunState()
//   Purpose: Invoked each iteration when run conditions have been met.

IvPFunction* BHV_${1}::onRunState()
{
  // Part 1: Build the IvP function
  IvPFunction *ipf = 0;



  // Part N: Prior to returning the IvP function, apply the priority wt
  // Actual weight applied may be some value different than the configured
  // m_priority_wt, depending on the behavior author's insite.
  if(ipf)
    ipf->setPWT(m_priority_wt);

  return(ipf);
}

EOF


echo "BHV_${1} generated. Don't forget to to update your CMakeLists.txt file"
