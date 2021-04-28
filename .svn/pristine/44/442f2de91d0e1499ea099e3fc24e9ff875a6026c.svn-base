/************************************************************/
/*    NAME: Mohamed Saad Ibn Seddik                         */
/*    ORGN: MIT                                             */
/*    FILE: ZoneEvent.h                                     */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef ZoneEvent_HEADER
#define ZoneEvent_HEADER

#include <vector>
#include <string>
#include <map>
#include <set>
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "NodeRecord.h"
#include "XYRangePulse.h"
#include "XYPolygon.h"

class ZoneEvent : public AppCastingMOOSApp
{
 public:
  ZoneEvent();
  ~ZoneEvent() {}

 protected:  // Standard MOOSApp functions to overload
  bool OnNewMail(MOOSMSG_LIST &NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();

 protected:  // Config utilities
  bool handleConfigZone(const std::string&);
  bool handleConfigViewZone(const std::string&, const std::string&);
  bool handleConfigPostVarZone(const std::string&, const std::string&);
  bool handleConfigColorZone(const std::string&, const std::string&);
  bool handleConfigGroupZone(const std::string&, const std::string&);
  bool handleConfigPolyZone(const std::string&, const std::string&);
  bool postZonesPoly();

 protected:
  bool onNodeReport(CMOOSMsg&);
  bool checkNodeInZone(const std::string&, NodeRecord&);

 protected:  // Standard AppCastingMOOSApp function to overload
  bool buildReport();

 protected:
  void registerVariables();

 protected:  // Configuration variables
  std::map<std::string, XYPolygon> m_zones;
  std::map<std::string, std::string> m_zones_group;
  std::map<std::string, bool> m_zones_view;
  std::map<std::string, std::vector<std::string> > m_zones_varval;

  std::map<std::string, NodeRecord> m_all_noderecords;

  CMOOSLock* p_events_w_lock;
  std::vector<std::string> m_events;

private:
  std::string tokStringParse(const std::string&, const std::string&, char, char);
};

#endif
