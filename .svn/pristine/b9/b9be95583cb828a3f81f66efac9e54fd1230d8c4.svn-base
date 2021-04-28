/************************************************************/
/*    NAME: Oliver MacNeely                                              */
/*    ORGN: MIT                                             */
/*    FILE: PingDisplay.h                                          */
/*    DATE:                                                 */
/************************************************************/

#ifndef PingDisplay_HEADER
#define PingDisplay_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "XYConvexGrid.h"

class PingDisplay : public CMOOSApp
{
 public:
   PingDisplay() {};
   ~PingDisplay() {};
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   void RegisterVariables();
   void postArray(std::vector<std::vector<float> > square, unsigned center, int layers, int length);
   void createHeatMap(unsigned point, int levels);

   int currentX;
   int currentY;
   double currentCELL;
   std::vector<std::vector<float> > array;
   std::vector<float> column;  


 protected:
   bool buildReport();
   void registerVariables();
   void handleReceivedPing(std::string);

   void postGrid();
   XYConvexGrid m_grid;
   
   int height;
   int width;
   int weight;
   int level;

 private: // State variables
   unsigned int m_iterations;
   double       m_timewarp;
   std::string  m_msgs;
};

#endif 
