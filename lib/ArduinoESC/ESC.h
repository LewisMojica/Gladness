#ifndef ESC_h
#define ESC_h
#include <Arduino.h>
#include <Servo.h>

class ESC
{
  private:

    byte pin;
    bool reverse_status = false;
    int speed;
    int max_throttle = 2000, min_throttle = 1600, neutral_micros = 1500, brake_micros = 1200, max_reverse_micros = 1000, min_reverse_micros = 1400;
    public:

    ESC():servo(){}

    Servo servo;

    const int brake = 123;

    void brakeMotor();
    //Configura el times al pin dado a una frecuencia de 50hz
    void attach(int);
    //asigna una duracion al periodo alto del puslo (en microsegundos)
    void writeMicroseconds(int);

    void setSpeed(int);
    
    bool getReverseStatus();


    void setMaxThrottleMicros(int);
    void setMinThrottleMicros(int);
    void setneutralMicros(int);
    void setBrakeMicros(int);
    void setMinReverseMicros(int);
    void setMaxReverseMicros(int);

    void enableReverse();

    int getSpeed();
};

#endif