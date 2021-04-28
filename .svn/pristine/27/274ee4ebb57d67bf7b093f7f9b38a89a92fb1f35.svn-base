/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: SpeechRec_3_0.cpp                               */
/*    DATE: August 13th, 2015                               */
/*    DATE: August 17th, 2017                               */
/*    DATE: January 10th, 2019                              */
/************************************************************/
#include <algorithm>
#include <ctype.h>
#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "SpeechRec_3_0.h"
#include <string>
#include <iostream>

using namespace std;

//---------------------------------------------------------
// Constructor

SpeechRec::SpeechRec()
{
  //Initialize variables
  m_julius_debug = FALSE;
  m_message_sequence = 0;
  m_jconf = NULL;
  m_recog = NULL;
  m_state = RUNNING;
  m_pause_state = "FALSE";
  m_start_state = "ACTIVE";
}

static inline bool isNotAlnum(char c) { return !(isalnum(c));}

bool wordValid(const std::string &str)
{
  return (find_if(str.begin(), str.end(), isNotAlnum) == str.end());
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool SpeechRec::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();
    string sval  = msg.GetString();
    
#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

    if(key == "FOO") 
      cout << "great!";
    else if( key == "SPEECH_ACTIVE"){
      if(sval == "TRUE"){
               unmuteRec();
      }
      else if(sval == "FALSE"){
               muteRec();
      }
    }
    else if( key == "SPEECH_PAUSE") {
      if(sval == "TRUE") {
  muteRec();
      }
      else if(sval == "FALSE") {
        unmuteRec();
      }
    }

    else if(key != "APPCAST_REQ") // handle by AppCastingMOOSApp
      reportRunWarning("Unhandled Mail: " + key);
  }
	
  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool SpeechRec::OnConnectToServer()
{
  registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second
// checks whether the queues of m_messages and m_scores
// have been set in the Julius Speech Rec callback
// outputResults
bool SpeechRec::Iterate()
{
  AppCastingMOOSApp::Iterate();
  // Do your thing here!

  //use mutex lock to be thread safe and check for messages
  //if there are messages post them to the DB and AppCast
  m_message_lock.Lock();
  while(!m_messages.empty()) {
    std::string curr = m_messages.front();
    m_messages.pop();
    std::string score = m_scores.front();
    m_scores.pop();
    Notify("SPEECH_RECOGNITION_SENTENCE",curr);
    Notify("SPEECH_RECOGNITION_SCORE", score);
    reportEvent("JULIUS SENTENCE " + score);
  }
  while(!m_errors.empty()) {
    std::string err = m_errors.front();
    m_errors.pop();
    Notify("SPEECH_RECOGNITION_ERROR",err);
    reportEvent("JULIUS ERROR: " + err );
  }
  m_message_lock.UnLock();


  AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: statusRecReady
// dummy functions that can leverage Julius Speech Rec
// status options

void SpeechRec::statusRecReady(Recog *recog, void *dummy)
{
}

//---------------------------------------------------------
// Procedure: pauseRec
// on receiving SPEECH_PAUSE = TRUE we pause speech rec

void SpeechRec::pauseRec()
{
  j_request_pause(m_recog);
  m_pause_state = "TRUE";
}

//---------------------------------------------------------
// Procedure: unpauseRec
// on receiving SPEECH_PAUSE = TRUE we pause speech rec

void SpeechRec::unpauseRec()
{
  j_request_resume(m_recog);
  m_pause_state = "FALSE";
}

//---------------------------------------------------------
// Procedure: muteRec
// on receiving SPEECH_PAUSE = TRUE we mute speech rec

void SpeechRec::muteRec()
{
  m_recog->jconf->preprocess.level_coef = 0.0f;
  m_recog->adin->level_coef = 0.0f;
  m_pause_state = "TRUE";
}

//---------------------------------------------------------
// Procedure: unmuteRec
// on receiving SPEECH_PAUSE = FALSE we unmute speech rec

void SpeechRec::unmuteRec()
{
  m_recog->jconf->preprocess.level_coef = 1.0f;
  m_recog->adin->level_coef = 1.0f;
  m_pause_state = "FALSE";
}

//---------------------------------------------------------
// Procedure: statusRecStart
// dummy functions that can leverage Julius Speech Rec
// status options

void SpeechRec::statusRecStart(Recog *recog, void *dummy)
{
}

//---------------------------------------------------------
// Procedure: outputResult
// callback function for Julius speech recognition
// to output the resulting sentences

void SpeechRec::outputResult(Recog *recog, void *dummy)
{
  int i,j;
  int len;
  WORD_INFO *winfo;
  WORD_ID *seq;
  int seqnum;
  int n;
  Sentence *s;
  RecogProcess *r;
  HMM_Logical *p;
  SentenceAlign *align;

  //All recognition results are stored at each rcognition process instance
  for(r = recog->process_list; r; r = r->next) {
    //skip if the process is not alive
    if (!r->live) {
      continue;
    }

    //results are in r->result see recog.h for details
    if(r->result.status < 0)  {
      //respond bases on status code
      switch(r->result.status) {
      case J_RESULT_STATUS_REJECT_POWER:
	      m_message_lock.Lock();
        m_errors.push("Rejected by Power"); 
        m_message_lock.UnLock();
 //"<input rejected by power>"
	break;
      case J_RESULT_STATUS_TERMINATE:
        m_message_lock.Lock();
        m_errors.push("Terminated by Request"); 
        m_message_lock.UnLock();
//"<input terminated by request>"
	break;
      case J_RESULT_STATUS_ONLY_SILENCE:
        m_message_lock.Lock();
        m_errors.push("Only Silence");
        m_message_lock.UnLock();
//"<input rejected by decoder (silence input result)>"
	break;
      case J_RESULT_STATUS_REJECT_GMM:
        m_message_lock.Lock();
        m_errors.push("Rejected by GMM");
        m_message_lock.UnLock();
        //"<input rejected by GMM>"
	break;
      case J_RESULT_STATUS_REJECT_SHORT:
        m_message_lock.Lock();
        m_errors.push("Rejected by Short Input");
        m_message_lock.UnLock();
        //"<input rejected by short input>"
	break;
      case J_RESULT_STATUS_FAIL:
        m_message_lock.Lock();
        m_errors.push("Search Failed");
        m_message_lock.UnLock();
        //"<search failed>"
	break;
      }

      m_message_lock.Lock();
      m_errors.push("Generic Julius Recognition Error"); 
      m_message_lock.UnLock();
      //continue to next process instance
      continue;
    }

    //output results for all the obtained sentences
    winfo = r->lm->winfo;

    for( n = 0; n < r->result.sentnum; n++) {
      s = &(r->result.sent[n]);
      seq = s->word;
      seqnum = s->word_num;

      //output word sequence like Julius does
      std::stringstream ss;

      for(i=0 ; i < seqnum; i++) {
	std::string htmp = winfo->woutput[seq[i]];
	if (!wordValid(htmp)) {
	  continue;
	}
	if(!ss.str().empty()) {
	  ss <<" ";
	}
	ss << winfo->woutput[seq[i]];
      }
	
      std::string sentence = ss.str();

      //Mutex locks to make transfer of messages safe to SpeechRec class
      m_message_lock.Lock();
      m_messages.push(sentence);

      //AppCasting score information
      std::stringstream score_info;

      score_info << "sentence= " << sentence;
      score_info << ", confidencescores=";
      //confidence scores
      for(i=0; i <seqnum; i++) {
        score_info << s->confidence[i];
        if(i!=seqnum-1){
          score_info << ":"; //separate confidence scores
        }
      }
      //AM and LM scores
      score_info << ", score" << (n+1) << "= " << s->score;

      if( r->lmtype == LM_PROB) {
	score_info << " (AM= " << s->score_am << " LM= " << s->score_lm;
      }
      if( r->lmtype == LM_DFA) {
	//if this uses DFA grammar
	//output which grammar the hypothesis belongs to when using multiple grammars
	if( multigram_get_all_num(r->lm) > 1) {
	  score_info << " grammar" << (n+1) << ": " << s->gram_id;
	}
      }
	
      //Keep scores for AppCasting
      m_scores.push(score_info.str()); 
      m_message_lock.UnLock();
    }
  }
}

//---------------------------------------------------------
// Procedure: handleJuliusConf
// given a filename from .moos file attempts to initialize
// a Julius Speech Rec instatiation
// once setup is complete the loop is started in its own
// thread

bool SpeechRec::handleJuliusConf(std::string fileName) 
{
  //Have been given string of filename in fileName
  char * cstr = (char*)fileName.c_str();
  //load the jconf
  m_jconf = j_config_load_file_new(cstr);

  //check to see if loading jconf worked
  if(m_jconf == NULL) { //did not work :(
    m_state = ERROR_CONFIG_FILE;
    reportConfigWarning("JULIUS ERROR: UNABLE TO READ GIVEN CONFIG FILE: " + fileName);
    return false; 
  }

  //keep file name for appcast output
  m_julius_configuration = fileName;

  //Set the Microphone as input device
  m_jconf->input.speech_input = SP_MIC;
  //jconf->input.speech_input = SP_STDIN;
  //Create recognition instance of julius

  m_recog = j_create_instance_from_jconf(m_jconf);

  //check to see if creating recognition with julius worked
  if(m_recog == NULL) { //did not work :(
    m_state = ERROR_CREATE_JULIUS;
    reportRunWarning("JULIUS ERROR: UNABLE TO CREATE JULIUS INSTANCE\n");
    return false;
  }

  //Add callbacks for Julius
  callback_add(m_recog, CALLBACK_EVENT_SPEECH_READY, statusRecReady, NULL);
  callback_add(m_recog, CALLBACK_EVENT_SPEECH_START, statusRecStart, NULL);
  callback_add(m_recog, CALLBACK_RESULT, outputResult, NULL);
  //next one is included just in case it is needed
  //callback_add(recog, CALLBACK_PAUSE_FUNCTION, status_paused_wait, NULL);

  //Initialize audio input device
  //ad-in thread starts at this time for microphone
  if(j_adin_init(m_recog) == FALSE) { //audio init failed :(
    m_state = ERROR_AUDIO_INIT;
    reportRunWarning("JULIUS ERROR: UNABLE TO INIT AUDIO CAPTURE\n");
    return false;
  }

  if(m_julius_debug) {
    j_recog_info(m_recog);
  }
  
  //What state is the stream in?
  switch(j_open_stream(m_recog, NULL)) {
  case 0:
    break;
  case -1:
    m_state = ERROR_AUDIO_INPUT;
    reportRunWarning("JULIUS ERROR: ERROR IN AUDIO INPUT STREAM\n");
    return false;
  case -2:
    m_state = ERROR_AUDIO_START;
    reportRunWarning("JULIUS ERROR: FAILED TO START AUDIO INPUT STREAM\n");
    return false;
  }

  //This function is blocking and is placed in own thread
  m_t = new CMOOSThread();
  
  bool threadCreated = m_t->Initialise(startJRecognize, this);

  //Handle poor thread creation  
  if(threadCreated == FALSE) {
    m_state = ERROR_RECOG_LOOP;
    reportRunWarning("JULIUS ERROR: RECOGNITION LOOP FAILURE\n");
    j_close_stream(m_recog);
    j_recog_free(m_recog);
    m_recog = NULL;
    return false;
  }
  else {
    m_t->Start();
  }

  //have start state from .moos file influence here
  if(m_start_state == "PAUSED") {
        muteRec();
  }
  else {
  unmuteRec();
}
  
  return true;

}

//---------------------------------------------------------
// Procedure: handleStartState
// given a config from .moos file named StartState
// that is either 'Active' or 'Paused' determines how
// Julius Speech Rec will initially start 

bool SpeechRec::handleStartState(std::string startState) 
{
  //convert startState to all caps for ease of use
  //  std::string upperCaseStartState = MOOSToUpper(startState);
  MOOSToUpper(startState);

  //default is active -- set in constructor

  //return true if either 'PAUSED' or 'ACTIVE
  if(startState == "ACTIVE" || startState == "PAUSED") {
    m_start_state = startState;
    return true;
  }
  
  //otherwise it is a malformed value - return false
  return false;

}

//---------------------------------------------------------
// Procedure: internalStartJRecognize
// wrapper around stream initialization
// used for Boolean checking

bool SpeechRec::internalStartJRecognize()
{
  if(j_recognize_stream(m_recog) == -1)
    return false;
  else
    return true;
}

//---------------------------------------------------------
// Procedure: startJRecognize
// used to initialize recognition loop

bool SpeechRec::startJRecognize(void* param)
{
  SpeechRec* me = (SpeechRec*)param;
  return me->internalStartJRecognize();
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool SpeechRec::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  STRING_LIST sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());
  
   
  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig     = *p;
    string sLine     = *p;
    string sVarName  = MOOSChomp(sLine, "=");
    sLine = stripBlankEnds(sLine);
  
    bool handled = false;
    sVarName = tolower(sVarName);
    if(MOOSStrCmp(sVarName, "JuliusConf")) {
      if(!strContains(sLine, " ")) {
	string tmp = stripBlankEnds(sLine);
	//std::vector<std::string> messages;
	handled = handleJuliusConf(tmp);
      }
    }
    else if(MOOSStrCmp(sVarName, "StartState")) {
      if(!strContains(sLine, " ")) {
	string tmp = stripBlankEnds(sLine);
	//std::vector<std::string> messages;
	handled = handleStartState(tmp);
      }
    }
 
 
    if(!handled)
      reportUnhandledConfigWarning(orig);
  }
  
  registerVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void SpeechRec::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
  Register("SPEECH_PAUSE", 0);
  Register("SPEECH_ACTIVE",0);
                              
  // Register("FOOBAR", 0);  
}

//------------------------------------------------------------
// Procedure: buildReport()

bool SpeechRec::buildReport() 
{
  m_msgs << "============================================ \n";
  m_msgs << "JuliusConf = " <<   m_julius_configuration << endl;

  if(m_pause_state == "TRUE") {
    m_msgs << "Recognizer Paused" << endl;
  }
  else if(m_pause_state == "FALSE") {
    m_msgs << "Recognizer Active" << endl;
  }
  //ACTable actab(4);
  //actab << "Alpha | Bravo | Charlie | Delta";
  //actab.addHeaderLines();
  //actab << "one" << "two" << "three" << "four";
  //m_msgs << actab.getFormattedString();
  //m_msgs<< endl<< "Last Recognized Sentence: "<< m_last_notified <<endl;
  
  return(true);
}
