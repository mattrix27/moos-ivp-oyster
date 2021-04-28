/****************************************************************/
/*   NAME: Michael "Misha" Novitzky                             */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: DialogManager_Info.cpp                               */
/*   DATE: August 17th, 2015y                                    */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "BotDialog_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The pBotDialog application is used for controlling the    "); 
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
  blu("Usage: uDialogManager file.moos [OPTIONS]                   ");
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
  blu("uDialogManager Example MOOS Configuration                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = uDialogManager                              ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("  ");
  blk("  //list of vars and values to publish given speech sentence    ");
  blk("  //var-value pairs are '+' separated                           ");
  blk("  sentence = Arnold_Deploy : DEPLOY = true + MOOS_MANUAL_OVERRIDE = false + RETURN = false");
  blk("  ");
  blk("  //quotes around a string for a value can be used              ");
  blk("  sentence = Arnold_Follow : NODE_MESSAGE_LOCAL = \"src_node=mokai,dest_node=betty,var_name=TRAIL,string_val=true\" ");
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
  blu("uDialogManager INTERFACE                                    ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  SPEECH_RECOGNITION_SENTENCE = produced by speech recognition    ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  SPEECH_COMMANDED   = an acknowledged command                    ");
  blk("  SAY_MOOS           = sent to iSay for spoken dialogue to user                  ");
  blk(" ");
  blk("  any other var value pair publications can be defined per speech rec sentence in the .moos file ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("uDialogManager", "gpl");
  exit(0);
}

