/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: ZoneTrackOpponents.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef ZoneTrackOpponents_HEADER
#define ZoneTrackOpponents_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "MBUtils.h"
#include "NodeRecord.h"

class ZoneTrackOpponents : public AppCastingMOOSApp
{
 public:
   ZoneTrackOpponents();
   ~ZoneTrackOpponents();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();
  bool handleOpForAssignment(std::string orig);
  bool handleZoneAssignment(std::string orig);
  bool handleHighValuePoint(std::string value);
  void handleMailNodeReport(std::string report);

 private: // Configuration variables
  std::string m_ownship;
  std::string m_op_for;
  double m_min_x;
  double m_min_y;
  double m_max_x;
  double m_max_y;
  std::string m_in_zone;
  bool m_high_value_point_set;
  double m_high_value_point_x;
  double m_high_value_point_y;

 private: // State variables
  std::map<std::string, NodeRecord> m_map_node_records;
  std::map<std::string, double  > m_map_intruders_x;
  std::map<std::string, double  > m_map_intruders_y;
  std::map<std::string, std::string> m_map_intruders_name;
};

#endif 
