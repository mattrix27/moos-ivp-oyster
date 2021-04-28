/************************************************************/
/*    NAME: Simon Andrews                                              */
/*    ORGN: MIT                                             */
/*    FILE: CamViewer.cpp                                        */
/*    DATE:                                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "CamViewer.h"

using namespace cv;
using namespace std;

//---------------------------------------------------------
// Constructor

CamViewer::CamViewer()
{
  imageWidth = -1;
  imageHeight = -1;
  imageType = -1; // CV_8UC1 = 0, so can't leave uninitialized
}

//---------------------------------------------------------
// Destructor

CamViewer::~CamViewer()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool CamViewer::OnNewMail(MOOSMSG_LIST &NewMail)
{
  MOOSMSG_LIST::iterator p;
   
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key = msg.GetKey();
    if (key == "IMAGE") {
      if (imageWidth <= 0 || imageHeight <= 0 || imageType < 0) {
        continue;
      }
      void *imageData = msg.GetBinaryData();
      image = Mat(imageHeight, imageWidth, imageType, imageData);
      imshow("Output", image);
    }
    else if (key == "IMAGE_WIDTH") {
      imageWidth = static_cast<int>(msg.GetDouble());
    }
    else if (key == "IMAGE_HEIGHT") {
      imageHeight = static_cast<int>(msg.GetDouble());
    }
    else if (key == "IMAGE_TYPE") {
      imageType = static_cast<int>(msg.GetDouble());
    } else { cout << "hmm" << endl; }
  }
  return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool CamViewer::OnConnectToServer()
{
   // register for variables here
   // possibly look at the mission file?
   // m_MissionReader.GetConfigurationParam("Name", <string>);
   // m_Comms.Register("VARNAME", 0);
	
   RegisterVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool CamViewer::Iterate()
{
  char c = static_cast<char>(waitKey(1));
  if (c == 27 /* ESC */) {
    // TODO: Make this quit properly?
    exit(0);
  }
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool CamViewer::OnStartUp()
{
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string line  = *p;
      string param = tolower(biteStringX(line, '='));
      string value = line;
      
      if(param == "foo") {
        //handled
      }
      else if(param == "bar") {
        //handled
      }
    }
  }
  
  RegisterVariables();	
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void CamViewer::RegisterVariables()
{
  Register("IMAGE", 0);
  Register("IMAGE_HEIGHT", 0);
  Register("IMAGE_WIDTH", 0);
  Register("IMAGE_TYPE", 0);
}

