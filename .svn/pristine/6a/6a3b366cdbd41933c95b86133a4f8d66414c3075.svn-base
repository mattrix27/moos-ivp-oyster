/*
 * moosJoyInfo.cpp
 *
 *  Created on: Sep 24 2015
 *      Author: Alon Yaari
 */

#include <cstdlib>
#include <iostream>
#include "ColorParse.h"
#include "ReleaseInfo.h"
#include "moosJoyInfo.h"

using namespace std;

void showSynopsis()
{
  blk("SYNOPSIS:");
  blk("------------------------------------");
  blk(" Reads a joystick and publishes axis and button info as MOOS messages.");
  blk(" Designed to be cross-platform and joystick-agnostic. Axis output is raw,");
  blk(" there are no dead zones or mapping of values. Button output is published");
  blk(" only on change of press status.");
}

void showHelpAndExit()
{
  blk("");
  blu("============================================================================");
  blu("Usage: iJoystick file.moos [OPTIONS]");
  blu("============================================================================");
  blk("");
  showSynopsis();
  blk("");
  blk("Options:                                                                    ");
  mag("  --example, -e                                                             ");
  blk("      Display example MOOS configuration block.                             ");
  mag("  --help, -h                                                                ");
  blk("      Display this help message.                                            ");
  mag("  --interface, -i                                                           ");
  blk("      Display MOOS publications and subscriptions.                          ");
  blk("");
  blk("Note: If argv[2] does not otherwise match a known option, then it will be   ");
  blk("      interpreted as a run alias. This is to support pAntler conventions.   ");
  blk("");
  exit(0);
}

void showExampleConfigAndExit()
{
//     0         1         2         3         4         5         6         7
//     01234567890123456789012345678901234567890123456789012345678901234567890123456789
  blk("");
  blu("============================================================================");
  blu("iJoystick Example MOOS Configuration");
  blu("============================================================================");
  blk("");
  blk("ProcessConfig = iJoystick");
  blk("{");
  blk("  // Higher tick values makes joystick more responsive");
  blk("  // Lower tick values can result in response lag");
  blk("  AppTick    = 20");
  blk("  CommsTick  = 20");
  blk("");
  blk("  JoystickID    = 0       // If more than one joystick is connected, this is the");
  blk("                          //   0-based index ID of the joystick to report on.");
  blk("                          //   Default is 0.");
  blk("  Output_Prefix = JOY_    // All output for this joystick will be published");
  blk("                          //   with this prefix on the message names.");
  blk("                          //   Default is JOY_");
  blk("  Dependent     = 0, 1    // For joysticks that output axes based on circular");
  blk("                          //   distance, this relates to two axes. Order is");
  blk("                          //   not important. If defined, axes will publish a");
  blk("                          //   second message including values for both axes.");
  blk("  ID_by_Button  = 0       // Only relevant when more than one controller is present.");
  blk("                          //   REQUIRED when more than one controller is present.");
  blk("                          //   ID number of the button that identifies the controller");
  blk("                          //   this instance of iJoystick will interface with.");
  blk("                          //   On startup, the application will wait until the specified");
  blk("                          //   button is pressed before publishing any output.");
  blk("}");
  blk("");
  exit(0);
}

void showInterfaceAndExit()
{
	  blk("");
  blu("============================================================================");
  blu("iJoystick INTERFACE                                                           ");
  blu("============================================================================");
  blk("");
  showSynopsis();
  blk("");
  blk("SUBSCRIPTIONS:");
  blk("------------------------------------ ");
  blk("  None.");
  blk("");
  blk("PUBLICATIONS:                                                               ");
  blk("------------------------------------                                        ");
  blk("  // [prefix] is defined in the Output_predix mission file parameter");
  blk("  // [X]      is the channel number for the current joystick");
  blk("  [prefix]_AXIS_COUNT    integer   Number of valid axes current joystick reports");
  blk("  [prefix]_AXIS_[X]      integer   Axis position value published for each valid joystick axis.");
  blk("  [prefix]_AXIS_[X]_DEP  string    If an axis has a dependency, this message is published with");
  blk("                                     format 'axis_val, dep_axis_val'");
  blk("  [prefix]_BUTTON_COUNT  integer   Number of valid buttons current joystick reports");
  blk("  [prefix]_BUTTON_[X]    string    Button status published for each valid joystick button.");
  blk("                                     ONLY PUBLISHED WHEN the button status changes.");
  blk("                                     Pressed:      DOWN");
  blk("                                     Not pressed:  UP");
  blk("                                     Example:      JOY2_BUTTON_6 = UP");
  blk("");
  exit(0);
}
























//
