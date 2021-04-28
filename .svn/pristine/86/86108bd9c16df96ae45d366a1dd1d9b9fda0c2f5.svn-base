/************************************************************/
/*    NAME: Michael DeFilippo                               */
/*    ORGN: MIT                                             */
/*    FILE: WebCam_mjd.h                                    */
/*    DATE: 21 July 2017                                    */
/************************************************************/

#ifndef WebCam_HEADER
#define WebCam_HEADER

#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"

#include "opencv2/opencv.hpp"
//#/include "opencv2/highgui/highgui.hpp"
//#/include "opencv2/core/core.hpp"      // Basic OpenCV structures (cv::Mat)
#include <iostream>
#include <ctime>
#include "FPSTracker.h"

class WebCam: public AppCastingMOOSApp
{
 public:
   WebCam();
   ~WebCam();

   cv::VideoCapture vc;
   cv::Mat capture_frame, image, bw_image;

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected: // Standard AppCastingMOOSApp function to overload 
   bool buildReport();

 protected:
   void registerVariables();

 private: // Configuration variables
   double imageWidth;
   double imageHeight;

 private: // State variables
   unsigned int imageCount;
   FPSTracker fpsTracker;
};

#endif 
