/****************************************************************/
/*   NAME: Michael "Misha" Novitzky                             */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: SpeechRec_Info_3_0.cpp                               */
/*   DATE: August 13th, 2015                                    */
/*   DATE: August 17th, 2017                                    */
/*   DATE: January 10th, 2019                                   */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "SpeechRec_Info_3_0.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The uSpeechRec application is used for initializing and       ");
  blk("  running the Julius open-source speech recognition software. ");
 }

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: uSpeechRec file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch uSpeechRec with the given process name         ");
  blk("      rather than uSpeechRec.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of uSpeechRec.        ");
  blk("                                                                ");
  blk("Note: If argv[2] does not otherwise match a known option,       ");
  blk("      then it will be interpreted as a run alias. This is       ");
  blk("      to support pAntler launching conventions.                 ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showExampleConfigAndExit

void showExampleConfigAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("uSpeechRec Example MOOS Configuration                           ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = uSpeechRec                                      ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("  JuliusConf = Alpha.jconf                                      ");
  blk("  //StartState: Default is recognition starts in 'Active' state ");
  blk("  //can be set to start in a 'Paused' state                     ");
  blk("  //will then need to be unpaused by publishing FALSE to        "); 
  blk("  //SPEECH_PAUSE to be put back into an 'Active' state          ");
  blk("  //SPEECH_ACTIVE has the same function but is reversed.        ");                                
  blk("  StartState = Paused                                           ");
  blk("}                                                               ");
  blk("                                                                ");
  exit(0);
}


//----------------------------------------------------------------
// Procedure: showInterfaceAndExit

void showInterfaceAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("uSpeechRec INTERFACE                                            ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("   SPEECH_PAUSE = TRUE/FALSE to pause/unpause speech recognition");
  blk("   SPEECH_ACTIVE = FALSE/TRUE to pause/unpause speech recognition");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  SPEECH_RECOGNITION_SENTENCE = string sentence produced by Julius");
  blk("  SPEECH_RECOGNITION_SCORE = string sentence and scores produced by Julius");
  blk("  SPEECH_RECOGNITION_ERROR = reason why Julius does not produce sentence");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("uSpeechRec_3_0", "gpl");
  exit(0);
}

