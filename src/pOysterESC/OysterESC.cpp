/************************************************************/
/*    NAME: Matt Tung                                              */
/*    ORGN: MIT                                             */
/*    FILE: OysterESC.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include <iostream>
#include "MBUtils.h"
#include "ACTable.h"
#include "OysterESC.h"
#include <signal.h>

using namespace std;

//---------------------------------------------------------
// Constructor

OysterESC::OysterESC() : port(io)
{
  m_time = MOOSTime();

  m_prev_left = 0;
  m_prev_right = 0;
  m_curr_left = 0;
  m_curr_right = 0;
  m_message = "";

  serialPortName = "";
  baudRate = 19200;
  m_base = 1500;
  m_range = 400;
}

//---------------------------------------------------------
// Destructor

OysterESC::~OysterESC()
{
  port.close();
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool OysterESC::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string msgKey = msg.GetKey();

    if (msgKey == m_inputName) {
      m_time = msg.GetTime();
      bool left_val = false;
      bool right_val = false;
      int left = 0;
      int right = 0;
      string raw = msg.GetString();

      int comma_i = raw.find(",");
      if (comma_i > 0) {
        string left_str = raw.substr(0, comma_i);
        string right_str = raw.substr(comma_i+1);

        int left_i = left_str.find("=");
        int right_i = right_str.find("=");

        if (left_i > 0) {
          string left_sval = left_str.substr(left_i+1);
          // if (isdigit(left_str)) {
          left = m_base + (m_range * stod(left_sval));
          left_val = true;
          // }
        }

        if (right_i > 0) {
          string right_sval = right_str.substr(right_i+1);
          // if (isdigit(right_str)) {
          right = m_base + (m_range * stod(right_sval));
          right_val = true;
          // }
        }
      }

      if (left_val && right_val) {
        m_prev_left = m_curr_left;
        m_curr_left = left;
        m_prev_right = m_curr_right;
        m_curr_right = right;

        m_message = to_string(left) + "," + to_string(right) + "\n";
        send();
      }
      else {
        reportRunWarning("INVALID MESSAGE FORMAT");
      }
    }

    else if(msgKey != "APPCAST_REQ") { // handle by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + msgKey);
    }
  }
	
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool OysterESC::OnConnectToServer()
{
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool OysterESC::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!

  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool OysterESC::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();


  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  bool handledPort = false;
  bool handledBaud = false;

  list<string>::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig  = *p;
    string line  = *p;
    string param = toupper(biteStringX(line, '='));
    string value = line;

    if(param == "SERIALPORT") {
      serialPortName = value;
      handledPort = true;
    }
    else if(param == "SERIALBAUD") {
      baudRate = atoi(value.c_str());
      handledBaud = true;
    }
    if(param == "INPUT") {
      m_inputName = value;
    }
  }

  if(!handledPort) {
    reportConfigWarning("No serial port name in configuration!");
  }
  if(!handledBaud) {
    reportConfigWarning("No serial port baud rate in configuration!");
  }

  RegisterVariables();	
// serial port initialization
  connect(serialPortName, baudRate);
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void OysterESC::RegisterVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register(m_inputName, 0);
}


bool OysterESC::buildReport() 
{
  m_msgs << "Last message: " << m_message << "\n";
  m_msgs << "Serial port is open: " << port.is_open() << "\n";
  return(true);
}


// Serial connection routine from example on https://github.com/labust/labust-ros-pkg/wiki/Create-a-Serial-Port-application
bool OysterESC::connect(const string& port_name, int baud)
{
  using namespace boost::asio;
  port.open(port_name);
    
  //Setup port
  port.set_option(serial_port::baud_rate(baud));
  port.set_option(serial_port::flow_control(serial_port::flow_control::none));
  port.set_option(serial_port::character_size(8));
  port.set_option(serial_port::parity(serial_port::parity::none));
  port.set_option(serial_port::stop_bits(serial_port::stop_bits::one));

  if (port.is_open())
  {
    cout << "Port is open" << endl;
    //Start io-service in a background thread.
    //boost::bind binds the ioservice instance
    //with the method call
    runner = boost::thread(boost::bind(&boost::asio::io_service::run, &io));

    // make sure that the io_service does not return because it thinks it is out of work
    boost::asio::io_service::work work(io);


    // write to port such that data is produced once per second
    string s = "read\r"; // string to read data once from the sonde
    // string s = "scr\r";  // string to have sonde send data once per second as the default
    boost::system::error_code ec;
    boost::asio::write(port, boost::asio::buffer(s.c_str(), s.size()), ec);
  }

  return port.is_open();
}


bool OysterESC::send()
{
  using namespace boost::asio;

  if (!port.is_open()) {
    reportEvent("Reopening serial port");
    io.reset(); //debug
    connect(serialPortName, baudRate);
  }

  boost::system::error_code ec;
  boost::asio::write(port, boost::asio::buffer(m_message.c_str(), m_message.size()), ec);   

  return(!ec);
}