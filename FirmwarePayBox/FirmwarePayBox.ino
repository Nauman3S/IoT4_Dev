
#include "MQTTHandler.h"
#define microSW D4
String msgP="";
String msgP_e_id="";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    
  }
  Serial.println();

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
  pinMode(D4,INPUT_PULLUP);
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
  if (now - lastMsg > 1000) {
    lastMsg = now;
    ++value;
    int SW=digitalRead(microSW);
    if(SW==0){
      msgP=String("true");
    }
    else{
      msgP=String("false");
    }

    
    if(msgP!=String("")){
    SendValue("out/paybox/a",msgP);
    //msgP="";
    }
    
   
    SendValue("out/paybox/p_id",String(WiFi.macAddress()));
  }

  
  }

  
  
