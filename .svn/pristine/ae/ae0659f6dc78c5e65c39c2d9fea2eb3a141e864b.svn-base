/************************************************************/
/*    NAME: Carter Fendley                                  */
/*    ORGN: MIT                                             */
/*    FILE: AttackCommander.h                               */
/*    DATE: August 10th, 2016                               */
/************************************************************/

#ifndef AttackCommander_HEADER
#define AttackCommander_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "XYSegList.h"
#include "XYFormatUtilsSegl.h"
#include "XYPoint.h"
#include "XYFormatUtilsPoint.h"
class AttackCommander : public AppCastingMOOSApp
{
 public:
   AttackCommander();
   ~AttackCommander() {};

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();
   
   XYPoint getCordsFromReport(std::string report);
   double distance(double x1, double y1, double x2, double y2);
   double distance(XYPoint point1, XYPoint point2);
   double distance(std::string report1, std::string report2);

 private: // Configuration variables
   std::string m_vteam;
   std::string m_vname;
   
   std::string m_path_update_var;

   XYSegList m_red_zone_bounds;
   XYSegList m_blue_zone_bounds;
   
   XYPoint m_red_flag;
   XYPoint m_blue_flag;

   XYSegList m_waypt_line;

   double m_vdist_thresh;

 private: // State variables
   std::map<std::string, std::string> m_vreports;
   
   int m_reports_recived;
   std::string m_last_path;
};

#endif 
