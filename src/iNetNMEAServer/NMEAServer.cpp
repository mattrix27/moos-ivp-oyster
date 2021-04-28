#include "NMEAServer.h"
#include <boost/bind.hpp>

using namespace std;
using boost::asio::ip::tcp;

NMEAServer::NMEAServer(boost::asio::io_service& io_service_in, short port, CMOOSCommClient* comms, string var_name) 
    : m_io_service(io_service_in),
      m_acceptor(io_service_in, tcp::endpoint(tcp::v4(), port))
{
  m_comms = comms;
  m_var_name = var_name;
  startAccept();
  // make sure that the io_service does not return because it thinks it is out of work
  boost::asio::io_service::work work(m_io_service);
}

void NMEAServer::startAccept()
{
  try
  {
    NMEASession::sptr new_session(new NMEASession(m_io_service, m_comms, m_var_name));
    cout << "setting up new session\n";
    m_sessions.push_back(new_session);
    cout << "waiting for connection\n";
    m_acceptor.async_accept(new_session->getSocket(),
          boost::bind(&NMEAServer::handleAccept, this, new_session,
          boost::asio::placeholders::error));
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void NMEAServer::handleAccept(NMEASession::sptr new_session,
      const boost::system::error_code& error)
{

    cout << "#################accepting new session\n";
  try
  {
    if (!error)
    {
      new_session->startReceive();
      //new_session->writeMessage("$dsskf,sf,g,3,1*00\n");
    }
    else
    {
      new_session->setReadyToClose(true);
      throw boost::system::system_error(error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  startAccept();
}

// remove sessions that had errors and thus no longer make a connection to a valid client
void NMEAServer::cleanUp()
{
  for(list<NMEASession::sptr>::const_iterator it = m_sessions.begin(); it != m_sessions.end(); ++it)
  {
    if((*it)->readyToClose())
    {
      it = m_sessions.erase(it);
    }
  }
}

void NMEAServer::writeToAll(string message)
{
  cleanUp();
  for(list<NMEASession::sptr>::const_iterator it = m_sessions.begin(); it != m_sessions.end(); ++it)
  {
    if((*it)->isActive())
    {
      (*it)->writeMessage(message);
    }
  }
}

string NMEAServer::writeReport()
{
  // there will always be one session object waiting for a connection
  string report = "Clients Connected: " + to_string(m_sessions.size()-1) + "\n";
  int session_counter = 0;
  for(list<NMEASession::sptr>::const_iterator it = m_sessions.begin(); it != m_sessions.end(); ++it)
  {
    if((*it)->isActive())
    {
      report += "***********************************************************************\n";
      report += "SESSION " + to_string(session_counter) + "\n";
      report += (*it)->writeReport();
      session_counter++;
    }
  }
  report += "***********************************************************************\n";
  return report;
}

