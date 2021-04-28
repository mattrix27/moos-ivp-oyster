#include <string>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "MOOS/libMOOS/Comms/MOOSCommClient.h"

#ifndef NMEA_SESSION
#define NMEA_SESSION

class NMEASession : public boost::enable_shared_from_this<NMEASession> 
{

public:
  typedef boost::shared_ptr<NMEASession> sptr;


  NMEASession(boost::asio::io_service& io_service, CMOOSCommClient* comms, std::string var_name);

  boost::asio::ip::tcp::socket& getSocket();

  void startReceive();

  void writeMessage(std::string message);

  void handleWrite(const boost::system::error_code& error, std::size_t bytes_transferred);

  bool readyToClose();

  bool isActive();

  void setReadyToClose(bool new_value);

  std::string writeReport();

private:

  void handleRead(const boost::system::error_code& error, size_t size);

  boost::asio::ip::tcp::socket m_socket;
  boost::asio::streambuf m_buf;

  CMOOSCommClient* m_comms;
  std::string m_var_name;
  bool m_ready_to_close;
  bool m_active;
  std::string m_nmea_received;
  std::string m_nmea_sent;
};

#endif