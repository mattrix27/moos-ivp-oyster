/*****************************************************************/
/*    NAME: Michael Benjamin                                     */
/*    ORGN: Dept of Mechanical Eng / CSAIL, MIT Cambridge MA     */
/*    FILE: main.cpp                                             */
/*    DATE: April 21st, 2017                                     */
/*****************************************************************/

#include <string>
#include <cstdlib>
#include <iostream>
#include "MBUtils.h"
#include "CatHandler.h"

using namespace std;

void showHelpAndExit();

//--------------------------------------------------------
// Procedure: main

int main(int argc, char *argv[])
{
  CatHandler handler;
    
  for(int i=1; i<argc; i++) {
    string argi = argv[i];

    bool handled = true;
    if((argi == "-h") || (argi == "--help"))
      showHelpAndExit();
    else {
      handled = handler.addFile(argi);
    }

    if(!handled) {
      cout << "Unhandle argument: " << argi << endl;
      return(1);
    }
  }

  bool ok = handler.handle();
  if(!ok)
    return(1);
  
  return(0);
}


//--------------------------------------------------------
// Procedure: showHelpAndExit()

void showHelpAndExit()
{ 
  cout << "Usage: [OPTIONS] file1 file2                          " << endl;
  cout << "                                                      " << endl;
  cout << "Synopsis:                                             " << endl;
  cout << "  Concatenate authorized_keys files while rejecting   " << endl;
  cout << "  duplicates.                                         " << endl;
  cout << "                                               " << endl;
  exit(0);
}
