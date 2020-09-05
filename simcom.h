/*
 *    Created on: September, 2, 2020
 *        Author: Ashkan
*/

#ifndef _SIMCOM_H_
#define _SIMCOM_H_

#ifndef Arduino_h
#include "Arduino.h"
#endif

#ifndef SoftwareSerial_h
#include <SoftwareSerial.h>
#endif

#ifndef _STDIO_INCLUDED
#include <stdio.h>
#endif

#define RX_PIN 			10
#define TX_PIN 			11

#define CTRL_Z 			0x1a
#define ENTER  			0x0d
#define double_quote 	0x22

#define RING_PIN  		2
#define RESET_PIN  		3
#define POWER_PIN 		4

#pragma used+


class SimCom		
{									
  private:
  	int _timeout;
	String _buffer;
		String _readSerial();

  public:

 	void init();	
 	void reset(); 
}

#endif