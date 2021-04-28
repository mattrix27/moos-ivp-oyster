/****************************************************************/
/*    NAME: Mike Benjamin                                       */
/*    FILE: main.cpp                                            */
/*    DATE: July 18th, 2018                                     */
/****************************************************************/

#include <iostream>
#include "KeyProg.h"

using namespace std;

void usage(string);

//--------------------------------------------------------
// Procedure: main

int main(int argc, char *argv[])
{
  if(argc != 2) {
    cout << "Usage: keyprog key" << endl;
    return(1);
  }
  KeyProg keyprog;
  keyprog.generate(argv[1]);
  
  return(0);
}

