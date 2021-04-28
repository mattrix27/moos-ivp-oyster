/************************************************************/
/*    NAME: Caileigh Fitzgerald                                              */
/*    ORGN: MIT                                             */
/*    FILE: LEDInterpreter.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef LEDInterpreter_HEADER
#define LEDInterpreter_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "iLEDInfoBar_enums.h"

class LEDInterpreter : public AppCastingMOOSApp
{
 public:
   LEDInterpreter();
   ~LEDInterpreter();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   bool buildReport();

 protected:
   void RegisterVariables();

 private: // Configuration variables
	std::string   m_tagged_var;
	std::string   m_out_of_bounds_var;
	std::string   m_have_flag_var;
	std::string   m_in_tag_range_var;
	std::string   m_flag_zone_var;

   bool tag_received;
   bool bounds_received;
   bool have_flag_received;
   bool tag_zone_received;
   bool flag_zone_received;

 private: // State variables
};

#endif 
