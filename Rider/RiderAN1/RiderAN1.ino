/*
   Initial Author: ryand1011 (https://github.com/ryand1011)

   Reads data written by a program such as "rfid_write_personal_data.ino"

   See: https://github.com/miguelbalboa/rfid/tree/master/examples/rfid_write_personal_data

   Uses MIFARE RFID card using RFID-RC522 reader
   Uses MFRC522 - Library
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D8         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D9        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
*/

#include <SPI.h>
#include <MFRC522.h>
#include "SerialHandler.h"
#include "DCDriver.h"
#include "AsyncSonar.h"


#define RST_PIN         8         // Configurable, see typical pin layout above
#define SS_PIN          9          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance
float Sonar1 = 0.00;
float Sonar2 = 0.00;
String nameS = "";
char buf1[18];
//*****************************************************************************************//


void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  setupSerial();
  setupMotor1();
  setupMotor2();
  setupSonar();
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read

}

//*****************************************************************************************//
void loop() {

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    Sonar1 = loopSonar1();
    Sonar2 = loopSonar2();
    Serial.println(Sonar1);
    Serial.println(Sonar2);
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
    nameS="";
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {

    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------



  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------

  Serial.print(F("Name: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));

    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);


    }
  }
  for (uint8_t i = 0; i < 16; i++) { //cleaning the output
    if (buffer1[i] == ' ') {
      buffer1[i] = '\0';
      break;
    }
  }
  char str[(sizeof buffer1) + 1];
  memcpy(str, buffer1, sizeof buffer1);
  str[sizeof buffer1] = 0; // Null termination
  nameS = nameS + (String(str));
  Serial.print(" ");

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  nameS = nameS + String(" ");
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );

  }

  for (uint8_t i = 0; i < 16; i++) { //cleaning the output
    if (buffer2[i] == ' ') {
      buffer2[i] = '\0';
      break;
    }
  }
  char str2[(sizeof buffer2) + 1];
  memcpy(str2, buffer2, sizeof buffer2);
  str2[sizeof buffer2] = 0; // Null termination
  nameS = nameS + (String(str2));


  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));

  Serial.println(nameS);
  //nameS=String("");
  delay(1000); //change value if you want to read cards faster


  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

//*****************************************************************************************//
