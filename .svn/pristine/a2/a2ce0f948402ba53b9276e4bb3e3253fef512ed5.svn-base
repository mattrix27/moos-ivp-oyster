/*****************************************************************/
/*    NAME: Michael Benjamin and John Leonard                    */
/*    ORGN: NAVSEA Newport RI and MIT Cambridge MA               */
/*    FILE: AOF_SimpleWaypoint.h                                 */
/*    DATE: Feb 22th 2009                                        */
/*****************************************************************/
 
#ifndef AOF_SIMPLE_DEFEND_HEADER
#define AOF_SIMPLE_DEFEND_HEADER

#include "AOF.h"
#include "IvPDomain.h"

class AOF_SimpleDefend: public AOF {
 public:
  AOF_SimpleDefend(IvPDomain);
  ~AOF_SimpleDefend() {};

public: // virtuals defined
  double evalPoint(const std::vector<double>&) const; 
  bool   setParam(const std::string&, double);
  bool   initialize();

protected:
  // Initialization parameters
  double m_osx;   // Ownship x position at time Tm.
  double m_osy;   // Ownship y position at time Tm.
  double m_ptx;   // x component of next the waypoint.
  double m_pty;   // y component of next the waypoint.
  double m_desired_spd;

 // Initialization parameter set flags
  bool   m_osx_set;  
  bool   m_osy_set;  
  bool   m_ptx_set;  
  bool   m_pty_set;   
  bool   m_desired_spd_set;

  // Cached values for more efficient evalBox calls
  double m_angle_to_wpt;
  double m_min_speed;
  double m_max_speed;
};

#endif

