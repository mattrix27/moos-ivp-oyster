//
// arduino-serial-lib -- simple library for reading/writing serial ports
//
// 2006-2013, Tod E. Kurt, http://todbot.com/blog/
//

#ifndef USE_KAESS_SERIAL

#ifndef __ARDUINO_SERIAL_LIB_H__
#define __ARDUINO_SERIAL_LIB_H__

#include <stdint.h>   // Standard types

class Serial
{
public:

	Serial() : serialPort(-1) {}
	bool serialport_init(const char* serialport, int baud);
	int serialport_close();
	bool serialport_writebyte(uint8_t b);
	bool serialport_write(const char* str);
	bool serialport_read_until(char* buf, char until, int buf_max,int timeout);
	int serialport_flush();
	bool serialport_read_one_char(char& c);

private:
//	struct termios tio;
//	struct termios tioOld;
	int serialPort;
};


#endif


#endif
