//This file takes information from velocity and directly applies them to the motors. There should be no calculations in this file, just motor control

#include "functionlist.h"
#include <AccelStepper.h>  //https://www.airspayce.com/mikem/arduino/AccelStepper/

float upcomingSpeed[4], pastSpeed[4], rampDist[4];
int rampFactor;

//   motorlayout
//    FRONT
//   A(0)-----B(1)
//     |     |
//     |     |
//   C(2)-----D(3)
//     REAR
// A->B = 270mm (from center plane of wheel)
// A->C = 200mm (axle to axle)
// Wheel diameter = 120mm

// setting up pins for the steppers
#define step0 22
#define dir0 23

#define step1 24
#define dir1 25

#define step2 26
#define dir2 27

#define step3 28
#define dir3 29

#define power 52;




//constructing the stepper objects

   AccelStepper stepper0( AccelStepper::DRIVER, step0, dir0);
   AccelStepper stepper1( AccelStepper::DRIVER, step1, dir1);
   AccelStepper stepper2( AccelStepper::DRIVER, step2, dir2);
   AccelStepper stepper3( AccelStepper::DRIVER, step3, dir3);
 
   float maxSpeed=3000;

// AccelStepper stepper0(4, in1A, in2A, in3A, in4A);  //4 or FULL4WIRE?
// AccelStepper stepper0(AccelStepper::FULL4WIRE, in1A, in2A, in3A, in4A);
// AccelStepper stepper1(AccelStepper::FULL4WIRE, in1B, in2B, in3B, in4B);
// AccelStepper stepper2(AccelStepper::FULL4WIRE, in1C, in2C, in3C, in4C);
// AccelStepper stepper3(AccelStepper::FULL4WIRE, in1D, in2D, in3D, in4D);

  
/////////////////////////////////////////////////////////////////
void motorSetup(){ 
  pinMode(52, OUTPUT);

  stepper0.setMaxSpeed(maxSpeed);  //in steps per seccond //"High" steps/second is 2000 to 3000--mecatronics uses 3000 setps per second--NOT RPM, and that requires very fast waveforms and fast magnetic field changes, so the stepper driver AND PROCESSOR SPEED is critical for high speeds. 
  stepper1.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepper2.setMaxSpeed(maxSpeed);  //in steps per seccond
  stepper3.setMaxSpeed(maxSpeed);  //in steps per seccond

  for(int j=0;j<4;j++){
   pastSpeed[j]=0;
  }
    
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

}

//take upcoming speeds at the target. use previous as current. 
//divide them into 3 groups 1, 3, 5, then max. and actuate the motors at each of those groups


/*
 * engageMotion() ensures that there is a nonlinear acceleration when steppers change speeds or accelerate
 * stepperStepsPerQuery must be more than _25_ per loop, or else the ramping will not be complete
 */
 
void engageMotion(){
  //rampDist=upcoming-past
  //stage1, if i<10, run motors at 1/10xrampdist 
 if(motorsEnabled)
 {
    digitalWrite(52, HIGH); //enabling motors  

    for(int j=0; j<4;j++)
    {
      rampDist[j]=upcomingSpeed[j]-pastSpeed[j];
    };

    
    for(int i=0;i<stepperStepsPerQuery;i++)
    { 
      if(i<10)                    //ramp stage 1
      {
        rampFactor=10;   // the difference in speed is divided by this factor before added to the previous speed. As this factor shrinks, it will ramp the steppers to the desired speed
      }
      else if(10<=i&&i<20)        //ramp stage 2
      {
        rampFactor=5;
      }
      else if(20<=i&&i<30)        //ramp stage 3
      {
        rampFactor=3;
      }
      else                        //run at full speed
      {
        rampFactor=1;           
      }

    };

     for(int j=0; j<4;j++) //setting previous speed to 0
    {
      pastSpeed[j]=0;
    };
    
 }
 else
 {
   digitalWrite(52, LOW);
   
   for(int j=0; j<4;j++) //setting previous speed to 0
    {
      pastSpeed[j]=0;
    };
    
 }

   for(int j=0; j<4;j++) //updating previous speed to 0
    {
      pastSpeed[j]=upcomingSpeed[j];
    };

 }

void actuateSteppers(int rampFactor){
//  Serial.print("intensity here:");Serial.print(robotVector.get_intensity()); Serial.print(" upcomingSpeed[1]:");Serial.println(upcomingSpeed[1]);
  stepper0.setSpeed(pastSpeed[0]+rampDist[0]/rampFactor);  
  stepper1.setSpeed(pastSpeed[1]+rampDist[1]/rampFactor);
  stepper2.setSpeed(pastSpeed[2]+rampDist[2]/rampFactor);
  stepper3.setSpeed(pastSpeed[3]+rampDist[3]/rampFactor);

  stepper0.runSpeed();  //use runSpeed?
//  stepper1.runSpeed();
//  stepper2.runSpeed();
//  stepper3.runSpeed();

}
