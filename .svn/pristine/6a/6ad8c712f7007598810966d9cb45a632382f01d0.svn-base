/**
 * @file Serial.h
 * @brief Simple serial interface, for example to talk to Arduino.
 * @author: Michael Kaess
 */

#ifdef USE_KAESS_SERIAL

#ifndef KAESS_SERIAL_H
#define KAESS_SERIAL_H

#include <string>


class Serial {


public:

  Serial() : m_serialPort(-1) {}

  // open a serial port connection
  void serialport_init(const std::string& port, int baudRate);

  void print(unsigned char *buf, int len);

  // send a string
  void print(std::string str) const;

  // send an integer
  void print(int num) const;

  // send a double
  void print(double num) const;

  // send a float
  void print(float num) const;

private:
    struct termios tio;
    struct termios tioOld;
    int m_serialPort; // file description for the serial port
};



#endif

#endif
