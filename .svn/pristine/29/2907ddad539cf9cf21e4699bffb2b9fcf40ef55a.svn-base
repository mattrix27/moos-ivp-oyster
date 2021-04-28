/****************************************************************/
/*   NAME: Michael "Misha" Novitzky                             */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: DialogManager_Info_5_0.cpp                           */
/*   DATE: August 17th, 2015                                    */
/*   UPDATED: Aug. 10 2016                                      */
/*   UPDATED: July 28 2017                                      */
/*   UPDATED: January 11 2019                                   */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "DialogManager_Info_5_0.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The uDialogManager_5_0 application is used for controlling the    "); 
  blk("  dialog between speech recognition and the user.  It's main    ");
  blk("  function is to correct for errors in speech.              ");
  blk("                                                                ");
}

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: uDialogManager v5.0 file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch uDialogManager with the given process name         ");
  blk("      rather than uDialogManager.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of uDialogManager.        ");
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
  blu("uDialogManager v5.0 Example MOOS Configuration                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = uDialogManager                                  ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("  ");
  blk("  //can reject sentences based on word confidence scores        ");
  blk("  //threshold value range (0,-1.0]                              ");
  blk("  //if not specified, reverts to accepting most likely sentence without considering word confidence ");
  blk("  confidence_thresh = 0.7                                       ");
  blk("  ");
  blk("  //indicate whether to use local text-to-speech (TTS) or       ");
  blk("  //pre-recorded wave files. Options are yes or no              ");
  blk("  Use_Wav_Files=Yes                                             ");
  blk("  ");
  blk("  //list of vars and values to publish given speech sentence    ");
  blk("  //var-value pairs are '+' separated                           ");
  blk("  sentence = Arnold_Deploy : DEPLOY = true + MOOS_MANUAL_OVERRIDE = false + RETURN = false");
  blk("  ");
  blk("  //quotes around a string for a value can be used              ");
  blk("  sentence = Arnold_Follow : NODE_MESSAGE_LOCAL = \"src_node=mokai,dest_node=betty,var_name=TRAIL,string_val=true\" ");
  blk("                                                                ");
  blk("  //sentence acknowledgement options can be specified after a sentence inside of curly braces '{' and '}' ");
  blk("  //in order to skip acknowledgment and variable-value pairs post immediately "); 
  blk("  sentence = grab { NOCONFIRM } : FLAG_GRAB_REQUEST = ``vname = $(VNAME)'' ");
  blk("                                                                ");
  blk("  //the user can specify words for confirming or declining commands withinthe curly braces ");
  blk("  sentence = tag { CONFIRM=verify | DECLINE=ignore }  : TAG_REQUEST = ``vname = $(VNAME)'' ");
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
  blu("uDialogManager 5.0 INTERFACE                                    ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  SPEECH_RECOGNITION_SENTENCE = produced by speech recognition    ");
  blk("  SPEECH_RECOGNITION_SCORE = produced by speech recognition with confidence scores   ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  SPEECH_COMMANDED   = an acknowledged command                    ");
  blk("  DIALOG_ERROR = posted when a sentence is rejected using word confidence score threshold");
  blk(" ");
  blk("  SAY_MOOS           = sent to iSay for spoken dialogue or use of wave files to user ");
  blk(" ");
  blk("  any other var value pair publications can be defined per speech rec sentence in the .moos file ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("uDialogManager 5.0", "gpl");
  exit(0);
}

