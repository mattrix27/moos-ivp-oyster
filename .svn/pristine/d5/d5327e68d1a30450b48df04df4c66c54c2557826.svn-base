/************************************************************/
/*    ORIGINAL NAME: Oliver MacNeely                        */
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: Comms_client.h                                  */
/*    DATE: March 21 2018                                   */
/************************************************************/

#ifndef Comms_client_HEADER
#define Comms_client_HEADER

#include  "MOOS/libMOOS/Thirdparty/AppCasting/AppCastingMOOSApp.h"
#include "MOOS/libMOOS/Utils/MOOSThread.h"
#include <sys/poll.h>

class Comms_client : public AppCastingMOOSApp
{
 public:
   Comms_client();
   ~Comms_client();

  struct pollfd ufds[1]; // set up polling so that the client isn't waiting to receive data from the server
 protected: // Standard MOOSApp functions to overload  
   bool OnNewMail(MOOSMSG_LIST &NewMail);
   bool Iterate();
   bool OnConnectToServer();
   bool OnStartUp();
   bool buildReport(); 

protected:
   void RegisterVariables();
  static bool StartMicThread(void* param);
  bool ReadMicThread();

  static bool StartPlayThread(void* param);
  bool PlayNetworkAudio();

 private: // Configuration variables
  
  CMOOSThread*  m_t;
  CMOOSThread*  p_t;
  int m_ClientSocket;
  std::string m_ClientIP;
  int m_ServerSocket;
  std::string m_ServerIP;
  std::string m_ListenForMOOSVar;
  std::string m_ListenForMOOSValue;
  std::string m_TransmitBufferSize;
  std::string m_ReceiveBufferSize;

 private: // State variables
  bool m_GoodState;
  bool m_SendAudio;
  bool m_Transmitting;
  bool m_Receiving;
  int  m_ReadMicCount;
  int  m_PlayNetworkAudioCount;
};

#endif 
