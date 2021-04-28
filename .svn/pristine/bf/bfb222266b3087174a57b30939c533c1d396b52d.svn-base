/*
 * mainJoystick.cpp
 *
 *  Created on: Sep 24, 2015
 *      Author: Alon Yaari
 */


#include <string>
#include "MBUtils.h"
#include "ColorParse.h"
#include "moosJoy.h"
#include "moosJoyInfo.h"

#include <SDL.h>

using namespace std;

int main(int argc, char *argv[])
{
  string mission_file = "";
  string run_command  = argv[0];

  for (int i = 1; i < argc; i++) {
    string argi = argv[i];
    if ((argi == "-e") || (argi == "--example") || (argi == "-example"))
      showExampleConfigAndExit();
    else if ((argi == "-h") || (argi == "--help") || (argi=="-help"))
      showHelpAndExit();
    else if ((argi == "-i") || (argi == "--interface"))
      showInterfaceAndExit();
    else if (strEnds(argi, ".moos") || strEnds(argi, ".moos++"))
      mission_file = argv[i];
    else if (strBegins(argi, "--alias="))
      run_command = argi.substr(8);
    else if (i == 2)
      run_command = argi; }
  if (mission_file == "")
    showHelpAndExit();
  cout << termColor("green");
  cout << "iJoystick running as: " << run_command << endl;
  cout << termColor() << endl;
  moosJoy joy;
  joy.Run(run_command.c_str(), mission_file.c_str());
  return 0;
}



















//
