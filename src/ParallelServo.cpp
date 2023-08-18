#include "ParallelServo.h"

// todo: use this constructor to set the default min and max values
// todo: create an attribute to check if the servo is attached to a pin
ParallelServo::ParallelServo(void)
{
}

// todo: check for invalid pins
// todo: make this function return an error
void ParallelServo::begin(u8 pin, i16 min=0, i16 max=180)
{
  const u8 MIN = 0;
  const u8 MAX = 180;

  _pin = pin;
  _min = min < MIN ? MIN : (u8)min;
  _max = max > MAX ? MAX : (u8)max;

  this->attach(_pin); // methods from the Servo.h
  this->write(_min);  // move the motor to the min value at the beggining
}
