/************************************************************/
/*    NAME: Michael DeFilippo                               */
/*    ORGN: MIT                                             */
/*    FILE: main.cpp                                        */
/*    DATE: December 29th, 1963                             */
/************************************************************/

#include <string>
#include "MBUtils.h"
#include "ColorParse.h"
#include "WebCam.h"
#include "WebCam_Info.h"

using namespace std;

using namespace cv;

int main(int argc, char *argv[])
{
  string mission_file;
  string run_command = argv[0];

  //Mat frame;
  time_t date_time = time(NULL);
  string date_time_string = asctime(localtime(&date_time));
  //string log_dir = "/home/nvidia/moos-ivp-jetsoncamtest/bin/test.avi";// + date_time_string + ".mpg";
  WebCam WebCam;

  for(int i=1; i<argc; i++) {
    string argi = argv[i];
    if((argi=="-v") || (argi=="--version") || (argi=="-version"))
      showReleaseInfoAndExit();
    else if((argi=="-e") || (argi=="--example") || (argi=="-example"))
      showExampleConfigAndExit();
    else if((argi == "-h") || (argi == "--help") || (argi=="-help"))
      showHelpAndExit();
    else if((argi == "-i") || (argi == "--interface"))
      showInterfaceAndExit();
    else if(strEnds(argi, ".moos") || strEnds(argi, ".moos++"))
      mission_file = argv[i];
    else if(strBegins(argi, "--alias="))
      run_command = argi.substr(8);
    else if(i==2)
      run_command = argi;
  }

  if(mission_file == "")
    showHelpAndExit();


  cout << termColor("green");
  cout << "iWebCam launching as " << run_command << endl;
  cout << termColor() << endl;

  //cout << termColor("red");
  //cout << asctime(localtime(&date_time)) << endl;
  //cout << termColor() << endl;

/*
  //create a window called "MyVideo"
    namedWindow("MyVideo", CV_WINDOW_AUTOSIZE);

  //get the width and height of frames of the video
  double dWidth = WebCam.vc.get(CV_CAP_PROP_FRAME_WIDTH);
  double dHeight = WebCam.vc.get(CV_CAP_PROP_FRAME_HEIGHT);

  //  cout << "Frame size:" << dWidth << "x"<< dHeight << endl;

  Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));

  // initialize VideoWriter object
  VideoWriter oVideoWriter(log_dir,CV_FOURCC('M','J','P','G'),10,frameSize,true);

  if(!oVideoWriter.isOpened()) //If not exit the program
  {
    cout << "Error: Failed to write video" << endl;
    return -1;
  }

  while(1)
    {
      WebCam.vc >> WebCam.capture_frame;
      if (WebCam.capture_frame.empty()) { cout << "Empty frame" << endl; break; }

      oVideoWriter.write(WebCam.capture_frame); //write the frame into the file

        imshow("MyVideo", WebCam.capture_frame); // show the frame in "MyVideo" window

      if (waitKey(30)==27) // wait for 'esc' key press for 30ms. if 'esc' key is pressed break loop
	{
	  cout << "esc key is pressed by user" << endl;
	  break;
	}
    }
  */
  WebCam.Run(run_command.c_str(), mission_file.c_str());

  return(0);
}

