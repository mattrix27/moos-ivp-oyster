/************************************************************/
/*    NAME: Paul R.                                              */
/*    ORGN: AUV Lab MIT                                             */
/*    FILE: NetNMEAClient.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "NetNMEAClient.h"
#include <boost/bind.hpp>


using namespace std;


//---------------------------------------------------------
// Constructor

NetNMEAClient::NetNMEAClient()
{
  // reasonable defaults
  server = "localhost";
  port = "2000";
  nmea_send_var = "FRONT_SEAT_NMEA";
  nmea_recv_var = "NMEA_RECEIVED";
  commandReady = false;
}

//---------------------------------------------------------
// Destructor

NetNMEAClient::~NetNMEAClient()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool NetNMEAClient::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

    if(key == nmea_send_var) {
        string data = msg.GetString();
        nmea_sent = data;
        writeMessage(nmea_sent);
     }
     else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
 
    }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToClient

bool NetNMEAClient::OnConnectToClient()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool NetNMEAClient::Iterate()
{
  AppCastingMOOSApp::Iterate();
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool NetNMEAClient::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = toupper(biteStringX(line, '='));
    string value = line;

    bool handled = false;
    if(param == "FOO") {
      handled = true;
    }
    else if(param == "SERVER") {
      server = value;
      handled = true;
    }
    else if(param == "PORT") {
      port = value;
      handled = true;
    }
    else if(param == "NMEA_SEND") {
      nmea_send_var = value;
      handled = true;
    }
    else if(param == "NMEA_RECV") {
      nmea_recv_var = value;
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  bool result = connectToNMEAServer();
  if(!result)
  {
    return false;
  }
  //Start io-service in a background thread.
  //boost::bind binds the ioservice instance
  //with the method call
  runner = boost::thread(
      boost::bind(
          &boost::asio::io_service::run,
          &io_service));

  // make sure that the io_service does not return because it thinks it is out of work
  boost::asio::io_service::work work(io_service);
  startReceive();
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void NetNMEAClient::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(nmea_send_var, 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool NetNMEAClient::buildReport() 
{
  m_msgs << "Most recent NMEA string received: " << nmea_received << "\n";
  m_msgs << "Most recent NMEA string sent:     " << nmea_sent << "\n";

  return(true);
}

bool NetNMEAClient::connectToNMEAServer() {
  try
  {
    using boost::asio::ip::tcp;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(server, port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    socket = new boost::asio::ip::tcp::socket(io_service);

    boost::asio::connect(*socket, endpoint_iterator);
    return true;
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
    return false;
  }
  

}

void NetNMEAClient::writeMessage(string message) {
  try
  {
    if(message.back() != '\n')
    {
      message += '\n';
    }
    boost::system::error_code error;
    boost::asio::write(*socket, boost::asio::buffer(message), error);
    if (error == boost::asio::error::eof) 
          reportEvent("Connection Closed by Server");
        else if (error)
          throw boost::system::system_error(error);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void NetNMEAClient::startReceive() {
  try
  {
    boost::asio::async_read_until(*socket,buffer,
        '\n', boost::bind(&NetNMEAClient::handle_read, this,
              boost::asio::placeholders::error,
              boost::asio::placeholders::bytes_transferred));
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

void NetNMEAClient::handle_read(const boost::system::error_code& error,
        size_t size)
{
  try
  {
    if (!error)
    {
      std::istream is(&buffer);
      std::string data(size,'\0');
      is.read(&data[0],size);

      Notify(nmea_recv_var, data);
      nmea_received = data;
     startReceive();
    }
    else
    {
      throw boost::system::system_error(error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

}


