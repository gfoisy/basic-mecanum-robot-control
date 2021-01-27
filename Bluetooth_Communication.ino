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
//return the direction vector and scaled intensity
//  Serial1.availableForWrite();
//  Serial.print(Serial1.availableForWrite());
  
  command = Serial1.read();

  //  Serial.print("command:");
  //  Serial.println(command);
 
  
  motorsEnabled=true;

  //if I create an analog remote or app, this switch table can go away
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
      case 'S':  //Stop -- FIRES IF NO INPUT from bluetooth
           motorsEnabled=false;
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
        motorsEnabled=false;
        break;     
      case 'W': // rotate left
         robotVector.set_rotationAngle(pi/2);
         break;
      case 'w': // stop rotating left
          robotVector.set_rotationAngle(0);
          motorsEnabled=false;
          break;
      case 'U': // rotate right
         robotVector.set_rotationAngle(-pi/2);
         break;
      case 'u': // stop rotating right
          robotVector.set_rotationAngle(0);
          motorsEnabled=false;
          break;
      default:  //Get velocity
        if(command=='q'){
          robotVector.set_intensity(1.0);  //Full velocity
          motorsEnabled=false;
        }
        else{
          //Chars '0' - '9' have an integer equivalence of 48 - 57, accordingly.
           if((command >= 48) && (command <= 57)){
             //Subtracting 48 changes the range from 48-57 to 0-9.
             //dividing by 9changes the range to 0-1.
             robotVector.set_intensity(((float)command - 48)/9);  
             motorsEnabled=false;
            }
        }    
     } //end of switch

   
    
    
}
