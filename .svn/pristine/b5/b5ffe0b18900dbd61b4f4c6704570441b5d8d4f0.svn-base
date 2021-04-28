/****************************************************************/
/*   NAME: Michael "Misha" Novitzky                             */
/*   Original NAME: Oliver MacNeely                             */
/*   ORGN: MIT Cambridge MA                                     */
/*   FILE: Comms_client_Info.cpp                               */
/*   DATE: Dec 29th 1963                                        */
/****************************************************************/

#include <cstdlib>
#include <iostream>
#include "Comms_client_Info.h"
#include "ColorParse.h"
#include "ReleaseInfo.h"

using namespace std;

//----------------------------------------------------------------
// Procedure: showSynopsis

void showSynopsis()
{
  blk("SYNOPSIS:                                                       ");
  blk("------------------------------------                            ");
  blk("  The pComms_client application is used for                     ");
  blk("  VOIP - in combination with a pComms_server and other          ");
  blk("  pComms_client applications.  Triggers sending audio           ");
  blk("  from the microphone via a specified MOOSDB variable.          ");
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
  blu("Usage: pComms_client file.moos [OPTIONS]                   ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("Options:                                                        ");
  mag("  --alias","=<ProcessName>                                      ");
  blk("      Launch pComms_client with the given process name         ");
  blk("      rather than pComms_client.                           ");
  mag("  --example, -e                                                 ");
  blk("      Display example MOOS configuration block.                 ");
  mag("  --help, -h                                                    ");
  blk("      Display this help message.                                ");
  mag("  --interface, -i                                               ");
  blk("      Display MOOS publications and subscriptions.              ");
  mag("  --version,-v                                                  ");
  blk("      Display the release version of pComms_client.        ");
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
  blu("pComms_client Example MOOS Configuration                        ");
  blu("=============================================================== ");
  blk("                                                                ");
  blk("ProcessConfig = pComms_client                                   ");
  blk("{                                                               ");
  blk("  AppTick   = 4                                                 ");
  blk("  CommsTick = 4                                                 ");
  blk("                                                                ");
  blk("//ClientSocket as integer                                       ");
  blk("  ClientSocket =  11112                                         ");
  blk("//ClientIP in string format                                     ");
  blk("  ClientIP = 192.168.1.50                                       ");
  blk("//ServerSocket as integer                                       ");
  blk("  ServerSocket = 11111                                          ");
  blk("//ServerIP in string format                                     ");
  blk("  ServerIP = 192.168.1.50                                       ");
  blk("                                                                ");
  blk("//Define MOOS Variable and Value                                ");
  blk("//to trigger sending audio to server                            ");
  blk("//if not specified, defaults to                                 ");
  blk("//MOOS Variable = \"SEND\"                                      ");
  blk("//Value = \"TRUE\"                                              ");
  blk("  SEND_VOICE_ON_VARNAME = SEND_VOICE                            ");
  blk("                                                                ");
  blk("  SEND_VOICE_ON_VALUE = TRUE                                    ");
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
  blu("pComms_client INTERFACE                                    ");
  blu("=============================================================== ");
  blk("                                                                ");
  showSynopsis();
  blk("                                                                ");
  blk("SUBSCRIPTIONS:                                                  ");
  blk("------------------------------------                            ");
  blk("  SEND = upon receiving \"TRUE\" value will send the local audio");
  blk("         from the microphone to pComms_server and other         ");
  blk("         pComms_clients. The MOOS variable name and value can   ");
  blk("         be changed by setting the paramaters in the .moos file.");
  blk("                                                                ");
  blk("PUBLICATIONS:                                                   ");
  blk("------------------------------------                            ");
  blk("  TRANSMIT                    TRUE when client is transmitting. ");
  blk("  TRANSMIT_BUFFER_SIZE        Size of transmission buffer.      ");
  blk("  RECEIVING_AUDIO             TRUE if receiving audio from server.");
  blk("  RECEIVING_AUDIO_BUFFER_SIZE Size of receiving buffer.         ");
  blk("                                                                ");
  exit(0);
}

//----------------------------------------------------------------
// Procedure: showReleaseInfoAndExit

void showReleaseInfoAndExit()
{
  showReleaseInfo("pComms_client", "gpl");
  exit(0);
}

