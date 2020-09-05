
#include <simcom.h>

SoftwareSerial SIM(RX_PIN,TX_PIN);


void SimCom::init(){
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
bool Sim800l::reset(){
  digitalWrite(RESET_PIN,1);
  delay(1000);
  digitalWrite(RESET_PIN,0);
  delay(1000);
  // wait for the module response

  SIM.print(F("AT\r\n"));
  _timeout=0;
  while (_readSerial().indexOf("OK")==-1){
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
  while (_readSerial().indexOf("SMS")==-1 ){
  } 
  return true;
}

/***************************************************/
