//This file takes information from velocity and directly applies them to the motors. There should be no calculations in this file, just motor control

#include "functionlist.h"
#include <AccelStepper.h>  //https://www.airspayce.com/mikem/arduino/AccelStepper/

float Aspeed, Bspeed, Cspeed, Dspeed;

//   motorlayout
//    FRONT
//   A-----B
//   |     |
//   |     |
//   C-----D
//     REAR
// A->B = 270mm (from center plane of wheel)
// A->C = 200mm (axle to axle)
// Wheel diameter = 120mm

// setting up pins for the steppers
#define stepA 22
#define dirA 23

#define stepB 24
#define dirB 25

#define stepC 26
#define dirC 27

#define stepD 28
#define dirD 29

#define power 52;




//constructing the stepper objects

   AccelStepper stepperA( AccelStepper::DRIVER, stepA, dirA);
   AccelStepper stepperB( AccelStepper::DRIVER, stepB, dirB);
   AccelStepper stepperC( AccelStepper::DRIVER, stepC, dirC);
   AccelStepper stepperD( AccelStepper::DRIVER, stepD, dirD);
 
   float maxSpeed=3000;

// AccelStepper stepperA(4, in1A, in2A, in3A, in4A);  //4 or FULL4WIRE?
// AccelStepper stepperA(AccelStepper::FULL4WIRE, in1A, in2A, in3A, in4A);
// AccelStepper stepperB(AccelStepper::FULL4WIRE, in1B, in2B, in3B, in4B);
// AccelStepper stepperC(AccelStepper::FULL4WIRE, in1C, in2C, in3C, in4C);
// AccelStepper stepperD(AccelStepper::FULL4WIRE, in1D, in2D, in3D, in4D);

  
/////////////////////////////////////////////////////////////////
void motorSetup(){ 
  pinMode(52, OUTPUT);

  stepperA.setMaxSpeed(maxSpeed);  //in steps per seccond //"High" steps/second is 2000 to 3000--mecatronics uses 3000 setps per second--NOT RPM, and that requires very fast waveforms and fast magnetic field changes, so the stepper driver AND PROCESSOR SPEED is critical for high speeds. 
  stepperB.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepperC.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepperD.setMaxSpeed(maxSpeed);  //in steps per seccond

}


/*
 * 
 * With the velocity vector and intensity , calculate the direction and speed for the stepper motors 
 */

void calculateStepperSpeeds(){
  //take velocityVector and intensity and calculates speeds and directions for the motors
  //can use trig values, Apparently they are in a lookup table written in machine code, should be plenty fast

  Aspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi)+robotVector.get_rotationAngle());  //calculates a speed for each stepper based on the limit set by max speed*intensity. The remainder of the equaition calculates the stepper power to achieve robot's desired direction and rotation
  Bspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi)-robotVector.get_rotationAngle());   //alternating wheels match speed and rotation when the robot is translating and not rotating
  Cspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi)+robotVector.get_rotationAngle());  //the rotation angle will adjust motor output so that rotation and translation should happen at the same time,
  Dspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi)-robotVector.get_rotationAngle());  // while staying below the motor's limits

  //applying the proper speeds to the steppers needs to be in actuateSteppers after cetCurrentPosition()
  stepperA.setSpeed(Aspeed);//Aspeed
//  stepperB.setSpeed(Bspeed);//Bspeed
//  stepperC.setSpeed(Cspeed);//Cspeed   500 is decently strong
//  stepperD.setSpeed(Dspeed);

//  stepperA.moveTo(stepperA.currentPosition()+stepperStepsPerQuery);

//  Serial.print(stepperA.currentPosition()+stepperStepsPerQuery);
//  Serial.print("  intensity:");Serial.print(robotVector.get_intensity()); Serial.print(" Aspeed:");Serial.println(Aspeed);
}




/*
 * With the speeds and directions calculated, this function jumps through the hoops to run them
 * it needs to be called every loop because the library can only move the motors by one step
 * 
 */

void actuateSteppers(){
//  Serial.print("intensity here:");Serial.print(robotVector.get_intensity()); Serial.print(" Bspeed:");Serial.println(Bspeed);

if(motorsEnabled){
  digitalWrite(52, HIGH); //enabling motors

  
  stepperA.runSpeed();  //use runSpeed?
//  stepperB.runSpeed();
//  stepperC.runSpeed();
//  stepperD.runSpeed();
}else{
 digitalWrite(52, LOW);
}


}
