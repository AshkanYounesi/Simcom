
#include <simcom.h>

SoftwareSerial SIM(RX_PIN,TX_PIN);


void SimCom::init()
{
	SIM.begin(9600);
	_buffer.reserve(255); //reserve memory to prevent intern fragmention
}

/***************************************************/
int SimCom::char2int(char A)
{
 switch(A)
 {
  case '0':return 0;
  case '1':return 1;
  case '2':return 2;
  case '3':return 3;
  case '4':return 4;
  case '5':return 5;
  case '6':return 6;
  case '7':return 7;
  case '8':return 8;
  case '9':return 9;
 }
}

/***************************************************/
String SimCom::_readSerial()
{
  _timeout=0;
  while  (!SIM.available()) 
  {
    delay(10);
    _timeout++;
    if (_timeout > 1000)
    {
    	break; 
    	return false;
    }
  }
  if (SIM.available()) {
 	return SIM.readString();
  }
}

/***************************************************/
bool SimCom::reset(){
  digitalWrite(RESET_PIN,1);
  delay(1000);
  digitalWrite(RESET_PIN,0);
  delay(1000);
  // wait for the module response

  SIM.print(F("AT\r\n"));
  _timeout=0;
  while (_readSerial().indexOf("OK")==-1)
  {
    SIM.print(F("AT\r\n"));
    delay(10);
    _timeout++;
    if (_timeout>1000) 
    {
    	break; 
    	return false;
    }
  }
  
  //wait for sms ready
  _timeout=0;
  while (_readSerial().indexOf("SMS")==-1 )
  {
	delay(10);
	_timeout++;
	if (_timeout>1000) 
	{
		break; 
		return false;
	}
  } 
  return true;
}

/***************************************************/
void SimCom::setPhoneFunctionality(){
  /*AT+CFUN=<fun>[,<rst>] 
  Parameters
  <fun> 0 Minimum functionality
  1 Full functionality (Default)
  4 Disable phone both transmit and receive RF circuits.
  <rst> 1 Reset the MT before setting it to <fun> power level.
  */
  SIM.print (F("AT+CFUN=1\r\n"));
}

/***************************************************/
void SimCom::signalQuality(){
/*Response
+CSQ: <rssi>,<ber>Parameters
<rssi>
0 -115 dBm or less
1 -111 dBm
2...30 -110... -54 dBm
31 -52 dBm or greater
99 not known or not detectable
<ber> (in percent):
0...7 As RXQUAL values in the table in GSM 05.08 [20]
subclause 7.2.4
99 Not known or not detectable 
*/
  SIM.print (F("AT+CSQ\r\n"));
  Serial.println(_readSerial());
}

/***************************************************/
bool SimCom::Baud_rate(char* baud_rate)
{
	SIM.print (F("AT+IRP=\""));  
	SIM.print (baud_rate);           
	SIM.print(F("\"\r"));  
	_timeout=0;
	while (_readSerial().indexOf("OK")==-1)
	{
		delay(10);
		_timeout++;
		if (_timeout>1000) 
		{
			break; 
			return false;
		}
	}
	return true;
}

/***************************************************/
bool SimCom::answerCall(){
   SIM.print (F("ATA\r\n"));
   _buffer=_readSerial();
   //Response in case of data call, if successfully connected 
   if ( (_buffer.indexOf("OK") )!=-1 ) return true;  
   else return false;
}

/***************************************************/


/***************************************************/


/***************************************************/


/***************************************************/


/***************************************************/


/***************************************************/


/***************************************************/


/***************************************************/


