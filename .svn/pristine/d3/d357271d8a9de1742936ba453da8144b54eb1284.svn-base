/*
 * os5000Info.cpp
 *
 *  Created on: July 22, 2014
 *      Author: Alon Yaari
 */

#include "os5000Info.h"

#include <cstdlib>
#include <iostream>
#include "os5000Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

void showSynopsis()
{
    blk("SYNOPSIS:");
    blk("------------------------------------");
    blk("  Receives sentences from an Ocean-Server OS5000 digital compass over a");
    blk("  serial connection. Sentences are parsed and extracted data is published.");
    blk("  This application assumes that the OS5000 unit was preconfigured to output");
    blk("  Format Type 0x01, '$C' messages. See the user manual for details. Onboard");
    blk("  non-volatile RAM retains configuration data when device is powered off.");
    blk("  Therefore once the unit is configured it does not require reconfiguration.");
    blk("  $C messages are parsed and published into the following MOOS messages:");
    blk("     prefix_HEADING     Heading in degrees from magnetic north (plus offset)");
    blk("     prefix_PITCH       Pitch angle in degrees from horizontal");
    blk("     prefix_ROLL        Roll angle in degrees from horizontal");
    blk("     prefix_TEMPERATURE Temperature reading if the compass circuitry in C");
    blk("  where prefix is user-defined in the mission file, default prefix='COMPASS_'.");
}

void showHelpAndExit()
{
    blk("");
    blu("============================================================================");
    blu("Usage: iOS5000 file.moos [OPTIONS]");
    blu("============================================================================");
    blk("");
    showSynopsis();
    blk("");
    blk("Options:");
    mag("  --example, -e");
    blk("      Display example MOOS configuration block.");
    mag("  --help, -h");
    blk("      Display this help message.");
    mag("  --interface, -i");
    blk("      Display MOOS publications and subscriptions.");
    blk("");
    blk("Note: If argv[2] does not otherwise match a known option, then it will be");
    blk("      interpreted as a run alias. This is to support pAntler conventions.");
    blk("");
    exit(0);
}

void showExampleConfigAndExit()
{
//     0         1         2         3         4         5         6         7
//     01234567890123456789012345678901234567890123456789012345678901234567890123456789
  blk("");
  blu("============================================================================");
  blu("iOS5000 Example MOOS Configuration");
  blu("============================================================================");
  blk("");
  blk("ProcessConfig = iOS5000");
  blk("{");
  blk("  AppTick     = 10");
  blk("  CommsTick   = 10");
  blk("");
  blk("  PREFIX      = COMPASS_       // Prepends this to all output message names");
  blk("  PORT        = /dev/ttyACM1   // Fully-qualified path to the serial port");
  blk("  SPEED       = 19200          // Alternate form of BAUDRATE");
  blk("  BAUDRATE    = 19200          // Serial port baud rate");
  blk("  PREROTATION = 0.0            // Alternate form of MAG_VAR");
  blk("  MAG_VAR     = 0.0            // Magnetic variation in degrees to offset");
  blk("                               // heading so it reports relative to true N");
  blk("}");
  blk("");
  exit(0);
}

void showInterfaceAndExit()
{
  blk("");
  blu("============================================================================");
  blu("iOS5000 INTERFACE");
  blu("============================================================================");
  blk("");
  showSynopsis();
  blk("");
  blk("SUBSCRIPTIONS:");
  blk("------------------------------------");
  blk("  none");
  blk("");
  blk("PUBLICATIONS:");
  blk("------------------------------------");
  blk("  [prefix]_HEADING double  Heading in degrees from magnetic north, plus offset");
  blk("  [prefix]_PITCH   double  Degrees of tilt left or right");
  blk("  [prefix]_ROLL    double  Degrees of tilt forward or back");
  blk("  [prefix]_TEMPERATURE double  Temp in Celsius at the device.");
  blk("");
  exit(0);
}

