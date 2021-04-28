//Author: Michael "Misha" Novitzky
//Date: March 26th 2018
//Origin: MIT

#ifndef UDPConnect_HEADER
#define UDPConnect_HEADER
#include<sys/socket.h>
#include<sys/types.h>
#include<iostream>
#include<string>
#include<arpa/inet.h>
#include<stdio.h>

using namespace std;

class UDPConnect
{ 
 public:
  UDPConnect();
  ~UDPConnect();
  struct sockaddr_in my_address;
  int sock;
  int valread;
  struct sockaddr_in send_to_address;

  int CreateSocket();
  int BindSocket( int myPortNo, std::string myAddress);
  int SendTo( short* data, int length, int destPortNo, std::string destIP);
  int Receive( short * buffer, int length, sockaddr_in & remote_client, socklen_t & remote_client_size);
};

  #endif
