#include "functionlist.h"

directionVector robotVector;



void setup() {
  Battery_setup();
  bluetoothSetup();
  motorSetup();
  time2=millis();
  stepperStepsPerQuery=200;
//  i=0;
}




void loop() {


  
if (Serial1.available()>0)// 
  {
  interperetBluetooth();     //takes the bluetooth chars and maps them to a unit velocity vector and intensity in class directionVector
  }   

//bluetoothDebug();

calculateUpcomingSpeeds();    //With the robot velocity's direction, rotation, and intensity , calculate and set the direction and speed for the stepper motors//

engageMotion();


time1=millis();
  
if( time1>(time2+30)){      //check the battery occationally
   checkBattery();
   time2=time1;
}

}
 
