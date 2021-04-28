/****************************************************************/
/*   NAME: Caileigh Fitzgerald                                             */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: LEDInfoBar_Info.cpp                               */
/*   DATE: May 5th 2018                                       */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "LEDInfoBar_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The iLEDInfoBar application is used for the LED strip in      ");
  blk("  the human operated kayak (Mokai).                             ");
  blk("  It displays information relevant to the user during the game. ");
  blk("    ex: if the user has been tagged or is in the \'flag zone\'. ");
  blk("    team colors are configured in the .moos file.               ");
  blk("                                                                ");
}

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: iLEDInfoBar file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch iLEDInfoBar with the given process name         ");
  blk("      rather than iLEDInfoBar.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of iLEDInfoBar.        ");
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
  blu("iLEDInfoBar Example MOOS Configuration                          ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = iLEDInfoBar                                     ");
  blk("{                                                               ");
  blk("  AppTick    = 4                                                ");
  blk("  CommsTick  = 4                                                ");
  blk("  TEAM_COLOR = \"blue\"                                         ");
  blk("  BAUDRATE   = 9600                                             ");
  blk("  PORT       = /dev/cu.usbmodemFA131                            ");
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
  blu("iLEDInfoBar INTERFACE                                    ");
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
  blk("  This app does not publish.                                    ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("iLEDInfoBar", "gpl");
  exit(0);
}

