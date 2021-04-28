/************************************************************/
/*    NAME: Michael DeFilippo                               */
/*    ORGN: MIT                                             */
/*    FILE: WebCam_mjd.cpp                                  */
/*    DATE:                                                 */
/************************************************************/

#include <stdlib.h>
#include <iterator>
#include "MBUtils.h"
#include "ACTable.h"
#include "WebCam.h"

using namespace std;

//---------------------------------------------------------
// Constructor

WebCam::WebCam()
{
  // defaults
  imageWidth = 640.0;
  imageHeight = 480.0;
  vc.open(1); //set to 1 because Jetson camera module takes 0 slot and is kinda broken -Simon, 7/25
  imageCount = 0;
  fpsTracker = FPSTracker();
}

WebCam::~WebCam()
{
  vc.release();
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool WebCam::OnNewMail(MOOSMSG_LIST &NewMail)
{
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;
  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;
    string key    = msg.GetKey();

#if 0 // Keep these around just for template
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif

     /*else* if(key != "APPCAST_REQ") // handle by AppCastingMOOSApp
       reportRunWarning("Unhandled Mail: " + key); */
  }
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool WebCam::OnConnectToServer()
{
   registerVariables();
   return(true);
}

//---------------------------------------------------------
// Procedure: Iterate()
//            happens AppTick times per second

bool WebCam::Iterate()
{
  AppCastingMOOSApp::Iterate();

  Notify("FPS", fpsTracker.getFPS());

  // Send binary data to MOOSDB
  if(vc.isOpened())
    {
      vc >> capture_frame;
      fpsTracker.count();
      Notify("IMAGE", (void*)capture_frame.data, capture_frame.step[0] * capture_frame.rows, MOOSLocalTime());
      Notify("IMAGE_HEIGHT", capture_frame.rows);
      Notify("IMAGE_WIDTH", capture_frame.cols);
      Notify("IMAGE_TYPE", capture_frame.type());
      imageCount++;
    }
    else {
      reportRunWarning("Camera object not open!");
    }

  AppCastingMOOSApp::PostReport();

  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool WebCam::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  if(!vc.isOpened())
    return false;

  // Load a configuration file (.moos?) into memory.
  STRING_LIST sParams;
  if(!m_MissionReader.GetConfiguration(GetAppName(), sParams))
    reportConfigWarning("No config block found for " + GetAppName());

  // Go through each value. If it's of interest, handle it appropriately. If
  // not, give a warning.
  STRING_LIST::iterator p;
  for(p=sParams.begin(); p!=sParams.end(); p++) {
    string orig = *p;
    string param = stripBlankEnds(biteString(*p, '='));
    string value = stripBlankEnds(*p);
	
    bool handled = false;

    if(param == "ImageWidth") {
      imageWidth = strtod(value.c_str(), 0);
      handled = true;
    }
    else if(param == "ImageHeight") {
      imageHeight = strtod(value.c_str(), 0);
      handled = true;
    }

    if(!handled)
      reportUnhandledConfigWarning(orig);
  }

  // set resolution to defaults or params, if included in plug file
  vc.set(CV_CAP_PROP_FRAME_WIDTH, imageWidth);
  vc.set(CV_CAP_PROP_FRAME_HEIGHT, imageHeight);

  registerVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: registerVariables

void WebCam::registerVariables()
{
  AppCastingMOOSApp::RegisterVariables();
}


//------------------------------------------------------------
// Procedure: buildReport()

bool WebCam::buildReport()
{
  m_msgs << "Requested resolution:  " << imageWidth << "x" << imageHeight << "\n";
  m_msgs << "Last image resolution: " << capture_frame.cols << "x" << capture_frame.rows << "\n";
  m_msgs << "OpenCV Image type: " << capture_frame.type() << "\n";
  m_msgs << "Number of images captured: " << imageCount << "\n";
  return(true);
}
