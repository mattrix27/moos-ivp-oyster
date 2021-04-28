/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: Authority.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef Authority_HEADER
#define Authority_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

class Authority : public AppCastingMOOSApp
{
 public:
   Authority();
   ~Authority();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();
  void handleAggressivePost(std::string value);

 private: // Configuration variables

 private: // State variables
  std::string m_internal_aggressive_state;
  bool m_authority_active;
};

#endif 
