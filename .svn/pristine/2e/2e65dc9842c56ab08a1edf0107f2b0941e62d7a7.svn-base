/************************************************************/
/*    ORIGINAL NAME: Oliver MacNeely                        */
/*    NAME: Michael "Misha" Novitzky                        */
/*    ORGN: MIT                                             */
/*    FILE: Comms_server.cpp                                */
/*    DATE: March 19th 2018                                 */
/************************************************************/

#include <iterator>
#include "MBUtils.h"
#include "Comms_server.h"
#include <cstdlib>   // for the strtoul() function
#include "UDPConnect.h"
#include <stdio.h>
#include <string.h>

using namespace std;
char ipstr[INET6_ADDRSTRLEN]; // string that contains the ip of the connected client
int port; // int that contains the port of the connected client

std::vector<unsigned short int> clients; // vector of the ports of clients connected to the server
std::vector<std::string> ips; // vector of the strings of clients

struct AudioBuffer { // structure that contains the information for each packet of audio

  short *recording; // pointer to packet data itself
  size_t size; // size of packet
  size_t recorded_size; // size of recording
  short *recordedSamples; // pointer to beginning of collated recordings

} AudioBuffer;

// initialize necessary variables

int message_counter = 0;
int port_counter = 0;

bool pushBACK = false;

// initialize structure for holding audio data

struct AudioBuffer buffer = {(short*) malloc(FRAMES_PER_BUFFER* sizeof(short)*NUM_CHANNELS), FRAMES_PER_BUFFER* sizeof(short)*NUM_CHANNELS, 0, NULL};

// initialize socket information for receiving data

// structures for holding server and client data for receiving data

UDPConnect server;

struct sockaddr_in client;

socklen_t l = sizeof(client);

//initialize socket information for sending data
UDPConnect sender;


//---------------------------------------------------------
// Constructor

Comms_server::Comms_server()
{
  m_GoodState = true;
}

//---------------------------------------------------------
// Destructor

Comms_server::~Comms_server()
{
}

//---------------------------------------------------------
// Procedure: OnNewMail

bool Comms_server::OnNewMail(MOOSMSG_LIST &NewMail)
{
  cout << endl << "In OnNewMail method " << endl;
  AppCastingMOOSApp::OnNewMail(NewMail);

  MOOSMSG_LIST::iterator p;

  for(p=NewMail.begin(); p!=NewMail.end(); p++) {
    CMOOSMsg &msg = *p;

#if 0 // Keep these around just for template
    string key   = msg.GetKey();
    string comm  = msg.GetCommunity();
    double dval  = msg.GetDouble();
    string sval  = msg.GetString();
    string msrc  = msg.GetSource();
    double mtime = msg.GetTime();
    bool   mdbl  = msg.IsDouble();
    bool   mstr  = msg.IsString();
#endif
  }
   return(true);
}

//---------------------------------------------------------
// Procedure: OnConnectToServer

bool Comms_server::OnConnectToServer()
{
  cout << endl << " In OnConnectToServer method " << endl;
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

bool Comms_server::Iterate()
{
  //  cout << endl << "In Iterate method " << endl;
  AppCastingMOOSApp::Iterate();
 AppCastingMOOSApp::PostReport();
  return(true);
}

//---------------------------------------------------------
// Procedure: OnStartUp()
//            happens before connection is open

bool Comms_server::OnStartUp()
{
  AppCastingMOOSApp::OnStartUp();

  bool server_sock_param_set = false;
  bool server_ip_param_set = false;

  cout << endl << "In StartUp method " << endl;
  list<string> sParams;
  m_MissionReader.EnableVerbatimQuoting(false);
  if(m_MissionReader.GetConfiguration(GetAppName(), sParams)) {
    list<string>::iterator p;
    for(p=sParams.begin(); p!=sParams.end(); p++) {
      string original_line = *p;
      string param = stripBlankEnds(toupper(biteString(*p, '=')));
      string value = stripBlankEnds(*p);

      if(param == "FOO") {
        //handled
      }
      else if(param == "BAR") {
        //handled
      }
      else if(param == "SERVERSOCKET") {
        cout << endl << "Reading ServerSocket config " << endl;
          uint64_t new_value = strtoul(value.c_str(), NULL, 0);
          m_ServerSocket = new_value;
          server_sock_param_set = true;
      }
      else if(param == "SERVERIP") {
        cout << endl << "Reading ServerIP config " << endl;
        m_ServerIp = value;
        server_ip_param_set = true;
      }

    }
  }

  if(!(server_sock_param_set && server_ip_param_set)) {
    reportConfigWarning("Server IP and Port Number not Set!");
    m_GoodState = false;
  }
  else {
    if(server.CreateSocket()== -1){
      reportConfigWarning("Unable to create socket!");
      m_GoodState = false;
    }
    else {
      if(server.BindSocket(m_ServerSocket,m_ServerIp) == -1) {
      reportConfigWarning("Server Socket Bind Error!");
      m_GoodState = false;
      }
      else {
        ufds[0].fd = server.sock;
        ufds[0].events = POLLIN;  
      }
    }
  }

  //Let's spawn the thread that reads from the socket
  //and passes it on to other clients
  if(m_GoodState == true) {

    s_t = new CMOOSThread();

    bool serverThreadCreated = s_t->Initialise(StartServerThread, this);

    if(serverThreadCreated == false) {
      reportConfigWarning("Unable to create server thread!");
      m_GoodState = false;
    }
    else {
      s_t->Start();
    }

  }

  RegisterVariables();
  return(true);
}

//---------------------------------------------------------
// Procedure: RegisterVariables

void Comms_server::RegisterVariables()
{
  AppCastingMOOSApp::RegisterVariables();

  // Register("FOOBAR", 0);
}

bool Comms_server::buildReport()
{
  m_msgs << "============================================ \n";
  m_msgs << "VOIP Server                                  \n";
  m_msgs << "============================================ \n";

  m_msgs << "    Server IP: " << m_ServerIp << endl;
  m_msgs << "Server Socket: " << m_ServerSocket << endl;
  m_msgs << endl;
  m_msgs << "Receiving Data From " << m_ReceivingFrom << " Buffer Size:" << m_ReceiveBufferSize << endl;

  //list pComms_clients
  m_msgs << endl;
  m_msgs << "Connected Clients" << endl;
  for(std::vector<std::string>::iterator it = m_connectedClients.begin(); it!= m_connectedClients.end(); ++it) {
    m_msgs << *it << endl;
  }
  m_msgs << "Transmit Buffer Size: " << m_TransmitBufferSize << endl;
  return(true);
}

bool Comms_server::SocketServerThread()
{

  bool allGood = true;

  if(allGood == true) {

  m_ReceiveBufferSize = "0";
  m_TransmitBufferSize = "0";

  if(m_GoodState){
    int rv = 0;
    
    rv = poll(ufds, 1, 1); // check to see if there is data from the clients

    if (rv != 0) { // if there is data, receive it


    pushBACK = false; // assume we shouldn't add the first connected port to list of clients

  int attempt_receive = server.Receive(buffer.recording, buffer.size, client,l);
  //  recvfrom(sock, buffer.recording, buffer.size, 0, (struct sockaddr *) &client, &l); // receive audio from connected client


  // check if ip4 or ip6 for grabbing port + ip address
  if (client.sin_family == AF_INET) {
    struct sockaddr_in *s = (struct sockaddr_in *)&client;
    port = ntohs(s->sin_port);
    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
  } else { // AF_INET6
    struct sockaddr_in6 *s = (struct sockaddr_in6 *)&client;
    port = ntohs(s->sin6_port);
    inet_ntop(AF_INET6, &s->sin6_addr, ipstr, sizeof ipstr);
  }

  m_ReceivingFrom = ipstr;
  Notify("RECEIVING_FROM_CLIENT",ipstr);
    std:stringstream rs;
  rs << buffer.size;
  m_ReceiveBufferSize = rs.str();
  Notify("RECEIVING_BUFFER_SIZE",m_ReceiveBufferSize);

  if (message_counter == 0) { // if this is the first time, add the client to list

 clients.push_back(port);
        ips.push_back(ipstr);
        m_connectedClients.push_back(ipstr);

        port_counter++;
        Notify("SERVER_INCOMING_PORT_COUNT",port_counter);
        std::string incoming_client = m_connectedClients.back();
        incoming_client += ":";
        incoming_client += clients.back();
        Notify("NEW_CLIENT",incoming_client);



      } else { // if not, iterate through list of clients and check to see whether connected client is there

        for (int i = 0; i < port_counter; i++) {

          if (clients[i] == port) {

            cout << "Same port!" << endl;
            cout << "saved port: " << clients[i] << endl;
            cout << "new port: " << port << endl;

            pushBACK = false; // if the client is there, don't add to list

            break;

          } else {

            pushBACK = true; // if the client isn't there, add to list

          }

        }

        if (pushBACK == true) { // depending on value, add client to list of conected clients

          clients.push_back(port);
          ips.push_back(ipstr);
          m_connectedClients.push_back(ipstr);

          port_counter++;
          Notify("SERVER_INCOMING_PORT_COUNT",port_counter);
          std::string incoming_client = m_connectedClients.back();
          incoming_client += ":";
          incoming_client += clients.back();
          Notify("NEW_CLIENT",incoming_client);

        }

      }

  for (int i = 0; i < port_counter; i++) {

    if (clients[i] == port) {

      cout << "I continued, port = " << clients[i] << endl;

    } else {

      // setup a information to send the audio for each client that isn't the one that send the audio
      sender.CreateSocket();
      //      sender.BindSocket(11112, ips[i]);
      sender.SendTo(buffer.recording, buffer.size, 11112, ips[i]);
      std::stringstream ts;
      ts << buffer.size;
      m_TransmitBufferSize = ts.str();
      std::string outgoing_client = ips[i];
      outgoing_client += ":";
      outgoing_client += 11112;
      Notify("TRANSMITTING_AUDIO_TO",outgoing_client );
      Notify("TRANSMITTING_AUDIO_BUFFER_SIZE",m_TransmitBufferSize);

         }

  }

  message_counter++;
    }
    else {
      m_ReceivingFrom = "";
    }
  }
    
  }
  return true;
}

bool Comms_server::StartServerThread(void *param)
{
  Comms_server* me = (Comms_server*)param;
  return me->SocketServerThread();
}

