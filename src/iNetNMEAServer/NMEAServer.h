#include <string>
#include <list>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "MOOS/libMOOS/Comms/MOOSCommClient.h"
#include "NMEASession.h"

#ifndef NMEA_SERVER
#define NMEA_SERVER

class NMEAServer 
{

public:
  NMEAServer(boost::asio::io_service& io_service_in, short port, CMOOSCommClient* comms, std::string var_name);
  void cleanUp();
  void writeToAll(std::string message);
  std::string writeReport();

private:

  void startAccept();
  void handleAccept(NMEASession::sptr new_session, const boost::system::error_code& error);

  boost::asio::io_service& m_io_service;
  boost::asio::ip::tcp::acceptor m_acceptor;
  CMOOSCommClient* m_comms;
  std::string m_var_name;
  std::list<NMEASession::sptr> m_sessions;
};

#endif
