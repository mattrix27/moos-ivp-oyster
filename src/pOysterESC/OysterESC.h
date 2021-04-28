/************************************************************/
/*    NAME: Matt Tung                                              */
/*    ORGN: MIT                                             */
/*    FILE: OysterESC.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef OysterESC_HEADER
#define OysterESC_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/asio/signal_set.hpp>

class OysterESC : public AppCastingMOOSApp
{
 public:
   OysterESC();
   ~OysterESC();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void RegisterVariables();
   bool connect(const std::string& port_name, int baud);
   bool send();

 private: // Configuration variables

  std::string serialPortName;
  int baudRate;
  std::string m_inputName;

  int m_base;
  int m_range;

  // REF: https://github.com/labust/labust-ros-pkg/wiki/Create-a-Serial-Port-application
  //Boost.Asio I/O service required for asynchronous 
  //operation
  boost::asio::io_service io;
  //Serial port accessor class
  boost::asio::serial_port port;
  //Background thread
  boost::thread runner;
  //Buffer in which to read the serial data
  boost::asio::streambuf buffer;
  // Construct a signal set registered for process termination
  //boost::asio::signal_set signals(io, SIGINT); 

 private: // State variables

   double m_time;

   double m_prev_left;
   double m_prev_right;
   double m_curr_left;
   double m_curr_right;

   std::string m_message;

};

#endif 
