
#include "SerialHandler.h"



void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  setupSerial();


}

//*****************************************************************************************//
void loop() {
    String dataA = String(Sonar1) + String(";") + String(Sonar2) + String(";") + nameS;
    sendDataV(dataA);
    String DataIncoming=readSData();
    if(DataIncoming!=""){
      if(DataIncoming.indexOf("forward")>=0){
        Forward(1);
        Forward(2);
      }
      else if(DataIncoming.indexOf("reverse")>=0){
        Reverse(1);
        Forward(2);
      }

      else if(DataIncoming.indexOf("stop")>=0){
        StopAll();
        
      }
    }
}

//*****************************************************************************************//
