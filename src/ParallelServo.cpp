#include "ParallelServo.h"

ParallelServo::ParallelServo(void)
{
  _min = 0;
  _max = 180;
}

void ParallelServo::begin(u8 pin, i16 min=0, i16 max=180)
{
  _pin = pin;

  _min = min < _min || min >= max ?
    _min : (u8)min;

  _max = max > _max || min >= max ?
    _max : (u8)max;

  this->attach(_pin); // methods from the Servo.h
  this->write(_min);  // move the motor to the min value at the beggining
}
