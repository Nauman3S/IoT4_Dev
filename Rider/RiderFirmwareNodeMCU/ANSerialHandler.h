#include <SoftwareSerial.h>

#define RX_1 D3
#define TX_1 D4

#define RX_2 D5
#define TX_2 D6

void setupSerials();
String readS1Data();
String readS2Data();
void sendDataS2(String data);
void sendDataS1(String data);

SoftwareSerial s1(RX_1,TX_1);//RX,TX
SoftwareSerial s2(RX_2,TX_2);//RX,TX
//int data;
void setupSerials(){

  s1.begin(9600);
  s2.begin(9600);
}

String readS1Data(){
  String data;
  if (s1.available()>0)
  {
    data=String(s1.readString());
    Serial.println(data);
    return data;
  }
  else{
    return String("");
  }
  
}

String readS2Data(){
  String data;
  if (s2.available()>0)
  {
    data=String(s2.readString());
    Serial.println(data);
    return data;
  }
  else{
    return String("");
  }
  
}

void sendDataS1(String data){
  s1.write(data.c_str());
}

void sendDataS2(String data){
  s2.write(data.c_str());
}
