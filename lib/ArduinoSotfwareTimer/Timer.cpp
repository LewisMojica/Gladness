#include <Arduino.h>
#include "Timer.h"

Timer::Timer(unsigned long interval){
  _interval=interval;
}

bool Timer::read(){
  if((millis() >= _interval + _pre_millis) && ((_init_and_initOn  & (1 << 6)) >> 6) == 1){
	_pre_millis = millis();
  _init_and_initOn &= ~(1 << 7);
  return true;
  }
  if((_init_and_initOn  >> 7) && ((_init_and_initOn  & (1 << 6)) >> 6)){
    _init_and_initOn &= ~(1 << 7);
    _pre_millis = millis();
    return true;
  }
  return false;
}

bool Timer::isRunning(){
  return ((_init_and_initOn  & (1 << 6)) >> 6);
}

bool Timer::check(){
  return ((millis() - _pre_millis) >= _interval) && ((_init_and_initOn & (1 << 6)) >> 6);
  
}

void Timer::reset(){
  _pre_millis = millis();
}

void Timer::init(){
  _init_and_initOn &= ~(1 << 7);
  _init_and_initOn |= (1 << 6);
  reset();
}


void Timer::initOn(){
  _init_and_initOn |= 1 << 7;
  _init_and_initOn |= 1 << 6;
}

void Timer::end(){
  _init_and_initOn &= ~(1 << 6);
}

void Timer::setInterval(unsigned long interval){
  _interval = interval;
}
