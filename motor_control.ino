//This file takes information from velocity and directly applies them to the motors. There should be no calculations in this file, just motor control

#include "functionlist.h"
#include <AccelStepper.h>  //https://www.airspayce.com/mikem/arduino/AccelStepper/

float Aspeed, Bspeed, Cspeed, Dspeed;

//   motorlayout
//   A-----B
//   |     |
//   |     |
//   C-----D
// A->B = 270mm (from center plane of wheel)
// A->C = 200mm (axle to axle)
// Wheel diameter = 120mm

// setting up pins for the steppers
#define in1A 31
#define in2A 32
#define in3A 33
#define in4A 34

#define in1B 99
#define in2B 99
#define in3B 99
#define in4B 99

#define in1C 99
#define in2C 99
#define in3C 99
#define in4C 99

#define in1D 99
#define in2D 99
#define in3D 99
#define in4D 99

float maxSpeed=50.0;

//constructing the stepper objects
 AccelStepper stepperA(AccelStepper::FULL4WIRE, in1A, in2A, in3A, in4A);
 AccelStepper stepperB(AccelStepper::FULL4WIRE, in1B, in2B, in3B, in4B);
 AccelStepper stepperC(AccelStepper::FULL4WIRE, in1C, in2C, in3C, in4C);
 AccelStepper stepperD(AccelStepper::FULL4WIRE, in1D, in2D, in3D, in4D);

/////////////////////////////////////////////////////////////////
void motorSetup(){ 
  stepperA.setMaxSpeed(maxSpeed);  //in steps per seccond //"High" steps/second is 2000 to 3000--mecatronics uses 3000 setps per second--NOT RPM, and that requires very fast waveforms and fast magnetic field changes, so the stepper driver AND PROCESSOR SPEED is critical for high speeds. 
  stepperA.setAcceleration(100.0);
  
  stepperB.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepperB.setAcceleration(100.0);

  stepperC.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepperC.setAcceleration(100.0);

  stepperD.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepperD.setAcceleration(100.0);
}



/*
 * 
 * With the velocity vector and intensity , calculate the direction and speed for the stepper motors 
 * this should take into account the time spent between bluetooths interactions and stuff
 */

void calculateStepperSpeeds(){
  //take velocityVector and intensity and calculates speeds and directions for the motors
  //can use sin/cos values Apparently they are in a lookup table written in machine code, should be plenty fast
  
  Aspeed=cos(robotVector.get_velocityAngle()-(.25*pi));  //will need to combine with robot's rotation speed here too
  Bspeed=cos(robotVector.get_velocityAngle()-(.75*pi));  //alternating wheels match speed and rotation when the robot is translating and not rotating
  Cspeed=cos(robotVector.get_velocityAngle()-(.75*pi));
  Dspeed=cos(robotVector.get_velocityAngle()-(.25*pi));
  
  stepperA.setSpeed(Aspeed);
  stepperB.setSpeed(Bspeed);
  stepperC.setSpeed(Cspeed);
  stepperD.setSpeed(Dspeed);

}


void actuateSteppers(){

}
