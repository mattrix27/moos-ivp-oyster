/************************************************************/
/*    NAME: Carter Fendley                                  */
/*    ORGN: MIT                                             */
/*    FILE: ButtonBox.cpp                                   */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "ButtonBox.h"

using namespace std;

//---------------------------------------------------------
// Constructor

ButtonBox::ButtonBox()
{
  m_first_read = true;
}

//---------------------------------------------------------
// Destructor

ButtonBox::~ButtonBox()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool ButtonBox::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

     if(key != "APPCAST_REQ") // handled by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key);
   }

   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool ButtonBox::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool ButtonBox::Iterate()
{
  AppCastingMOOSApp::Iterate();

  if(!m_serial->IsGoodSerialComms()){
    if(m_valid_serial_connection){
      reportRunWarning("Serial communication stopped.");
    }
    m_valid_serial_connection = serialSetup(false);
  }

  while(m_valid_serial_connection && m_serial->DataAvailable()){ // grab data from arduino
    string data = m_serial->GetNextSentence();
    
    if(m_first_read){
      //Dump first read beacuase it is almost always mangled
      m_first_read = false;
      continue;
    }


    parseSerialString(data);

    for(int i=0; i < m_button_values.size(); i++){
      if(m_last_button_values.size() <= i){
        m_last_button_values.push_back(m_button_values[i]);
      }
      
      if(m_last_button_values[i] != m_button_values[i]){
        std::vector<VarDataPair> *posts;
        if(m_button_values[i])
          posts = &m_button_down_posts[i];
        else
          posts = &m_button_up_posts[i];

        for(unsigned int j=0; j<posts->size(); j++){
          VarDataPair pair = posts->at(j);

          std::stringstream report;
          report << "NEW POST: var:" << pair.get_var() << " val:";
          if(!pair.is_string()){
            Notify(pair.get_var(), pair.get_ddata());
            report << pair.get_ddata() << " (ddata)";
          }else{
            Notify(pair.get_var(), pair.get_sdata());
            report << pair.get_sdata() << " (sdata)";
          }
          reportEvent(report.str());
        }

        m_last_button_values[i] = m_button_values[i];
      }
    }
  }
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool ButtonBox::OnStartUp()
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
    if(param == "PORT") { // define the port where we access the arduino
      handled = true;
      m_serial_port = line;

      if(m_serial_port.empty()){
	    reportConfigWarning("Mission file parameter PORT must not be blank");
      }
    }

    if(param == "BAUDRATE"){ // define the speed at which we receive data
        handled = true;
        m_baudrate = atoi(line.c_str());
    }

    if(param.substr(0,7) == "BUTTON_" && param.substr(param.length() - 10, param.length() ) == "_DOWN_POST"){ 
      // grabs the button down post data
      handled = true;

      int button_number = atoi(param.substr(7,param.length()-5).c_str());

      VarDataPair pair = stringToVarDataPair(line);
      if(pair.valid()){
        std::map<int, std::vector<VarDataPair> >::iterator it;
        it = m_button_down_posts.find(button_number);

        m_button_down_posts[button_number].push_back(pair);
      }else{
        reportConfigWarning("Invalid VarDataPair: "+line); 
      }

    }

    if(param.substr(0,7) == "BUTTON_" && param.substr(param.length() - 8, param.length() ) == "_UP_POST"){ 
      // grabs the button down post data
      handled = true;

      int button_number = atoi(param.substr(7,param.length()-5).c_str());

      VarDataPair pair = stringToVarDataPair(line);
      if(pair.valid()){
        std::map<int, std::vector<VarDataPair> >::iterator it;
        it = m_button_up_posts.find(button_number);

        m_button_up_posts[button_number].push_back(pair);
      }else{
        reportConfigWarning("Invalid VarDataPair: "+line); 
      }

    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }

  m_valid_serial_connection = serialSetup(true);

  registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void ButtonBox::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool ButtonBox::buildReport()
{
  m_msgs << endl << "SETUP" << endl << "-----" << endl;
  m_msgs << "	PORT: " << m_serial_port << endl;
  m_msgs << "	BAUDRATE: " << m_baudrate << endl;

  m_msgs << endl << "STATUS" << endl << "-----" << endl;
  m_msgs << "	Valid serial connection: " << std::boolalpha << m_valid_serial_connection << endl;
  m_msgs << "\tData available: " << std::boolalpha << (bool) m_serial->DataAvailable() << endl;

  m_msgs << endl;

  if(m_button_values.size() == 0){
    m_msgs << "	No current button values." << endl;
  }

  for(std::vector<int>::size_type i = 0; i != m_button_values.size(); i++) {
    m_msgs << "\tBUTTON #"<< i << ": " << m_button_values[i] << endl;
  }

  return(true);
}

bool ButtonBox::serialSetup(bool reportErrors)
{
  std::string errMsg = "";
  m_serial = new SerialComms(m_serial_port, m_baudrate, errMsg);

  if (m_serial->IsGoodSerialComms()) {
    m_serial->Run();
    string msg = "Serial port opened. Communicating over port ";
    msg += m_serial_port;
    reportEvent(msg);
    return(true);
  }
  if(reportErrors){
    std::stringstream ss;
    ss << "Unable to open serial: " << m_serial_port << " with baud: " << m_baudrate;
    ss << " Err: " << errMsg;
    reportRunWarning(ss.str());
  }

  return(false);
}

void ButtonBox::parseSerialString(std::string data) //parse data sent via serial from arduino
{
  if(data.size() == 0){
    reportRunWarning("Empty string sent to parser.");
    return;
  }
  if(data.at(0) != '$'){
    reportEvent("Malformed data string! Does not begin with $ char");
    return;
  }

  std::string values = data.substr(data.find(":") + 1);

  for(unsigned int i = 0; i<values.length(); i++) {
    char c = values[i];
    if(c != '0' && c != '1' && c != ','){
      std::string err = "Malformed data string: ";
      err += data;
      reportEvent(err);
      return;
    }
  }

  std::stringstream ss(values);
  m_button_values.clear();
  while(ss.good()){
    string substr;
    getline(ss, substr, ',');

    if(substr.compare("0") == 0){
      m_button_values.push_back(true);
    }else if(substr.compare("1") == 0){
      m_button_values.push_back(false);
    }else{
      std::string err = "Malformed data string: ";
      err += data;
      reportRunWarning(err);
      return;
    }
  }
}

