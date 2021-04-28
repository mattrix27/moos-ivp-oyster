/************************************************************/
/*    NAME: Carter Fendley                                  */
/*    ORGN: MIT                                             */
/*    FILE: NetMon.h                                      */
/*    DATE:                                                 */
/************************************************************/

#ifndef NetMon_HEADER
#define NetMon_HEADER

#include "MOOS/libMOOS/MOOSLib.h"
#include <array>

using namespace std;

class NetMon : public CMOOSApp
{
 public:
   NetMon();
   ~NetMon();

 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();

 protected:
   void RegisterVariables();
   bool isHostUp(string ip);
   string genNameStr(string name, string ip);
   string genStatusStr(bool up);
   int writeStatus(int y, int x, string name, string ip, bool up);
   int writeStatus(int y, int x, string ip, bool up);
   void updateMaxStatusLength();
   string genDebugStr();
   void setupScreen();

 private: // Configuration variables
   static const int m_buffer_size = 1; 
 private: // State variables
   map <string, vector< array<string, 2> > > m_group_map;
   int m_max_y, m_max_x;
   int m_max_dstring_size;
   int m_dstring_per_line;
   int m_max_name_len;
   int m_max_status_len;

   stringstream m_debug;
};

#endif 
