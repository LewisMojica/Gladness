#include <Arduino.h>
#include "ESC.h"


// ESC::ESC(){
//     Servo myServo;
// }

void ESC::attach(int _pin){
    pin = _pin;
    servo.attach(_pin);

    servo.writeMicroseconds(neutral_micros);

}

void ESC::writeMicroseconds(int micro_seg){
    servo.writeMicroseconds(micro_seg);
}

void ESC::setSpeed(int _speed){

    if(_speed >= 1 && _speed <= 100){
        if(reverse_status == true && speed < neutral_micros){
            servo.writeMicroseconds(neutral_micros);
             delay(400);
        }

        servo.writeMicroseconds(map(_speed,1,100,min_throttle,max_throttle));
        speed = _speed;
        reverse_status = false;

    } else if(_speed <= -1 && _speed >= -100){
        if (reverse_status == false){
            if (speed != neutral_micros){
                servo.writeMicroseconds(neutral_micros);    
                delay(300);
            }
            servo.writeMicroseconds(min_reverse_micros);
            delay(200);
            servo.writeMicroseconds(neutral_micros);
            delay(200);
            servo.writeMicroseconds(map(_speed,-1,-100,min_reverse_micros,max_reverse_micros));
            speed = _speed;
            reverse_status = true;
        } else{
            servo.writeMicroseconds(map(_speed,-1,-100,min_reverse_micros,max_reverse_micros));
            speed = _speed;
        }
    } else {
        servo.writeMicroseconds(neutral_micros);
        speed = neutral_micros;
    }
}

void ESC::brakeMotor(){
    if(reverse_status == false)
        servo.writeMicroseconds(brake_micros);
    else{
        servo.writeMicroseconds(min_throttle);
        delay(100);
        servo.writeMicroseconds(brake_micros);
    }
    speed = 123;
}

void ESC::enableReverse(){
    if (reverse_status == false){
        if (speed != neutral_micros){
            servo.writeMicroseconds(neutral_micros);    
            delay(300);
        }   
        servo.writeMicroseconds(min_reverse_micros);
        delay(200);
        servo.writeMicroseconds(neutral_micros);
        delay(200);
        reverse_status = true;
    }
    
    
}

void ESC::setMaxThrottleMicros(int in){
    max_throttle = in;
}

void ESC::setMinThrottleMicros(int in){
    min_throttle = in;
}

void ESC::setneutralMicros(int in){
    neutral_micros = in;
}

void ESC::setBrakeMicros(int in){
    brake_micros = in;
}

void ESC::setMinReverseMicros(int in){
    min_reverse_micros = in;
}

void ESC::setMaxReverseMicros(int in){
    max_reverse_micros = in;
}

int ESC::getSpeed(){
    return speed;
}

bool ESC::getReverseStatus(){
    return reverse_status;
}
