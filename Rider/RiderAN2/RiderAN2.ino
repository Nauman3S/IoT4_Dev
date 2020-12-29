
#include "SerialHandler.h"
#include "MPU6050Handler.h"

void setup() {
  Serial.begin(9600);    // Initialize serial communications with the PC
  setupSerial();
  setupMPU6050();


}


void loop() {
    String dataA = "";
    dataA=getMPU605Data();
    sendDataV(dataA);
    String DataIncoming=readSData();
    if(DataIncoming!=""){
      if(DataIncoming.indexOf("forward")>=0){
       
      }
     
      
    }
}
