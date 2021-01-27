#include "functionlist.h"

void Battery_setup(){
pinMode(53, OUTPUT);
pinMode(A15, INPUT);
}

 void checkBattery(){
    int sensorValue=analogRead(A15);
    float voltage=sensorValue*(5.0/1023.00)*3;

  if(voltage<11){
    digitalWrite(53, HIGH);
  }else if(voltage>11){
    digitalWrite(53, LOW);
  }

   Serial.print("volts");Serial.println(voltage);
  
 }
