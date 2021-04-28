/****************************************************************/
/*   NAME: Mohamed Saad Ibn Seddik                                             */
/*   ORGN: MIT                                     */
/*   FILE: RangeEvent_Info.cpp                               */
/*   DATE: 2016/03/15                                        */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "RangeEvent_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The pRangeEvent application is used to publishes a variable   ");
  blk("  defined under \"event_var\" in the configuration file         ");
  blk("  whenever another vehicle (based on NODE_REPORT) is whitin     ");
  blk("  the predefined range.                                         ");
  blk("                                                                ");
}

//----------------------------------------------------------------
// Procedure: showHelpAndExit

void showHelpAndExit()
{
  blk("                                                                ");
  blu("=============================================================== ");
  blu("Usage: pRangeEvent file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch pRangeEvent with the given process name         ");
  blk("      rather than pRangeEvent.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of pRangeEvent.        ");
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
  blu("pRangeEvent Example MOOS Configuration                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = pRangeEvent                              ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("                                                                ");
  blk("  // Range within which the event is triggered");
  blk("  min_range = 0 // default");
  blk("  max_range = 10 // default");
  blk("                                                                ");
  blk("  ignore_group = red // this group will be ignored when within range");
  blk("                                                                ");
  blk("  // Event variables:");
  blk("  // Dynamic values options");
  blk("  //          ($[SELFVNAME], $[SELFVX], $[SELFVY],");
  blk("  //          $[SELFSPEED], $[SELFHEADING],");
  blk("  //          $[TARGVNAME], $[TARGVX], $[TARGVY],");
  blk("  //          $[TARGSPEED], $[TARGHEADING],");
  blk("  //          $[RANGE], $[TIME])");
  blk("  event_var = TAG_REQUEST=vname=$[TARGVNAME]");
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
  blu("pRangeEvent INTERFACE                                    ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  NODE_REPORT ");
  blk("              ");
  blk("  NODE_REPORT_LOCAL ");
  blk("              ");
  blk("  DB_UPTIME ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  Publishes the a message under the name given by event_var in  ");
  blk("  the configuration file. (more info with the option -e)");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("pRangeEvent", "mit");
  exit(0);
}
