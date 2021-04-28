/************************************************************/
/*    NAME: Arjun Gupta                                              */
/*    ORGN: MIT                                             */
/*    FILE: NodeReportParse.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef NodeReportParse_HEADER
#define NodeReportParse_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class NodeReportParse : public AppCastingMOOSApp
{
 public:
   NodeReportParse();
   ~NodeReportParse();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();
   void ProcessNodeReport(std::string report);

 private: // Configuration variables

 private: // State variables
};

#endif 
