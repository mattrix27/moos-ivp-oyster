/****************************************************************/
/*   NAME:                                              */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: ZoneEvent_Info.cpp                               */
/*   DATE: Dec 29th 1963                                        */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "ZoneEvent_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The uFldZoneEvent application is used for broadcasting a      ");
  blk("  variable each time a vehicle enters the predefined area.      ");
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
  blu("Usage: uFldZoneEvent file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch uFldZoneEvent with the given process name         ");
  blk("      rather than uFldZoneEvent.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of uFldZoneEvent.        ");
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
  blu("uFldZoneEvent Example MOOS Configuration                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = uFldZoneEvent                              ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("");
  blk("  // dynamic values ($[VNAME], $[GROUP], $[TIME], $[VX], $[VY])");
  blk("  // zone name should correspond to the vehicle's group name to be active");
  blk("  zone_info = name=blue # pts={-51.05,-70.72:-52.96,-64.84:-57.96,-61.21:-64.14,-61.21:-69.14,-64.84:-71.05,-70.72:-69.14,-76.60:-64.14,-80.23:-57.96,-80.23:-52.96,-76.60}");
  blk("  zone_info = name=blue # post_var = UNTAG_REQUEST=vname=$[VNAME]");
  blk("  zone_info = name=blue # post_var = UFZE_DBG=vname=$[VNAME]");
  blk("  zone_info = name=blue # group = blue // mandatory");
  blk("  zone_info = name=blue # viewable=true  // default is true");
  blk("  zone_info = name=blue # color=blue  // default is orange");
  blk("  zone_info = name=red  # pts={71.84,-13.20:69.93,-7.32:64.93,-3.69:58.75,-3.69:53.75,-7.32:51.84,-13.20:53.75,-19.08:58.75,-22.71:64.93,-22.71:69.93,-19.08}");
  blk("  zone_info = name=red  # post_var = UNTAG_REQUEST=vname=$[VNAME]");
  blk("  zone_info = name=red  # viewable=true # color=red # group = red");
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
  blu("uFldZoneEvent INTERFACE                                    ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  NODE_REPORT   ");
  blk("                                                                ");
  blk("  NODE_REPORT_LOCAL   ");
  blk("                                                                ");
  blk("  DB_UPTIME   ");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  Publishes the a message under the name given by post_var in  ");
  blk("  the configuration file. (more info with the option -e)");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("uFldZoneEvent", "mit");
  exit(0);
}
