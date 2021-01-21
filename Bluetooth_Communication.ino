#include "functionlist.h"

char command, previousCommand;


 void bluetoothSetup(){
    Serial.begin(9600);
    Serial1.begin(9600);   //pins 18 and 19 are serial 1. connect tx to tx and rx to rx through the 1k ohm and ground it with a 2k
 }

/*
 *  The bluetooth app chosen transmits characters for directions and an interger value for speed. 
 *  To increase the speed of the loop (and therefore the activation of the steppers) this function is called every __ loops, about every ___seconds
 */

void interperetBluetooth(){
//read the serial for letters and sort into a unit vector
//
//read the serial for speed and scale it as intensity from 0 to 1

//return the direction vector and scaled intensity

  command = Serial1.read();
  //if I create an analogue remote or app, this switch table can go away
  switch(command){ 
      case 'F':  //Forward
        robotVector.set_velocityAngle(0); 
        break;
      case 'B':  //Back
        robotVector.set_velocityAngle(pi); 
        break;
      case 'L':  //Left
        robotVector.set_velocityAngle(1.5*pi);  
        break;
      case 'R':  //Right
        robotVector.set_velocityAngle(.5*pi); 
        break;
      case 'S':  //Stop
        robotVector.set_intensity(0.0); 
        // DOES THIS FIRE WHEN NO InPUT IS SELECTED?        
        break;
      case 'I':  //FR 
        robotVector.set_velocityAngle(.25*pi);
        break;
      case 'J':  //BR 
        robotVector.set_velocityAngle(.75*pi);
        break;       
      case 'G':  //FL 
       robotVector.set_velocityAngle(1.75*pi);
        break;
      case 'H':  //BL
        robotVector.set_velocityAngle(1.25*pi);
        break;
      case 'D':  //Everything OFF
        robotVector.set_intensity(0.0); 
        robotVector.set_rotationAngle(0);
        break;     
      case 'W': // rotate left
         robotVector.set_rotationAngle(pi/2);
      case 'w': // stop rotating left
          robotVector.set_rotationAngle(0);
      case 'U': // rotate rigth
         robotVector.set_rotationAngle(pi/2);
      case 'u': // stop rotating right
          robotVector.set_rotationAngle(0);
      default:  //Get velocity
        if(command=='q'){
          robotVector.set_intensity(1.0);  //Full velocity
        }
        else{
          //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
           if((command >= 48) && (command <= 57)){
             //Subtracting 48 changes the range from 48-57 to 0-9.
             //dividing by 9 changes the range to 0-1.
             robotVector.set_intensity((command - 48)/9);      
            }
        }    
     } //end of switch
    
}
