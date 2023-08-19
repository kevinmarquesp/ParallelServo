#include "ParallelServo.h"

// ------------------------------ constructor ------------------------------ //

ParallelServo::ParallelServo(void)
{
  _min = 0;
  _max = 180;

  _index = 0;
  _isDone = false;
  _isLocked = false;
  _isMoving = false;
}

// ----------------------------- public methods ---------------------------- //

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

ParallelServo* ParallelServo::move(bool condition, u8 deg, u8 speed)
{
  // this line just ajust the deg value to the correct range (between _min and _max)
  deg = deg < _min ?
    _min : deg > _max ?
      _max : deg;

  if (!condition || _isLocked)
    return this;
  else
    _isDone = false; //reset done value when the movement starts

  // it's unecessary to do any math when the speed is 0, just go ahead and finish the movemt
  if (speed < 1)
  {
    this->write(deg);
    _stopAndMarkMovementAsDone();
  }

  if (!_isMoving && !_isDone)
  {
    _mpc = millis();
    _isMoving = true;
  }
  else if (_isMoving && !_isDone)
  {
    _updateCurrentPosition(deg, speed);
  }

  return this;
}

ParallelServo* ParallelServo::move(u8 deg, u8 speed)
{
  return this->move(_index == 0, deg, speed);
}

void ParallelServo::reset(void)
{
  _isMoving = false;
  _isDone = false;
  _index = 0;
}

void ParallelServo::afterDone(void routine(void))
{
  if (_isDone)
    routine();
}

// --------------------------- private methods ----------------------------- //

void ParallelServo::_updateCurrentPosition(u8 deg, u8 speed)
{
  if (millis() - _mpc >= speed)
  {
    u8 currdeg = this->read();
    _mpc = millis(); //update the process counter

    // increment/decrement by one each speed millisseconds
    if (deg > currdeg)
      this->write(this->read() + 1);
    else
      this->write(this->read() - 1);
  }
}

void ParallelServo::_stopAndMarkMovementAsDone(void)
{
  _isDone = true;
  _isMoving = false;
  ++_index; //increment the index to the next movement
}
