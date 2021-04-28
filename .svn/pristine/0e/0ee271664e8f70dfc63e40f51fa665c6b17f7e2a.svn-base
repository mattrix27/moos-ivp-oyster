/****************************************************************/
/*   NAME: Caileigh Fitzgerald                                             */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: LEDInterpreter_Info.cpp                               */
/*   DATE: Dec 29th 1963                                        */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "LEDInterpreter_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The iLEDInterpreter application is used as an interpreter     ");
  blk("  for iLEDInfoBar. Since the variables published through        ");
  blk("  uFld--Manager apps have a lot of complexity, iLEDInterpreter  ");
  blk("  simplifies them and publishes for iLEDInfoBar.                ");
  blk("                                                                ");
  blk("  The interpreters ONLY job is to;                              ");
  blk("   - Translate variables published by uFld--Manager             ");
  blk("   - Immediately publish the simplified vars to the MOOSDB      ");
  blk("                                                                ");
  blk("  See iLEDInfoBar -i for more info.                             ");
  blk("                                                                ");
}

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: iLEDInterpreter file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch iLEDInterpreter with the given process name         ");
  blk("      rather than iLEDInterpreter.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of iLEDInterpreter.        ");
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
  blu("iLEDInterpreter Example MOOS Configuration                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = iLEDInterpreter                              ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
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
  blu("iLEDInterpreter INTERFACE                                    ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  NODE_MESSAGE = src_node=alpha,dest_node=bravo,var_name=FOO,   ");
  blk("                 string_val=BAR                                 ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  TAGGED        = (active || off || blinking)                          ");
  blk("  IN_TAG_RANGE  = (active || off || blinking)                          ");
  blk("  IN_FLAG_ZONE  = (active || off || blinking)                          ");
  blk("  HAVE_FLAG     = (active || off || blinking)                          ");
  blk("  OUT_OF_BOUNDS = (active || off || blinking)                          ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("iLEDInterpreter", "gpl");
  exit(0);
}

