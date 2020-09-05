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
 	bool reset(); 
 	int char2int(char A);
 	void setPhoneFunctionality();
 	void signalQuality();
 	bool Baud_rate(char* baud_rate);
 	bool answerCall();
 	void callNumber(char* number);
 	char Recall(void);
 	void RejectCall(void);
 	bool sim_is_call(void);
 	uint8_t getCallStatus();
 	bool hangoffCall();
 	bool sendSms(char* number,char* text);
 	String getNumberSms(uint8_t index);
 	String readSms(uint8_t index);
 	bool deleteSms(bool Mode);
 	void RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second);
 	String dateNet();
 	bool echo(bool echo);
 	bool sleep(char mode);
 	bool Microphone(char channel ,int gainlevel);
 	void PowerOff(void);
 	bool MicSwitch(char mode);
 	bool WhiteList(char mode,char index,char*number);
};

#pragma used-

#endif