//Arduino code
#include <SoftwareSerial.h>

void sendDataV(String data);
void setupSerial();
String readSData();

SoftwareSerial s(6,7);
 
void setupSerial() {
s.begin(9600);
}
 
void sendDataV(String data) {
//int data=50;
if(s.available()>0)
{
 s.write(data.c_str());
}
}

String readSData(){
  String data;
  if (s.available()>0)
  {
    data=String(s.readString());
    Serial.println(data);
    return data;
  }
  else{
    return String("");
  }
  
}
