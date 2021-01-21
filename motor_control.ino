//This file takes information from velocity and directly applies them to the motors. There should be no calculations in this file, just motor control

#include "functionlist.h"
#include <AccelStepper.h>  //https://www.airspayce.com/mikem/arduino/AccelStepper/

float Aspeed, Bspeed, Cspeed, Dspeed;
int currentLimit;

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
#define in1A 23
#define in2A 25
#define in3A 27
#define in4A 29
#define enAA 2
#define enBA 3

#define in1B 31
#define in2B 33
#define in3B 35
#define in4B 37
#define enAB 4
#define enBB 5

#define in1C 22
#define in2C 24
#define in3C 26
#define in4C 28
#define enAC 6
#define enBC 7

#define in1D 30
#define in2D 32
#define in3D 34
#define in4D 36
#define enAD 8
#define enBD 9


//constructing the stepper objects
 AccelStepper stepperA(AccelStepper::FULL4WIRE, in1A, in2A, in3A, in4A);
 AccelStepper stepperB(AccelStepper::FULL4WIRE, in1B, in2B, in3B, in4B);
 AccelStepper stepperC(AccelStepper::FULL4WIRE, in1C, in2C, in3C, in4C);
 AccelStepper stepperD(AccelStepper::FULL4WIRE, in1D, in2D, in3D, in4D);
 float maxSpeed=1500;
  
/////////////////////////////////////////////////////////////////
void motorSetup(){ 
  stepperA.setMaxSpeed(maxSpeed);  //in steps per seccond //"High" steps/second is 2000 to 3000--mecatronics uses 3000 setps per second--NOT RPM, and that requires very fast waveforms and fast magnetic field changes, so the stepper driver AND PROCESSOR SPEED is critical for high speeds. 
  
  stepperB.setMaxSpeed(maxSpeed);  //in steps per seccond

  stepperC.setMaxSpeed(maxSpeed);  //in steps per seccond

  stepperD.setMaxSpeed(maxSpeed);  //in steps per seccond

  currentLimit=200;                // 1-255; setting up the pwm to make the enable pins output less power throught eh driver, hopefully lowering the temps.
  //TEST THIS AT 0 TO SEE IF IT HAS AN EFFECT

//for (int i=2; i<10;i++){
//  pinMode(i, OUTPUT);
//}

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  analogWrite(enAA,currentLimit);
  analogWrite(enBA,currentLimit);
  analogWrite(enAB,currentLimit);
  analogWrite(enBB,currentLimit);
  analogWrite(enAC,currentLimit);
  analogWrite(enBC,currentLimit);
  analogWrite(enAD,currentLimit);
  analogWrite(enBD,currentLimit);




}




/*
 * 
 * With the velocity vector and intensity , calculate the direction and speed for the stepper motors 
 * this should take into account the time spent between bluetooths interactions and stuff
 */

void calculateStepperSpeeds(){
  //take velocityVector and intensity and calculates speeds and directions for the motors
  //can use trig values, Apparently they are in a lookup table written in machine code, should be plenty fast



  //probably works, does not include rotation
//  Aspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi));  //will need to combine with robot's rotation speed here too
//  Bspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi));  //alternating wheels match speed and rotation when the robot is translating and not rotating
//  Cspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi));
//  Dspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi));

  Aspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi)+robotVector.get_rotationAngle());  //calculates a speed for each stepper based on the limit set by max speed*intensity. The remainder of the equaition calculates the stepper power to achieve robot's desired direction and rotation
  Bspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi)-robotVector.get_rotationAngle());   //alternating wheels match speed and rotation when the robot is translating and not rotating
  Cspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.75*pi)+robotVector.get_rotationAngle());  //the rotation angle will adjust motor output so that rotation and translation should happen at the same time,
  Dspeed=maxSpeed*robotVector.get_intensity()*cos(robotVector.get_velocityAngle()-(.25*pi)-robotVector.get_rotationAngle());  // while staying below the motor's limits

  //applying the proper speeds to the steppers needs to be in actuateSteppers after cetCurrentPosition()
  

}

/*
 * With the speeds and directions calculated, this function jumps through the hoops to run them
 * it needs to be called every loop because the library can only move the motors by one step
 * 
 * how??
 */

void actuateSteppers(){
//  //set positions to zero -- 
//  stepperA.setCurrentPosition(0); //it also zeros the current motor speed
//  stepperB.setCurrentPosition(0);
//  stepperC.setCurrentPosition(0);
//  stepperD.setCurrentPosition(0);
  
  //de-zeroing the motor speed. 
  stepperA.setSpeed(Aspeed); //this may not be able to go negative...
  stepperB.setSpeed(Bspeed);
  stepperC.setSpeed(Cspeed);
  stepperD.setSpeed(Dspeed);

  
  //set positions to positive or negative values based on the angle--is this nessisary, speeds are already negated
  // these values hsould be higher than the steppers can travel in one loop
//  stepperA.move(1000);   //documentation says to call setspeed after move or moveTo. I believe this code takes care of that, but it would be best to keep it in mind
//  stepperB.move(1000);
//  stepperC.move(1000);
//  stepperD.move(1000);
  
//for moving steppers
//  runSpeedToPosition?
//  runSpeed -Poll the motor and step it if a step is due, implementing a constant speed as set by the most recent call to setSpeed(). You must call this as frequently as possible, but at least once per step interval, 
//  run -same as runSpeed, but it has acceleration and deceleration built in

  stepperA.runSpeed();
  stepperB.runSpeed();
  stepperC.runSpeed();
  stepperD.runSpeed();
  Serial.println(Aspeed);
  
}
