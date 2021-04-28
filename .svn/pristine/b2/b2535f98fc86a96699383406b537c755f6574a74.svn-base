/************************************************************/
/*    NAME: Mohamed Saad Ibn Seddik                                              */
/*    ORGN: MIT                                    */
/*    FILE: RangeEvent.h                                          */
/*    DATE: 2016/03/15                                      */
/************************************************************/

#ifndef RangeEvent_HEADER
#define RangeEvent_HEADER

#include <vector>
#include <string>
#include <map>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "NodeRecord.h"

class RangeEvent : public AppCastingMOOSApp
{
 public:
  RangeEvent();
  ~RangeEvent() {};

 protected: // Standard MOOSApp functions to overload
  bool OnNewMail(MOOSMSG_LIST &NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload
  bool buildReport();

 protected:
  void registerVariables();

  bool handleConfigMinRange(std::string, bool = true);
  bool handleConfigEventVar(const std::string&);
  bool handleConfigGroupVar(const std::string&);
  void publishEvents();

 protected: // Mail Callbacks
#if 0 // Keep this as an example for callbacks
  bool onMessageFoo(CMOOSMsg&);
#endif
  bool onNodeReport(const std::string&);
  bool onNodeReportLocal(const std::string&);

 private: // Configuration variables
  double m_min_range, m_max_range;
  std::string m_ignored_group;

 private: // State variables
  double m_vx, m_vy, m_speed, m_heading;
  double m_dbtime;

  std::map<std::string, std::string> m_map_var_val;
  std::map<std::string, NodeRecord> m_map_v_records;
};

#endif
