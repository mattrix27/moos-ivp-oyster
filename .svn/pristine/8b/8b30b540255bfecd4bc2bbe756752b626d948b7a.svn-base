/****************************************************************/
/*   NAME: Michael "Misha" Novitzky                             */
/*   Original NAME: Oliver MacNeely                             */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: Record_Info.cpp                                      */
/*   DATE: March 28th 2018                                      */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "Record_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("--------------------------------------------------------------  ");
  blk("  The pRecord application is used for recording audio from      ");
  blk("  a microphone to a local wave file.                            ");
  blk("                                                                ");
  blk("                                                                ");
  blk("                                                                ");
  blk("                                                                ");
}

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: pRecord file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch pRecord with the given process name         ");
  blk("      rather than pRecord.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of pRecord.        ");
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
  blu("pRecord Example MOOS Configuration                              ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = pRecord                                         ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("                                                                "); 
  blk("//Set the MOOS Variable and Value for which to record           ");
  blk("//If not specified, defaults to MOOS_VAR_WATCH = SPEECH_BUTTON  ");
  blk("// and MOOS_VALUE_WATCH = TRUE                                  ");
  blk("  MOOS_VAR_WATCH = TEST_SPEECH                                  ");
  blk("  MOOS_VALUE_WATCH = FALSE                                      ");
  blk("                                                                ");
  blk("//Set the prefix of .wave files to be saved                     ");
  blk("//If not specified, defaults to \"file_\"                       ");
  blk("  SAVE_FILE_PREFIX = speech_rec_                                ");
  blk("                                                                ");
  blk("//Set directory save prefix                                     ");
  blk("//pRecord saves the directory relative to execution of the      ");
  blk("//program with date and time appended.                          ");
  blk("//If not specified, defaults to \"pRecord_saves\"               ");
  blk("  SAVE_DIR_PREFIX = SPEECH_SAVE                                 ");
  blk("                                                                ");
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
  blu("pRecord INTERFACE                                               ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  By default subscribes to SPEECH_BUTTON                        ");
  blk("  Unless otherwise configured to watch for another variable in  ");
  blk("  .moos file with MOOS_VAR_WATCH                                ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("AUDIO_FILE_SAVED -folder and name of latest saved audio file    ");
  blk("                                                                ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("pRecord", "gpl");
  exit(0);
}

