#include "functionlist.h"

directionVector robotVector;

void setup() {
  battery_setup();
  bluetoothSetup();
  motorSetup();
  time2=millis();
}

void loop() {
//Serial.println(Serial1.available());

//if (Serial1.available()>0)
//  {
//  interperetBluetooth();     //takes the bluetooth chars and maps them to a unit velocity vector and intensity in class directionVector
//  }                          //else --maybe decelerate or something if disconnected.

bluetoothDebug();

calculateStepperSpeeds();    //With the robot velocity's direction, rotation, and intensity , calculate and set the direction and speed for the stepper motors//

actuateSteppers();           //Jump through hoops here to set up the steppers to execute properly with the timing and stuff. have calculateSpeeds be more pure
                             //send the steppers their commands

time1=millis();           
if( time1>(time2+5000)){      //check the battery every once and a while

}

}
 
