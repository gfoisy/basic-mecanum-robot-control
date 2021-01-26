#include "functionlist.h"

directionVector robotVector;



void setup() {
  battery_setup();
  bluetoothSetup();
  motorSetup();
  time2=millis();
  stepperStepsPerQuery=200;
  i=0;
}




void loop() {

if (Serial1.available()>0)
  {
  interperetBluetooth();     //takes the bluetooth chars and maps them to a unit velocity vector and intensity in class directionVector
  }   
//else //--maybe decelerate or something if disconnected.


//bluetoothDebug();

calculateUpcomingSpeeds();    //With the robot velocity's direction, rotation, and intensity , calculate and set the direction and speed for the stepper motors//

engageMotion();

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
 
