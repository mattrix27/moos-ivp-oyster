/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: DialogManager.cpp                               */
/*    DATE: Aug. 17 2015                                   */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "DialogManager.h"
#include "unistd.h"

using namespace std;

//---------------------------------------------------------
// Constructor

DialogManager::DialogManager()
{
  //Initialize state machine to waiting for voice command
  m_state = WAIT_COMMAND;

  //Initialize map for nicknames
  // example m_nicknames["nickname"]="vehicle_name";
  m_nicknames["archie"]="archie";
  m_nicknames["betty"]="betty";
  m_nicknames["charlie"]="charlie";
  m_nicknames["davis"]="davis";
  m_nicknames["evan"]="evan";
  m_nicknames["felix"]="felix";
  m_nicknames["gus"]="gus";
  m_nicknames["team"]="all";
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool DialogManager::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

    //#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString(); 
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
    //#endif
    
    if(key == "SPEECH_RECOGNITION_SENTENCE") {
      //A Finite State Machine (FSM) is used to determine the mode
      string keepConversation;
      keepConversation = "User: " + sval;
      m_conversation.push_back(keepConversation);

      if(m_state == WAIT_COMMAND) {
	m_state = COMMAND_RECEIVED;
	triggerCommandSequence(sval);
      }
      else if(m_state == WAIT_ACK) {
	m_state = ACK_RECEIVED;
	triggerAckSequence(sval);
      }
    }

    else if(key != "APPCAST_REQ") // handle by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
  }
	
  return(true);
}

//---------------------------------------------------------
// Procedure: triggerAckSequence
// DialogManager is waiting for an ack to
// command verification
// Here we need to check for 3 states
// Received "Yes" -- triggers command forwarding
// Received "No" -- reverts us back to waiting for a command

void DialogManager::triggerAckSequence(string sval)
{
  std::string ackStatement = "";
  std::string local_message = "";
  bool matched = false;
  bool nameMatched = false;
  
  if(sval == "YES") {
    /*  Legacy Code From When Used Nicknames Only - Prior to defining .moos speech - var pairs
   //chop up m_commanded_string on space
    std::string nickNameCapitalized = biteString(m_commanded_string,' ');
    std::string nickName = tolower(nickNameCapitalized);
    std::string commanded = m_commanded_string;
    std::string recipient;

    //search through nickname map to confirm mapping
    std::map<string,string>::iterator it;
    it = m_nicknames.find(nickName);
    if(it == m_nicknames.end()) {
      //nickname not found
    }
    else {
      nameMatched = true;
      recipient = m_nicknames.find(nickName)->second;
    */	

    //search through possible speech sentences defined in .moos file
    std::map<string,list<var_value> >::iterator it;
    it = m_actions.find(m_commanded_string);
    if(it == m_actions.end()) {
      //Speech Sentence to Variable Assignment not defined!
    }
    else { //we have found the Speech Sentence defined in the .moos file
      matched = true;
      //now go through and publish MOOS vars 
    //access the list
    std::list<var_value> tmpList=    m_actions.find(m_commanded_string)->second;
    std::list<var_value>::iterator il;
    for(il = tmpList.begin(); il != tmpList.end(); ++il) {
      m_Comms.Notify(il->var_name,il->value);
    }
    }
  }

  //Here we check to see if the person answered No for an Ack which cancels everything and we wait for another command
  //If the person answers yes, we must check whether
  //1) The Nickname provided matches a robot
  //2) The command after the name has been defined
  if(sval == "NO") { //all is canceled
 
    ackStatement = "Command Canceled";
  }
  /*  else  if(nameMatched == false) { //name provided does not match any defined
    ackStatement = "Incorrect Ack Or Wrong Name";
    } */

  else if(matched == true) { //command matched
	  
    ackStatement = "Command Sent";
  }
  else {
    ackStatement = "Error Wrong Ack or Command Not Defined";
  }

  m_Comms.Notify("SAY_MOOS",ackStatement);
  string keepConversation;
  keepConversation = "DM: " + ackStatement;
  m_conversation.push_back(keepConversation);
   
  if(matched == true) {
    m_Comms.Notify("SPEECH_COMMANDED", m_commanded_string);
  }
  m_state = WAIT_COMMAND;
}

//---------------------------------------------------------
// Procedure: triggerCommandSequence
// A command has been received
// It will be appended with a dialog question
// Then place the Finite State Machine (FSM)
// into a wait for ack state either a "yes" or a "no"

void DialogManager::triggerCommandSequence(string sval)
{

  //Ignore "YES" and "NO"
  if(sval == "YES" || sval == "NO") {
    //ignore
    m_state = WAIT_COMMAND;
  }
  else {
  std:string svalLowered = tolower(sval);
    //Append question to command
    string newSVal = "say={Did you mean " + svalLowered +"}, rate=200";
    //Send verification question
    m_Comms.Notify("SAY_MOOS",newSVal);
    string toKeepConversation = "DM: Did you mean " + svalLowered;
    m_conversation.push_back(toKeepConversation);

    m_commanded_string = sval;
    //Place FSM into wait for acknowledgement state
    m_state = WAIT_ACK;
  }
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool DialogManager::OnConnectToServer()
{
  registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool DialogManager::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!
  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool DialogManager::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  //  m_MissionReader.EnableVerbatimQuoting(true);
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
    else if(param == "BAR") {
      handled = true;
    }
    else if(param == "NICKNAME") {
      handled = handleNickNameAssignments(line);
    }
    else if(param == "SENTENCE") {
      handled = handleActionAssignments(line);
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);

  }
  
  registerVariables();	
  return(true);
}

//-------------------------------------------------------
// Procedure: handleNickNameAssignments

bool DialogManager::handleNickNameAssignments(std::string line) {

  std::string actualVehicleName = tolower(biteStringX(line,':'));
  std::string vehicleNickName = tolower(line);

  //find current vehicleName nickName pair
  //find original vehicle entry
  int erased =   m_nicknames.erase(actualVehicleName);


    m_nicknames[vehicleNickName] = actualVehicleName;
    return (true);
}

//-------------------------------------------------------
// Procedure: handleActionAssignments

bool DialogManager::handleActionAssignments(std::string line) {

  //take human entered sentence and convert to uppercase
  //because this is how speech does it
  //spaces are key for sentence so make sure to keep them
  std::string actualWholeSentence = toupper(biteStringX(line,':'));

  if(line == "") { //config warning as missing proper Action format
    return false;
  }

  //Before assigning speech to map we must make sure it is
  // All caps and keeps the spaces between the words
  std::string speechAdaptedSentence;

  //search for _'s until we find more elegant way of
  //including spaces maybe with quotes
  std::size_t found = actualWholeSentence.find('_');
  while(found!=std::string::npos) {
    actualWholeSentence.replace(found,1," ");

    //check again for _'s that should be changed to a space
    found = actualWholeSentence.find('_');
  }
  /*
  //Julius speech sentences in quotation marks
  if(isQuoted(actualWholeSentence)) {//means sentence is quoted
    actualWholeSentence = stripQuotes(actualWholeSentence); //remove the quotes
  }
  */
  //Now contain whole list of var-value pairs
  //make sure to enforce MOOS VARS are all caps
  //but keep values as assigned
  std::string totalListOfVarValuePairs = line;

  //break them up by the '+' plus sign
  //we will need to loop here on the '+'s 
  //if there was no new '+' then biteStringX assigns "" to original string
  std::list<var_value> tmpList;
  while(totalListOfVarValuePairs != "") {
    std::string tempVarValuePair = biteStringX(totalListOfVarValuePairs,'+');

    //assume var_name = var_value is the variable
    std::string varName = biteStringX(tempVarValuePair,'=');

    if(tempVarValuePair == "") { //poor formating of var_name = var_value
      return false;
    }

    var_value tmpVarValue;
    tmpVarValue.var_name = varName;

    //remove quotes if needed
    if(isQuoted(tempVarValuePair)) { //found quotes
      tempVarValuePair = stripQuotes(tempVarValuePair);
    }

    tmpVarValue.value = tempVarValuePair;

    //assign the var_value struct to the list 
    tmpList.push_back(tmpVarValue);
  }

  m_actions[actualWholeSentence] = tmpList;

    return (true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void DialogManager::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  m_Comms.Register("SPEECH_RECOGNITION_SENTENCE",0);
}


//------------------------------------------------------------
// Procedure: buildReport()

bool DialogManager::buildReport() 
{
  //Example AppCast Output
  //  m_msgs << "============================================ \n";
  //m_msgs << "File:                                        \n";
  //m_msgs << "============================================ \n";

  /* NICKNAMES ARE CURRENTLY NOT AVAILABLE IN V2.0
  //Let's output the nickname to vehicle pairings
  ACTable actab(2);
  actab << "Nickname | Vehicle Name";
  actab.addHeaderLines();
  for(std::map<string,string>::iterator it=m_nicknames.begin(); it!=m_nicknames.end(); ++it)
    actab<< it->first << it->second; 
      
  m_msgs << actab.getFormattedString();
  */

  //List action of speech sentences to variables published
  for(std::map<string,std::list<var_value> >::iterator it = m_actions.begin(); it!=m_actions.end(); ++it) {
    m_msgs << endl << endl << "Sentence Action: " << it->first << " : ";
    //how do we access the items of the list?
    std::list<var_value>::iterator listIt = it->second.begin();
    for( ; listIt != it->second.end(); ++listIt) {
      m_msgs << listIt->var_name << "=" << listIt->value;
      std::advance(listIt,1);
      if(listIt==it->second.end()) {
	}
      else {
	m_msgs <<" + ";

	}
      std::advance(listIt,-1);

    }
  }


  m_msgs <<endl<<endl<<"CURRENT STATE: "<< endl;
  if(m_state == WAIT_COMMAND) {
    m_msgs <<"Ready For Command."<< endl;
  }
  else if (m_state == COMMAND_RECEIVED) {
    m_msgs <<"Received Command." << endl;
  }
  else if (m_state == WAIT_ACK) {
    m_msgs << "Waiting For ACK: Yes or No" << endl;
  }
  else if(m_state == ACK_RECEIVED) {
    m_msgs << "ACK Received" << endl;
  }

  //Let's keep the coversation down to 10 elements (no need to grow unbounded)
 int sizeVec = m_conversation.size();
 if(sizeVec > 10) {
    //greater than 10 so let's delete the first set to make it 10 elements
   int difference = sizeVec - 10;
   m_conversation.erase(m_conversation.begin(),m_conversation.begin()+difference);
  }

  //Let's list the last 10 conversation sentences
 m_msgs << endl << "CONVERSATIONS:" << endl << endl;
  for(std::vector<std::string>::reverse_iterator it = m_conversation.rbegin(); it!=m_conversation.rend(); ++it) {
    m_msgs << *it << endl;
  }
  
  return(true);
}
