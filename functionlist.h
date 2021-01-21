 #pragma once
//Declarations

#define pi 3.14159

unsigned long time1, time2;


// Battery monitor
   void battery_setup();

// Bluetooth_Communication
   void bluetoothSetup();
   void interperetBluetooth();


// Motor_control
   void motorSetup();
   void calculateStepperSpeeds();
   void actuateSteppers();


// debug
   void bluetoothDebug();
   void motorsDebug();
   void miscDebug();



class directionVector{
  public:
    void set_velocityAngle(float angle){_velocityAngle=angle;}; //in rads
    void set_intensity(float val){_intensity=val;};

    void set_rotationAngle(float angle){ _rotationAngle=angle;};  //angle is currently unused, will be implemented later to control the rotation of the bot 

    float get_velocityAngle(){return _velocityAngle;};
    float get_rotationAngle(){return _rotationAngle;};
    float get_intensity(){return _intensity;};  

    
  private:  
   float _velocityAngle=0;  //=0? should set default values here or somewhere else?
   float _rotationAngle=0;
   float _intensity=0;
   
 };



// void set_velocityAngle(float angle);{
//     _velocityAngle=angle;
// }

// void set_rotationAngle(float angle);{
//     _rotationAngle=angle;
// }
// void directionVector::set_intensity(float val){
//     intensity=val;
// }
