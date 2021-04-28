/************************************************************/
/*    NAME: Caileigh Fitzgerald                                              */
/*    ORGN: MIT                                             */
/*    FILE: LEDInfoBar.h                                          */
/*    DATE: May 5th 2018                                                  */
/************************************************************/

#ifndef LEDInfoBar_HEADER
#define LEDInfoBar_HEADER

#include "MBUtils.h"
#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "SerialComms.h"
#include "iLEDInfoBar_enums.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <sstream>

class LEDInfoBar : public AppCastingMOOSApp
{
 public:
  LEDInfoBar();
  virtual ~LEDInfoBar();

  bool OnNewMail(MOOSMSG_LIST &NewMail);
  bool Iterate();
  bool OnConnectToServer();
  bool OnStartUp();
  void RegisterVariables();
  int  toEnum(std::string state);
  std::string toString(int i);
  std::string toString(int type, int state);

protected:
    // relevant to comms with arduino
  bool serialSetup();
  bool buildReport();

  int           m_baudrate;
  bool          m_valid_serial_connection;
  std::string   m_serial_port;
  SerialComms*  m_serial;

  std::string   m_team_color;
  int *m_icons; // keeps track of the state of each LED

  std::string   m_tagged_var;
  std::string   m_out_of_bounds_var;
  std::string   m_have_flag_var;
  std::string   m_in_tag_range_var;
  std::string   m_flag_zone_var;

};

#endif 
