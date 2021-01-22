#include "functionlist.h"

directionVector robotVector;

void setup() {
  battery_setup();
  bluetoothSetup();
  motorSetup();
  time2=millis();
}


/*
 * make a stopping function that isn't setting intensity to zero
 * double check speed numbers agains themselves for symmetry
 * 
 * battery meter
 * 
 */



void loop() {

if (Serial1.available()>0)
  {
  interperetBluetooth();     //takes the bluetooth chars and maps them to a unit velocity vector and intensity in class directionVector
  }                          //else --maybe decelerate or something if disconnected.


calculateStepperSpeeds();    //With the robot velocity's direction, rotation, and intensity , calculate and set the direction and speed for the stepper motors//

actuateSteppers();           //Jump through hoops here to set up the steppers to execute properly with the timing and stuff. have calculateSpeeds be more pure
                             //send the steppers their commands

       
//if( time1>(time2+5000)){      //check the battery occationally
//
//   time2=time1;
//}



//Serial.print("velocity angle:"); Serial.print(robotVector.get_velocityAngle());
//Serial.print("rotation angle:"); Serial.print(robotVector.get_rotationAngle()); 
//Serial.print("intensity:"); Serial.println(robotVector.get_intensity()); 


//bluetoothDebug();
}
 
