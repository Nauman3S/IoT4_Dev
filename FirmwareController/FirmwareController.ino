
#include "MQTTHandler.h"

String msgE="";
String msgE_e_id="";
String msgP_p_id="";
String msgR_r_id="";
String msgR="";
String msgP="";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    if(String(topic)==String("out/et/a")){
    msgE=msgE+String((char)payload[i]);
    }
    else if(String(topic)==String("out/et/e_id")){
      msgE_e_id=msgE_e_id+String((char)payload[i]);
    }
    else if(String(topic)==String("out/rider/a")){
      msgR=msgR+String((char)payload[i]);
    }
    else if(String(topic)==String("out/paybox/a")){
      msgP=msgP+String((char)payload[i]);
    }
    else if(String(topic)==String("out/paybox/p_id")){
      msgP_p_id=msgP_p_id+String((char)payload[i]);
    }
    else if(String(topic)==String("out/rider/r_id")){
      msgR_r_id=msgR_r_id+String((char)payload[i]);
    }
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
    
    if(msgR!=String("")){
    SendValue("out/controller/rider",msgR);
    msgR="";
    }
    if(msgE_e_id!=String("")){
    SendValue("out/controller/r_id",msgR_r_id);
    msgR_r_id="";
    }
    if(msgE!=String("")){
    SendValue("out/controller/entrance",msgE);
    msgE="";
    }
    if(msgP!=String("")){
    SendValue("out/controller/paybox",msgP);
    msgP="";
    }
    if(msgE_e_id!=String("")){
    SendValue("out/controller/e_id",msgE_e_id);
    msgE_e_id="";
    }
    if(msgP_p_id!=String("")){
    SendValue("out/controller/p_id",msgP_p_id);
    msgP_p_id="";
    }
    if(msgR_r_id!=String("")){
    SendValue("out/controller/r_id",msgR_r_id);
    msgR_r_id="";
    }
    SendValue("out/controller/c_id",String(WiFi.macAddress()));
  }

  
  }

  
  
