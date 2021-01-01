
#include "SerialHandler.h"
#include "MPU6050Handler.h"
#include "StepperH.h"
void setup() {
  Serial.begin(9600);    // Initialize serial communications with the PC
  setupSerial();
  setupMPU6050();
  setupSteppers();

}

unsigned long previousMillis = 0;   
int long interval = 1000;   
int ParallelstepperPos=1;
int ParallelstepperPos2=1;
void loop() {
    String dataA = "";
    dataA=getMPU605Data();
    sendDataV(dataA);
    String DataIncoming=readSData();
    if(DataIncoming!=""){
      if(DataIncoming.indexOf("accelerate")>=0){//expand
       MoveSteppers(1,1);
      }
      else if(DataIncoming.indexOf("StartAccelerate")>=0){//shrink
       MoveSteppers(1,4);//enable
      }
      else if(DataIncoming.indexOf("StopAccelerate")>=0){//shrink
       MoveSteppers(1,3);//disable
      }
      else if(DataIncoming.indexOf("deaccelerate")>=0){//shrink
       MoveSteppers(2,2);
      }
      else if(DataIncoming.indexOf("StartDeaccelerate")>=0){//shrink
       MoveSteppers(2,4);//enable
      }
      else if(DataIncoming.indexOf("StopDeaccelerate")>=0){//shrink
       MoveSteppers(2,3);//disable
      }
      else if(DataIncoming.indexOf("StartStayparallel")>=0){
          MoveSteppers(3,4);
          MoveSteppers(4,4);
      }
      else if(DataIncoming.indexOf("StopStayparallel")>=0){
        MoveSteppers(3,3);
          MoveSteppers(4,3);
      }
      else if(DataIncoming.indexOf("stayparallel")>=0){
       if(getGX()!=0){
         unsigned long currentMillis = millis();
         if (currentMillis - previousMillis >= interval) {
           ParallelstepperPos=2;
          interval=interval+500;

          if(interval>=5000){
            interval=1000;
            ParallelstepperPos=1;
          }
          previousMillis = currentMillis;
         }
         MoveSteppers(3,ParallelstepperPos);
          
       }

       if(getGY()!=0){
         unsigned long currentMillis = millis();
         if (currentMillis - previousMillis >= interval) {
           ParallelstepperPos2=2;
          interval=interval+500;

          if(interval>=5000){
            interval=1000;
            ParallelstepperPos2=1;
          }
          previousMillis = currentMillis;
         }
         MoveSteppers(4,ParallelstepperPos2);
          
       }
       
      }
      else if(DataIncoming.indexOf("Startconveyor")>=0){//shrink
       MoveSteppers(5,4);
      }
      else if(DataIncoming.indexOf("Stopconveyor")>=0){//exapnd
       MoveSteppers(5,3);
      }
      else if(DataIncoming.indexOf("conveyorForward")>=0){//
       MoveSteppers(5,1);
      }
     
      else if(DataIncoming.indexOf("conveyorBackward")>=0){//
       MoveSteppers(5,2);
      }
      else if(DataIncoming.indexOf("StartrotationalClock")>=0){
          MoveSteppers(6,4);
      }
      else if(DataIncoming.indexOf("StoprotationalClock")>=0){
          MoveSteppers(6,3);
      }
      else if(DataIncoming.indexOf("rotationalClock")>=0){//
       MoveSteppers(6,1);
      }

      else if(DataIncoming.indexOf("rotationalantiClock")>=0){//
       MoveSteppers(6,2);
      }
    }
}
