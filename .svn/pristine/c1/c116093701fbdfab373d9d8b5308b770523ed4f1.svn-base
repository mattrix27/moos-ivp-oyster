/************************************************************/
/*    NAME: Simon Andrews                                   */
/*    ORGN: MIT                                             */
/*    FILE: CamViewer.h                                     */
/*    DATE:                                                 */
/************************************************************/

#ifndef CamViewer_HEADER
#define CamViewer_HEADER

#include <opencv2/opencv.hpp>
#include "MOOS/libMOOS/MOOSLib.h"

class CamViewer : public CMOOSApp
{
 public:
   CamViewer();
   ~CamViewer();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   void RegisterVariables();

 private: // Configuration variables

 private: // State variables
   cv::Mat image;
   int imageWidth;
   int imageHeight;
   int imageType;
};

#endif 
