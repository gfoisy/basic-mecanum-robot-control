#include "functionlist.h"

directionVector robotVector;

int i=0;

void setup() {
  battery_setup();
  bluetoothSetup();
  motorSetup();
  time2=millis();
  stepperStepsPerQuery=200;
}




void loop() {

if (Serial1.available()>0)
  {
  interperetBluetooth();     //takes the bluetooth chars and maps them to a unit velocity vector and intensity in class directionVector
  }   
//else //--maybe decelerate or something if disconnected.


//bluetoothDebug();

calculateStepperSpeeds();    //With the robot velocity's direction, rotation, and intensity , calculate and set the direction and speed for the stepper motors//


while(i<stepperStepsPerQuery){
  actuateSteppers();             //Jump through hoops here to set up the steppers to execute properly with the timing and stuff. have calculateSpeeds be more pure
  i++;                            //send the steppers their commands
};

 i=0;
 
//i++;
//time1=micros();
//if(i==5000){
//  Serial.println(time2-time1);
//  i=0;
//}

//time2=time1;


     
//if( time1>(time2+5000)){      //check the battery occationally
//
//   time2=time1;
//}

}
 
