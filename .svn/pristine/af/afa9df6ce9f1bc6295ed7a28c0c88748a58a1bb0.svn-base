/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: DialogManager.h                                 */
/*    DATE: August 17th, 2015                               */
/************************************************************/

#ifndef DialogManager_HEADER
#define DialogManager_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <string>
#include <map>
#include <vector>
#include <list>


struct var_value {
  std::string var_name;
  std::string value;
};


class DialogManager : public AppCastingMOOSApp
{
 public:
  DialogManager();
  ~DialogManager() {};

 protected: // Standard MOOSApp functions to overload  
  bool OnNewMail(MOOSMSG_LIST &NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
  bool buildReport();

 protected:
  void registerVariables();
  void triggerCommandSequence(std::string sval);
  void triggerAckSequence(std::string sval);
  bool handleNickNameAssignments(std::string line);
  bool handleActionAssignments(std::string line);

 private: // Configuration variables
  std::map<std::string,std::string> m_nicknames;
  std::map<std::string,std::list<var_value> > m_actions;

 private: // State variables
  std::string m_commanded_string;
  enum type_name {
    WAIT_COMMAND,
    COMMAND_RECEIVED,
    WAIT_ACK,
    ACK_RECEIVED
  } m_state;

};

#endif 
