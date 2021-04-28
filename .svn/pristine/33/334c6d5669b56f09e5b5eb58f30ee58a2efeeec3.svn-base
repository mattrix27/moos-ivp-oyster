/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: DialogManager.h                                 */
/*    DATE: August 17th, 2015                               */
/*    UPDATED: Aug. 10 2016                                 */
/************************************************************/

#ifndef DialogManager_3_0_HEADER
#define DialogManager_3_0_HEADER

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
  bool triggerVariablePosts();

 private: // Configuration variables
  int m_number_ack_attempts;
  std::map<std::string,std::string> m_nicknames;
  std::map<std::string,std::list<var_value> > m_actions;
  std::map<std::string,bool> m_just_publish;
  std::map<std::string,std::string> m_confirm_word;
  std::map<std::string,std::string> m_decline_word;

 private: // State variables
  std::string m_commanded_string;
  std::vector<std::string> m_conversation;
  enum type_name {
    WAIT_COMMAND,
    COMMAND_RECEIVED,
    WAIT_ACK,
    ACK_RECEIVED
  } m_state;

};

#endif 
