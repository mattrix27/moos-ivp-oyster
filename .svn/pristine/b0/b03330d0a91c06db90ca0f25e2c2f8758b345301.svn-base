/**
 * @file Serial.cpp
 * @brief Simple serial interface, for example to talk to Arduino.
 * @author: Michael Kaess
 */

#ifdef USE_KAESS_SERIAL

#include <fcntl.h>
#include <termios.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string.h>

#include "KaessSerial.h"

using namespace std;



void Serial::open(const string& port, int baudRate)
{
    speed_t baud;

    switch (baudRate) {
    case 9600:      baud = B9600;     break;
    case 19200:     baud = B19200;    break;
    case 38400:     baud = B38400;    break;
    case 57600:     baud = B57600;    break;
    case 115200:    baud = B115200;   break;
    default:        baud = 19200;     break; }

    m_serialPort = ::open(port.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (m_serialPort < 0) {
        cout << "Unable to open serial port" << endl;
        exit (-1); }
    tcgetattr(m_serialPort, &tioOld);

    memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0; // Maybe set this to IGNPAR?
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL;             // 8n1, see termios.h for more information
    tio.c_lflag = 0;
    tio.c_cc[VMIN]  = 0;
    tio.c_cc[VTIME] = 10;
    cfsetospeed(&tio, baud);
    cfsetispeed(&tio, baud);
    tcflush(m_serialPort, TCIFLUSH);
    tcsetattr(m_serialPort, TCSANOW, &tio);
/*
    // GNU/Linux: open a serial port connection
    m_serialPort = ::open(port.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (m_serialPort == -1) {
        cout << "Unable to open serial port" << endl;
        exit (-1); }
    fcntl(m_serialPort, F_SETFL,0);
    struct termios port_settings;           // structure to store the port settings in
    cfsetispeed(&port_settings, baud);   // set baud rates
    cfsetospeed(&port_settings, baud);
    port_settings.c_cflag &= ~PARENB;       // set no parity, stop bits, 8 data bits
    port_settings.c_cflag &= ~CSTOPB;
    port_settings.c_cflag &= ~CSIZE;
    port_settings.c_cflag |= CS8;
    tcsetattr(m_serialPort, TCSANOW, &port_settings);    // apply the settings to the port
*/

}

void Serial::print(unsigned char *buf, int len) {
    int res = ::write(m_serialPort, buf, len);
}

// send a string
void Serial::print(string str) const {
  int res = ::write(m_serialPort, str.c_str(), str.length());
}

// send an integer
void Serial::print(int num) const {
  stringstream stream;
  stream << num << endl;
  string str = stream.str();
  print(str);
}

// send a double
void Serial::print(double num) const {
  stringstream stream;
  stream << num << endl;
  string str = stream.str();
  print(str);
}

// send a float
void Serial::print(float num) const {
  print((double)num);
}

#endif
