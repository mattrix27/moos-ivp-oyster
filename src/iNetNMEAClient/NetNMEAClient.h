/************************************************************/
/*    NAME:                                               */
/*    ORGN: MIT                                             */
/*    FILE: NetNMEAClient.h                                          */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#ifndef NetNMEAClient_HEADER
#define NetNMEAClient_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include <boost/asio.hpp>
#include <boost/thread.hpp>


class NetNMEAClient : public AppCastingMOOSApp
{
 public:
   NetNMEAClient();
   ~NetNMEAClient();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToClient();
   bool OnStartUp();
   bool connectToNMEAServer();
   void handle_read(const boost::system::error_code& error,size_t size);
   void startReceive();
   void writeMessage(std::string message);

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables
 std::string server;
 std::string port;
 std::string nmea_send_var;
 std::string nmea_recv_var;

 private: // State variables
 boost::asio::io_service io_service;
 boost::asio::ip::tcp::socket* socket;
 boost::asio::streambuf buffer; 
 //Background thread
 boost::thread runner;
 std::string nmea_received;
 std::string nmea_sent;
 int nmea_lines_received;
 bool commandReady;
};

#endif 
