/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: NetNMEAServer.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef NetNMEAServer_HEADER
#define NetNMEAServer_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <vector>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "NMEAServer.h"

class NetNMEAServer : public AppCastingMOOSApp
{
 public:
   NetNMEAServer();
   ~NetNMEAServer();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables
   int port;
   boost::asio::io_service io_service;
   NMEAServer* server;
   std::string nmea_send_var;
   std::string nmea_recv_var;
   //Background thread
  boost::thread runner;


 private: // State variables
   std::string m_message;
};

#endif 
