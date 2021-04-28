/*
 * OysterRCInfo.cpp
 *
 *  Created on: Sep 30, 2015
 *      Author: Alon Yaari
 */

#include "OysterRCInfo.h"

#include <cstdlib>
#include <iostream>
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

void showSynopsis()
{
  blk("SYNOPSIS:");
  blk("------------------------------------");
  blk("   Publishes messages based on a range of input values or as a result of being");
  blk(" triggered. For a RANGE, output values are mapped based on a definition of the");
  blk(" input range, normalization parameters, and the output range. For a TRIGGER,");
  blk(" output is a single defined value published whenever the input message changes");
  blk(" to the defined trigger value.");
  blk("   The main purpose of pOysterRC is to provide convert raw joystick readings from");
  blk(" the iJoystick application into values that are usable for pOysterESC and flipping");
  blk(" Joystick axes are the input RANGE and joystick buttons are the input TRIGGERs.");
  blk(" This data flow can be used to convert any numerical input range into any");
  blk(" numerical output range and any trigger, not just buttons.");
  blk("");
}

void showHelpAndExit()
{
  blk("");
  blu("============================================================================");
  blu("Usage: pOysterRC file.moos [OPTIONS]");
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
  blu("pOysterRC Example MOOS Configuration");
  blu("============================================================================");
  blk("");
  blk("ProcessConfig = pOysterRC");
  blk("{");
  blk("  AppTick    = 10");
  blk("  CommsTick  = 10");
  blk("");
  blk("  // RANGE = in_msg=, in_min=, in_max=, dead=, sat=, norm_min=, norm_max=, /");
  blk("  //         out_msg=, out_min=, out_max=, dep=, trig_msg=, trig_val=");
  blk("  //      IN_MSG   (string, required) Message name for incoming range values");
  blk("  //      IN_MIN   (double, required) Minimum expected value on the input message");
  blk("  //      IN_MAX   (double, required) Maximum expected value on the input message");
  blk("  //      NORM_MIN (double, optional) Minimum normalized value to map to output (default = -1.0)");
  blk("  //      NORM_MAX (double, optional) Maximum normalized value to map to output (default = 1.0)");
  blk("  //      OUT_MSG  (string, required) Mapped value published to this message");
  blk("  //      OUT_MIN  (double, required) Minimum value input range is mapped to");
  blk("  //      OUT_MAX  (double, required) Maximum value input range is mapped to");
  blk("  //      DEAD     (int,    optional) Percent to each side of 0 that reports 0 (default = 0.0");
  blk("  //      SAT      (int,    optional) Percent at each end that reports extreme value (def. = 0.0");
  blk("  //      DEP      (string, optional) Message name of dependent axis");
  blk("  //      TRIG_MSG (string, optional) Publish mapped value only when on this trigger message");
  blk("  //      TRIG_VAL (any,    required) Publish only when trig_msg has this value.");
  blk("  RANGE = in_msg=JOY_AXIS_0, in_min=-32768, in_max=32768, dead=5, sat=5, /");
  blk("            out_msg=DESIRED_RUDDER, out_min=-40, out_max=40, trig_msg=JOY_BUTTON_0, trig_val=DOWN");
  blk("  RANGE = in_msg=JOY_AXIS_1_DEP, in_min=-32768, in_max=32768, dead=5, sat=5, /");
  blk("            norm_min = 0.0, norm_max = -1.0, out_msg=DESIRED_THRUST, out_min=0, out_max=100");
  blk("");
  blk("  // TRIGGER = in_msg=w, trigger=x, out_msg=y, out_val=z");
  blk("  //      IN_MSG  (string, required) Message name for incoming switch value");
  blk("  //      TRIGGER (any,    required) When in_msg contents change to match this trigger,");
  blk("  //                                   the out_msg will be published. String/numeric agnostic.");
  blk("  //      OUT_MSG (string, required) Message name for resulting publication.");
  blk("  //      OUT_VAL (any,    required) Resulting publication posts this value.");
  blk("  //                                   If value is a numeric (within '+-.01234567889'),");
  blk("  //                                   published message is a double. Otherwise, a");
  blk("  //                                   string is published. To publish a numeric as a");
  blk("  //                                   string, put the number in quotes.");
  blk("   TRIGGER   = in_msg=JOY_BUTTON_4, trigger=DOWN, out_msg=ALL_STOP, out_val=true");
  blk("}");
  blk("");
  exit(0);
}

void showInterfaceAndExit()
{
	  blk("");
  blu("============================================================================");
  blu("pOysterRC INTERFACE                                                           ");
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
  blk("  [out_msg]       The range or trigger out_val defined in the mission file");
  blk("                    One publication per definition.");
  blk("");
  exit(0);
}
























//
