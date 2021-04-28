/************************************************************/
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: main_3_0.cpp                                    */
/*    DATE: August 13th, 2015                               */
/*    DATE: August 17th, 2017                               */
/*    DATE: January 10th, 2019                              */
/************************************************************/

#include <string>
#include <queue>
#include "MBUtils.h"
#include "ColorParse.h"
#include "SpeechRec_3_0.h"
#include "SpeechRec_Info_3_0.h"

using namespace std;
//These following variables are for Julius Speech Rec
//Callback function which assigns static variable
//to SpeechRec class
std::queue<std::string> SpeechRec::m_messages;
std::queue<std::string> SpeechRec::m_scores;
std::queue<std::string> SpeechRec::m_errors;
CMOOSLock SpeechRec::m_message_lock;

int main(int argc, char *argv[])
{
 
  string mission_file;
  string run_command = argv[0];

  for(int i=1; i<argc; i++) {
    string argi = argv[i];
    if((argi=="-v") || (argi=="--version") || (argi=="-version"))
      showReleaseInfoAndExit();
    else if((argi=="-e") || (argi=="--example") || (argi=="-example"))
      showExampleConfigAndExit();
    else if((argi == "-h") || (argi == "--help") || (argi=="-help"))
      showHelpAndExit();
    else if((argi == "-i") || (argi == "--interface"))
      showInterfaceAndExit();
    else if(strEnds(argi, ".moos") || strEnds(argi, ".moos++"))
      mission_file = argv[i];
    else if(strBegins(argi, "--alias="))
      run_command = argi.substr(8);
    else if(i==2)
      run_command = argi;
  }
  
  if(mission_file == "")
    showHelpAndExit();

  cout << termColor("green");
  cout << "uSpeechRec launching as " << run_command << endl;
  cout << termColor() << endl;

  SpeechRec SpeechRec;

  SpeechRec.Run(run_command.c_str(), mission_file.c_str());
  
  return(0);
}

