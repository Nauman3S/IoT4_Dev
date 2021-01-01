/*
 * Simple demo, should work with any driver board
 *
 * Connect STEP, DIR as indicated
 *
 * Copyright (C)2015-2017 Laurentiu Badea
 *
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#include <Arduino.h>
#include "BasicStepperDriver.h"

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 120

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR1 4
#define STEP1 3
#define SLEEP1 2

#define DIR2 9
#define STEP2 8
#define SLEEP2 5

#define DIR3 12
#define STEP3 11
#define SLEEP3 10

#define DIR4 A3
#define STEP4 A2
#define SLEEP4 A1

#define DIR5 A4
#define STEP5 A5
#define SLEEP5 A6


#define DIR6 6
#define STEP6 7
#define SLEEP6 A7
// 2-wire basic config, microstepping is hardwired on the driver
BasicStepperDriver stepper1(MOTOR_STEPS, DIR1, STEP1);
BasicStepperDriver stepper2(MOTOR_STEPS, DIR2, STEP2);
BasicStepperDriver stepper3(MOTOR_STEPS, DIR3, STEP3);
BasicStepperDriver stepper4(MOTOR_STEPS, DIR4, STEP4);
BasicStepperDriver stepper5(MOTOR_STEPS, DIR5, STEP5);
BasicStepperDriver stepper6(MOTOR_STEPS, DIR6, STEP6);

//Uncomment line to use enable/disable functionality
//BasicStepperDriver stepper(MOTOR_STEPS, DIR, STEP, SLEEP);

void setupSteppers() {
    stepper1.begin(RPM, MICROSTEPS);
    stepper2.begin(RPM, MICROSTEPS);
    stepper3.begin(RPM, MICROSTEPS);
    stepper4.begin(RPM, MICROSTEPS);
    stepper5.begin(RPM, MICROSTEPS);
    stepper6.begin(RPM, MICROSTEPS);
    // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
    // stepper.setEnableActiveState(LOW);
}

void MoveSteppers(int n, int dir) {
  
    // energize coils - the motor will hold position
    // stepper.enable();;
  
    /*
     * Moving motor one full revolution using the degree notation
     */
    if(n==1){
        if(dir==1){
            stepper1.rotate(360);
        }
    /*
     * Moving motor to original position using steps
     */
    else if(dir==2){
    stepper1.move(-MOTOR_STEPS*MICROSTEPS);
    }
    else if(dir==3){
        stepper1.disable();
    }
    else if(dir==4){
        stepper1.enable();
    }
    }
    // pause and allow the motor to be moved by hand
    // stepper.disable();;

    else if(n==2){
        if(dir==1){
    stepper2.rotate(360);
        }
    /*
     * Moving motor to original position using steps
     */
    else if(dir==2){
    stepper2.move(-MOTOR_STEPS*MICROSTEPS);
    }
    else if(dir==3){
        stepper2.disable();
    }
    else if(dir==4){
        stepper2.enable();
    }
    }


    else if(n==3){
        if(dir==1){
    stepper3.rotate(360);
        }
    /*
     * Moving motor to original position using steps
     */
    else if(dir==2){
    stepper3.move(-MOTOR_STEPS*MICROSTEPS);
    }
    else if(dir==3){
        stepper3.disable();
    }
    else if(dir==4){
        stepper3.enable();
    }
    }



    else if(n==4){
        if(dir==1){
    stepper4.rotate(360);
        }
    /*
     * Moving motor to original position using steps
     */
    else if(dir==2){
    stepper4.move(-MOTOR_STEPS*MICROSTEPS);
    }
    else if(dir==3){
        stepper4.disable();
    }
    else if(dir==4){
        stepper4.enable();
    }
    }


    else if(n==5){
        if(dir==1){
    stepper5.rotate(360);
        }
    /*
     * Moving motor to original position using steps
     */
    else if(dir==2){
    stepper5.move(-MOTOR_STEPS*MICROSTEPS);
    }
    else if(dir==3){
        stepper5.disable();
    }
    else if(dir==4){
        stepper5.enable();
    }
    }



    else if(n==6){
        if(dir==1){
    stepper6.rotate(360);
        }
    /*
     * Moving motor to original position using steps
     */
    else if(dir==2){
    stepper6.move(-MOTOR_STEPS*MICROSTEPS);
    }
    else if(dir==3){
        stepper6.disable();
    }
    else if(dir==4){
        stepper6.enable();
    }
    }
}