/************************************************************/
/*    NAME: Paul R.                                               */
/*    ORGN: AUV Lab @ MIT                                             */
/*    FILE: NetNMEAServer.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "NetNMEAServer.h"
#include <boost/bind.hpp>

using namespace std;

//---------------------------------------------------------
// Constructor

NetNMEAServer::NetNMEAServer()
{
  // reasonable defaults
  port = 2000;
  nmea_send_var = "FRONT_SEAT_NMEA";
  nmea_recv_var = "NMEA_RECEIVED";
  m_message = "";
}

//---------------------------------------------------------
// Destructor

NetNMEAServer::~NetNMEAServer()
{
  delete server;
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool NetNMEAServer::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    
    m_message = key;

    if(key == nmea_send_var) {
      string data = msg.GetString();
      server->writeToAll(data);
    }

    else if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
   }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool NetNMEAServer::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool NetNMEAServer::Iterate()
{
  AppCastingMOOSApp::Iterate();
  m_message = server->writeReport();
  server->cleanUp();
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool NetNMEAServer::OnStartUp()
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

    if(param == "PORT") {
      port = atoi(value.c_str());
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

  server = new NMEAServer(io_service, port, &m_Comms, nmea_recv_var);

  // make sure that the io_service does not return because it thinks it is out of work
  boost::asio::io_service::work work(io_service);

  //Start io-service in a background thread.
  //boost::bind binds the ioservice instance
  //with the method call
  runner = boost::thread(
      boost::bind(
          &boost::asio::io_service::run,
          &io_service));


  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void NetNMEAServer::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(nmea_send_var, 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool NetNMEAServer::buildReport() 
{
  m_msgs << "Listening to: " << nmea_recv_var << endl;
  m_msgs << "Sending to:   " << nmea_send_var << endl;
  m_msgs << server->writeReport();

  
  return(true);
}




