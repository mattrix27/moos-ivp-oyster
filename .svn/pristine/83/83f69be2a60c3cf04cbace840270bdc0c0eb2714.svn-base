/************************************************************/
/*    NAME: Jonathan Schwartz                                              */
/*    ORGN: MIT                                             */
/*    FILE: BHV_Defense.h                                      */
/*    DATE:                                                 */
/************************************************************/

#ifndef Defense_HEADER
#define Defense_HEADER

#include <string>
#include "IvPBehavior.h"
#include "WaypointEngine.h"
#include "XYPolygon.h"

class BHV_Defense : public IvPBehavior {
public:
  BHV_Defense(IvPDomain);
  ~BHV_Defense() {};
  
  bool         setParam(std::string, std::string);
  void         onSetParamComplete();
  void         onCompleteState();
  void         onIdleState();
  void         onHelmStart();
  void         postConfigStatus();
  void         onRunToIdleState();
  void         onIdleToRunState();
  IvPFunction* onRunState();
  void getOppCoords(string);

protected: // Local Utility functions
  WaypointEngine m_waypoint_engine;
  IvPFunction* buildFunctionWithZAIC();

protected: // Configuration parameters

protected: // State variables
  double m_flagX;
  double m_flagY;
  double m_speed;
  double m_oppX;
  double m_oppY;
  double m_dist_from_flag;
  double m_osX;
  double m_osY;
  double m_destX;
  double m_destY;
  double m_attack_angle;
  string m_curr_node_report;
  XYSegList m_points;
  bool m_move;
  double m_angle;
};


#define IVP_EXPORT_FUNCTION

extern "C" {
  IVP_EXPORT_FUNCTION IvPBehavior * createBehavior(std::string name, IvPDomain domain) 
  {return new BHV_Defense(domain);}
}
#endif
