//This file takes information from velocity and directly applies them to the motors. There should be no calculations in this file, just motor control

#include "functionlist.h"
#include <AccelStepper.h>  //https://www.airspayce.com/mikem/arduino/AccelStepper/

float upcomingSpeed[4], distance[4];


//   motorlayout
//    FRONT
//    (0)----(1)
//     |      |
//     |      |
//    (2)----(3)
//     REAR
// 0->1 = 270mm (from center plane of wheel)
// 0->2 = 200mm (axle to axle)
// Wheel diameter = 120mm

// setting up pins for the steppers
#define step0 23
#define dir0 22

#define step1 25
#define dir1 24

#define step2 27
#define dir2 26

#define step3 29
#define dir3 28

#define power 52;




//constructing the stepper objects
   AccelStepper stepper0( AccelStepper::DRIVER, step0, dir0);
   AccelStepper stepper1( AccelStepper::DRIVER, step1, dir1);
   AccelStepper stepper2( AccelStepper::DRIVER, step2, dir2);
   AccelStepper stepper3( AccelStepper::DRIVER, step3, dir3);

   float maxSpeed=500;
   int accel=10000; //5000 works


  
/////////////////////////////////////////////////////////////////
void motorSetup(){ 
  pinMode(52, OUTPUT);  //THIS PIN NEEDS TO BE SET AT HIGH TO ENABLE THE MOTORS

  stepper0.setMaxSpeed(maxSpeed);  //in steps per seccond //"High" steps/second is 2000 to 3000--mecatronics uses 3000 setps per second--NOT RPM, and that requires very fast waveforms and fast magnetic field changes, so the stepper driver AND PROCESSOR SPEED is critical for high speeds. 
  stepper1.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepper2.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepper3.setMaxSpeed(maxSpeed);  //in steps per seccond

  stepper0.setAcceleration(accel);
  stepper1.setAcceleration(accel);
  stepper2.setAcceleration(accel);
  stepper3.setAcceleration(accel);
  
  stepper0.setSpeed(0);  
  stepper1.setSpeed(0);
  stepper2.setSpeed(0);
  stepper3.setSpeed(0);

    stepper0.setPinsInverted(true,false,false);
    stepper1.setPinsInverted(true,false,false);

}


/*
 * 
 * With the velocity vector and intensity , calculate the direction and speed for the stepper motors 
 */

void calculateUpcomingSpeeds(){
  //take velocityVector and intensity and calculates speeds and directions for the motors
  //can use trig values, Apparently they are in a lookup table written in machine code, should be plenty fast
  upcomingSpeed[0]=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi)+robotVector.get_rotationAngle());  //calculates a speed for each stepper based on the limit set by max speed*intensity. The remainder of the equaition calculates the stepper power to achieve robot's desired direction and rotation
  upcomingSpeed[1]=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi)-robotVector.get_rotationAngle());   //alternating wheels match speed and rotation when the robot is translating and not rotating
  upcomingSpeed[2]=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi)+robotVector.get_rotationAngle());  //the rotation angle will adjust motor output so that rotation and translation should happen at the same time,
  upcomingSpeed[3]=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi)-robotVector.get_rotationAngle());  // while staying below the motor's limits

  stepper0.move(isPos(upcomingSpeed[0])*10000);
  stepper1.move(isPos(upcomingSpeed[1])*10000);
  stepper2.move(isPos(upcomingSpeed[2])*10000);
  stepper3.move(isPos(upcomingSpeed[3])*10000);

  stepper0.setSpeed(upcomingSpeed[0]);  
  stepper1.setSpeed(upcomingSpeed[1]);
  stepper2.setSpeed(upcomingSpeed[2]);
  stepper3.setSpeed(upcomingSpeed[3]);

}


/*
 * 
 */
 
void engageMotion(){
 
 if(motorsEnabled)
 {
    digitalWrite(52, HIGH); //enabling motors  
    actuateSteppers();
 }
 else
 {
//   Serial.print("off");
   digitalWrite(52, LOW);
 }

 }


int isPos(float speedIn){
  if(speedIn>0){return 1;}
  else if(speedIn<0){return -1;}
  else{return 0;};
}

void actuateSteppers(){ // the difference in speed is divided by this factor before added to the previous speed. As this factor shrinks, it will ramp the steppers to the desired speed
//  Serial.print("upcoming  "); Serial.print(upcomingSpeed[0]);Serial.print("past  ");Serial.print(pastSpeed[0]);(Serial.println(rampDist[0]/rampFactor));//Serial.print(robotVector.get_intensity()); Serial.print(" upcomingSpeed[1]:");Serial.println(upcomingSpeed[1]);

  stepper0.run();  //use runSpeed?
  stepper1.run();
  stepper2.run();
  stepper3.run();

}
