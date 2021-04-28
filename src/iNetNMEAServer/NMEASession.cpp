#include "NMEASession.h"
#include <boost/bind.hpp>


using namespace std;
using boost::asio::ip::tcp;

NMEASession::NMEASession(boost::asio::io_service& io_service, CMOOSCommClient* comms, string var_name) : m_socket(io_service)
{
  m_comms = comms;
  m_var_name = var_name;
  m_ready_to_close = false;
  m_active = false;
}

tcp::socket& NMEASession::getSocket()
{
  return m_socket;
}

void NMEASession::startReceive()
{
  m_active = true;
  boost::asio::async_read_until(m_socket,m_buf,
        '\n', boost::bind(&NMEASession::handleRead, shared_from_this(),
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
}

void NMEASession::handleRead(const boost::system::error_code& error, size_t size)
{
  try
  {
    if (!error)
    {
      std::istream is(&m_buf);
      std::string data(size,'\0');
      is.read(&data[0],size);

      cout << "RECEIVED: " << data << endl;
      m_comms->Notify(m_var_name, data);
      m_nmea_received = data;
      startReceive();
    }
    else
    {
      m_ready_to_close = true;
      throw boost::system::system_error(error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void NMEASession::writeMessage(string message)
{
  cout << "SENDING: " << message << endl;
  if(message.back() != '\n')
  {
    message += '\n';
  }
  m_nmea_sent = message;
  boost::system::error_code error;
  boost::asio::async_write(m_socket, boost::asio::buffer(message), boost::bind(&NMEASession::handleWrite, this,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
  
}

void NMEASession::handleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
  try
  {
    if(error)
    {
      m_ready_to_close = true;
      throw boost::system::system_error(error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  //startReceive();
}

bool NMEASession::readyToClose()
{
  return m_ready_to_close;
}

void NMEASession::setReadyToClose(bool new_value)
{
  m_ready_to_close = new_value;
}

bool NMEASession::isActive()
{
  return m_active;
}

string NMEASession::writeReport()
{
  string report = "Received: " + m_nmea_received + "\n";
  report += "Sent: " + m_nmea_sent + "\n";
  if(m_ready_to_close)
  {
    report += "READY TO CLOSE\n";
  }
  return report;

}


