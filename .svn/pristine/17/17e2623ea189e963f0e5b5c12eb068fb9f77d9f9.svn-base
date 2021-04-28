/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: DialogManager_5_0.cpp                           */
/*    DATE: Aug. 17 2015                                    */
/*    UPDATED: Aug. 10 2016                                 */
/*    UPDATED: July 28 2017                                 */
/*    UPDATED: January 11 2019                              */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "DialogManager_5_0.h"
#include "unistd.h"

using namespace std;

//---------------------------------------------------------
// Constructor

DialogManager::DialogManager()
{
  //Initialize state machine to waiting for voice command
  m_state = WAIT_COMMAND;
  m_number_ack_attempts = 0;

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

  //initialize for backwards compatibility to use most likely sentence regardless of word confidence scores.
  m_use_confidence = false;
  m_confidence_thresh = 0.0;
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
    
    if(key == "SPEECH_RECOGNITION_SENTENCE" || key == "SPEECH_RECOGNITION_SCORE") {
      //check to see if uses sentence or score based on use confidence
      if(m_use_confidence == true) {
        if(key == "SPEECH_RECOGNITION_SENTENCE") { //we are waiting for SCORE
          continue;
        }
        else { //SCORE has arrived

          bool goOn;
          goOn = acceptConfidenceScores(sval);
          if(goOn == false) { //reject sentence because confidence scores are too low
            string rejection = "Sentence Rejected Due to Low Confidence: ";
            rejection += sval;
            reportRunWarning(rejection);
            m_Comms.Notify("DIALOG_ERROR",rejection);

            //trigger did not understand sequence
            //which for now is "SAY_AGAIN"
            std::string queryStatement = "SAY AGAIN";
            if(m_use_wave_files == "YES") { //format string for using wave files
              //replace spaces with underscores for file convention
              std::string fileAckStatement;
              fileAckStatement = tolower(queryStatement);
              fileAckStatement = spacesToUnderscores(fileAckStatement);
              fileAckStatement = "file=sounds/" + fileAckStatement;
              fileAckStatement += ".wav";
              m_Comms.Notify("SAY_MOOS",fileAckStatement);
            }
            else {
              m_Comms.Notify("SAY_MOOS",queryStatement);
            }
            continue;
            
          }
          else if(goOn == true) { //word confidence has been accepted
            //now strip out just recognized sentence and assign to sval
            string tempSVAL;
            tempSVAL = justSentence(sval);
            sval = tempSVAL;
          }
        }
      }
      else if (m_use_confidence == false) {
        if(key == "SPEECH_RECOGNITION_SCORE") {//we are looking for SENTENCE
          continue;
        } //otherwise, we have found SENTENCE and proceed as already accepted
      }


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
// Procedure: triggerVariablePosts
// DialogManager triggers variable posts based on speech sentences

bool DialogManager::triggerVariablePosts()
{
  bool matched = false;
    //search through possible speech sentences defined in .moos file
    std::map<string,list<var_value> >::iterator it;
    it = m_actions.find(m_commanded_string);
    if(it == m_actions.end()) {
      //Speech Sentence to Variable Assignment not defined!
      matched = false;
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
    return matched;
}

//---------------------------------------------------------
// Procedure: triggerAckSequence
// DialogManager is waiting for an ack to
// command verification
// Here we need to check for 3 states
// Received "Yes" or confirm word-- triggers command forwarding
// Received "No" or decline word -- reverts us back to waiting for a command

void DialogManager::triggerAckSequence(string sval)
{
  std::string ackStatement = "";
  std::string local_message = "";
  bool matched = false;
  bool nameMatched = false;
  
  //in 3.0 we now support user defined confirmation word
  if(sval == m_confirm_word[m_commanded_string]) {
    matched = triggerVariablePosts();
    ackStatement = "Command Sent";
    m_state = WAIT_COMMAND;
    m_number_ack_attempts = 0;
  }

  //Here we check to see if the person answered No for an Ack which cancels everything and we wait for another command
  //If the person answers yes, we must check whether
  //1) The Nickname provided matches a robot
  //2) The command after the name has been defined
  else if(sval == m_decline_word[m_commanded_string]) { //all is canceled
 
    ackStatement = "Command Canceled";
    m_state = WAIT_COMMAND;
    m_number_ack_attempts = 0;
  }

  else if(m_number_ack_attempts==1){ //means have have errored our ack a certain number of times
    ackStatement = "Command Canceled Wrong Responses";
    m_state = WAIT_COMMAND;
    m_number_ack_attempts = 0;
  }
  else{
    //    ackStatement = "Error Wrong Ack";
    ackStatement = "Try one more time " +  m_confirm_word[m_commanded_string] + " or " +  m_decline_word[m_commanded_string];
    m_state = WAIT_ACK;
    m_number_ack_attempts += 1;
  }

  if(m_use_wave_files == "YES") { //format string for using wave files
    //replace spaces with underscores for file convention
    std::string fileAckStatement;
    fileAckStatement = tolower(ackStatement);
    fileAckStatement = spacesToUnderscores(fileAckStatement);
    fileAckStatement = "file=sounds/" + fileAckStatement;
    fileAckStatement += ".wav";
    m_Comms.Notify("SAY_MOOS",fileAckStatement);
  }
  else {
    m_Comms.Notify("SAY_MOOS",ackStatement);
  }
  
  string keepConversation;
  keepConversation = "DM: " + ackStatement;
  m_conversation.push_back(keepConversation);
   
  if(matched == true) {
    m_Comms.Notify("SPEECH_COMMANDED", m_commanded_string);
  }
  
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
  //seems speech recognition will easily fire a false positive
  if(sval == "YES" || sval == "NO") {
    //ignore
    m_state = WAIT_COMMAND;
  }
  else {

    
    string newSVal;
    if(m_use_wave_files == "YES") {
     newSVal = "file=sounds/";
    }
    else {
      newSVal = "say={";
    }
    
    string toKeepConversation = "DM: ";
    
    //search through possible speech sentences defined in .moos file
    std::map<string,list<var_value> >::iterator it;
    it = m_actions.find(sval);
    if(it == m_actions.end()) {
      //Speech Sentence to Variable Assignment not defined!
      newSVal += "command not defined";
      toKeepConversation += " Command Not Defined";
      m_state = WAIT_COMMAND;
    }
    else{
 
      //keep track of the command 
	m_commanded_string = sval;

      //for version 3.0 we now support no acknowledgement commands
      if(m_just_publish[sval] == true) {
	//this sentence has a NOCONFIRM option set
	bool posted =  triggerVariablePosts();

	newSVal += "command sent";
	toKeepConversation += "Command Sent";
	//Place FSM into wait for next command
	m_state = WAIT_COMMAND;
      }
      else {
	std::string svalLowered = tolower(sval);
	//Append question to command
	newSVal += "did you mean " + svalLowered;
        toKeepConversation = "DM: Did you mean " + svalLowered;

	//Place FSM into wait for acknowledgement state
	m_state = WAIT_ACK;
      }
    }

    if(m_use_wave_files == "YES") {
      newSVal = spacesToUnderscores(newSVal);
      newSVal +=".wav";
    }
    else {
      newSVal +="}, rate=200";
    }
    
    //Send verification question
    m_Comms.Notify("SAY_MOOS",newSVal);
    m_conversation.push_back(toKeepConversation);

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
    else if(param == "USE_WAV_FILES") {
      handled = handleWaveFiles(line);
    }
    else if(param == "CONFIDENCE_THRESH"){
      handled = handleConfidenceThresh(line);
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
  std::string sentenceAndOptions = toupper(biteStringX(line,':'));

  if(line == "") { //config warning as missing proper Action format
    return false;
  }

  //adding for version 3.0 ability to have no confirmation where word accepted then trigger
  //expecting word NOCONFIRM after sentence within '{' '}' so  ARNOLD_FOLLOW {NOCONFIRM}
  std::string actualWholeSentence = toupper(biteStringX(sentenceAndOptions,'{'));

  //search for _'s until we find more elegant way of
  //including spaces maybe with quotes
  std::size_t found = actualWholeSentence.find('_');
  while(found!=std::string::npos) {
    actualWholeSentence.replace(found,1," ");

    //check again for _'s that should be changed to a space
    found = actualWholeSentence.find('_');
  }

  if(sentenceAndOptions == "") { 
    //means no specified words for CONFIRM or for DECLINE
  m_just_publish[actualWholeSentence] = false;
  m_confirm_word[actualWholeSentence] = "YES";
  m_decline_word[actualWholeSentence] = "NO";
  }
  else { //means using 3.0 formating with {confirmation options}
    //strip of the '}' character
    std::string justOptions = biteStringX(sentenceAndOptions,'}');

    if(sentenceAndOptions != "") { 
      //config warning as missing proper Action format
      return false;
    }

    //check for '|' which splits confirmation and decline words
    std::string checkNoConfirmOption = biteStringX(justOptions,'|');

    if (justOptions == "") { //means no '|' character was found
      //so check for NOCONFIRM option
      if (checkNoConfirmOption == "NOCONFIRM") { 
	//means if sentence recognized just trigger posting variables

	m_just_publish[actualWholeSentence] = true;
	m_confirm_word[actualWholeSentence] = "";
	m_decline_word[actualWholeSentence] = "";
      }
      else{
	//if not NOCONFIRM then this is a malformed sentence action pairing
	return false;
      }
    }
    else { // this sentence's confirmation is {confirm = someconfirm | deline = somedecline}
      //this means checkNoConfirmOption will have Confirm
      std::string confConfirm = biteStringX(checkNoConfirmOption,'=');

      if(confConfirm!="CONFIRM" || checkNoConfirmOption == "") {
	//means first option is not CONFIRM or that malformed lacking Confirm=word
	return false;
      }
      else{

	m_just_publish[actualWholeSentence] = false;
	m_confirm_word[actualWholeSentence] = checkNoConfirmOption;
      }

      //this means justOptions will have Decline
      std::string confDecline = biteStringX(justOptions,'=');
      if(justOptions == "" || confDecline != "DECLINE"){
	//means first option is not DECLINE or that malformed lacking Decline=word
	return false;
      }
      else{
	m_just_publish[actualWholeSentence] = false;
	m_decline_word[actualWholeSentence] = justOptions;
      }
    }

  }
  
  //Before assigning speech to map we must make sure it is
  // All caps and keeps the spaces between the words
  std::string speechAdaptedSentence;


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


//-------------------------------------------------------
// Procedure: spacesToUnderscores
std::string DialogManager::spacesToUnderscores(std::string line) {
  //search for spaces and replace with underscores
  std::size_t found = line.find(' ');
  while(found!=std::string::npos) {
    line.replace(found,1,"_");

    //check again for _'s that should be changed to an underscore
    found = line.find(' ');
  }

  std::string augmentedLine = line;

  return augmentedLine;
}

//-------------------------------------------------------
// Procedure: handleWaveFiles

bool DialogManager::handleWaveFiles(std::string line) {
  //decide whether to use local text-to-speech or wav files
  //we are expecting a sentence that is formated as
  //USE_WAV_FILES=YES or =NO
  //std::string variableName = toupper(biteStringX(line,'='));
  std::string variableName = toupper(line);

  if(line == "") { //config warning as missing proper format
    return false;
  }

    //if(variableName == "USE_WAV_FILES") { //correctly formed variable name
    if(variableName == "YES" || variableName == "NO") { //proper option selected
      m_use_wave_files = variableName;
      return true;
    }
    else {  //wrong options
      return false;
    }
    //  else { //porly formed variable name
    //return false;
    //}
}

//-------------------------------------------------------
// Procedure: handleConfidenceThresh

bool DialogManager::handleConfidenceThresh(std::string line) {
  //decide whether to use Julius word confidence to reject
  //the most likely sentence
  //uses information from SPEECH_RECOGNITION_SCORE variable
  //we are expecting a sentence that is formated as
  //confidence_thresh = 0.7
  //std::string variableName = toupper(biteStringX(line,'='));

  if(line == "") { //config warning as missing proper format
    return false;
  }

  double catchConfidenceThresh = atof(line.c_str());

  if(catchConfidenceThresh == 0.0) { //invalid conversion atof
    return false;
  }
  else if (catchConfidenceThresh < 0.0 || catchConfidenceThresh > 1.0){ //valid float but out of range
    reportConfigWarning("confidence_thresh must be in range (0.0,1.0]");
    return false;
  }
  else {  //confidence thresh set
    m_use_confidence = true;
    m_confidence_thresh = catchConfidenceThresh;
    return true;
  }
}

//-------------------------------------------------------
// Procedure: acceptConfidenceScores

bool DialogManager::acceptConfidenceScores(std::string sval) {
  //decide whether we will accept the confidence scores based
  //on the m_confidence_thresh

  //first need to strip out the confidence scores and make sure they are above thresh
  std::string tempString;
  //assumption is format is "sentence= BLUE THREE ATTACK, confidencescores=1:0.99:0.91:0.73, score=-12884.4"
  //step 1: separate out confidencescores with tokStringParse
  tempString = tokStringParse(sval, "confidencescores", ',', '=');
  //step 2: use parseString to create vector of strings separated by ':' char
  vector<string> temp_str_vector = parseString(tempString, ':');
  //step 3: locally convert each string to check against threshold
  //skip first and last as they are for the silence portions and should be 1.0
  if(temp_str_vector.size()==2) {
    //error as at minimum will be size 3 with first and last being silence
    return false;
  }
  for(unsigned int i = 1; i<temp_str_vector.size()-1; i++){
    float temp_float;
    temp_float = atof(temp_str_vector[i].c_str());
    if( temp_float < m_confidence_thresh){
      return false; //any one of the words has less than confidence threshold then fail
    }
  }

  return true;
}

//-------------------------------------------------------
// Procedure: justSentence

std::string DialogManager::justSentence(std::string sval) {
  //strip out only the recognized sentence from
  //SPEECH_RECOGNITION_SCORE
  //which includes speech confidence scores
  std::string tempString;
  //assumption is format is "sentence= BLUE THREE ATTACK, confidencescores=1:0.99:0.91:0.73, score=-12884.4"
  //step 1: separate out sentence with tokStringParse
  tempString = tokStringParse(sval, "sentence", ',', '=');

  return tempString;
}

//---------------------------------------------------------
// Procedure: registerVariables

void DialogManager::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  // Register("FOOBAR", 0);
  m_Comms.Register("SPEECH_RECOGNITION_SENTENCE",0);
  m_Comms.Register("SPEECH_RECOGNITION_SCORE",0);
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

  m_msgs << "Use Word Confidence Scores = ";
  if(m_use_confidence == true) {
    m_msgs << "YES";
      }
  else {
    m_msgs << "NO";
    
  }
  m_msgs << endl;
  m_msgs << "Word confidence threshold = " << m_confidence_thresh << endl;
  m_msgs << "USE_WAV_FILES = " << m_use_wave_files << endl;
  
  //List action of speech sentences to variables published
  for(std::map<string,std::list<var_value> >::iterator it = m_actions.begin(); it!=m_actions.end(); ++it) {
    m_msgs << endl << endl << "Sentence Action: " << it->first ;

    //adding NOCONFIRM, confirm = , decline = 
    if(m_just_publish[it->first] == true) {
      m_msgs << " { NOCONFIRM }";
    }
    else {
      m_msgs << " { Confirm = " + m_confirm_word[it->first] + " | Decline = " + m_decline_word[it->first] + " }";
    } 

    m_msgs << " : ";
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
