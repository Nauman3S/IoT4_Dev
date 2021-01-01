

#include "MQTTHandler.h"
#include "ANSerialHandler.h"
#include "SStack.h"

String msgS1="";
String msgS2="";

float sonar1=0.0;
float sonar2=0.0;
String nameRFID="";


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String SWV="";
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    SWV=SWV+String((char)payload[i]);
  }
  Serial.println();
  String MicroSW=SWV;
  if(MicroSW==String("true")){
    //shrink
    sendDataS2("StartDeaccelerate");
    sendDataS2("deaccelerate");
    sendDataS2("Startconveyor");
    sendDataS2("conveyorBackward");//move back
  }
  
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  setupSerials();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  }

//*****************************************************************************************//
void loop() {

  
   // Serial.println("no new card");
     if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  msgS1=readS1Data();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    ++value;
    if(msgS1!=String("")){

    sonar1=StringSeparator(msgS1,';',0).toFloat();
    sonar2=StringSeparator(msgS1,';',1).toFloat();
    nameRFID=StringSeparator(msgS1,';',2);
    if(nameRFID!=String("")){
      sendDataS2("StartAccelerate");
      sendDataS2("accelerate");
      sendDataS2("StartStayparallel");
      sendDataS2("stayparallel");
      sendDataS2("Startconveyor");
      sendDataS2("conveyorForward");
      sendDataS2("StartrotationalClock");
      sendDataS2("rotationalantiClock");
    }
    else{
      sendDataS2("deaccelerate");
      sendDataS2("StopAccelerate");
      sendDataS2("StopStayparallel");
      sendDataS2("conveyorBackward");
      sendDataS2("Stopconveyor");
      sendDataS2("StoprotationalClock");

    }
    SendValue("out/rider/a",msgS1);
    
    
    }

    if(msgS2!=String("")){

    
    
    SendValue("out/rider/b",msgS2);
    
    }
    SendValue("out/rider/r_id",String(WiFi.macAddress()));
  }

  
  }

  
  
