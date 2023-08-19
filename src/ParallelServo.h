/*!
 * @file ParallelServo.h
 *
 * This library is used to handle multiple servo components simultaneously
 * using the strategy of counting the output of the `millis()` function from
 * the `Arduino.h` library. For more information about this strategy, check out
 * the articles below:
 *   -> https://learn.adafruit.com/multi-tasking-the-arduino-part-1/using-millis-for-timing
 *   -> https://circuitdigest.com/microcontroller-projects/arduino-multitasking-using-millis-in-arduino
 *   -> https://kevinmarquesp.github.io/post/230719143253_multitasking-com-um-arduino-uno/
 *
 * In order to make this library work properly, you'll need to have the
 * `Servo.h` library installed. You can download it manually from this
 * repository:
 *   -> https://github.com/arduino-libraries/Servo
 *
 * Licence: MIT (see the LICENCE file)
 */

#pragma once

#include <Arduino.h>
#include <Servo.h> //dependency

#define u8  uint8_t
#define i16 int16_t
#define u16 uint16_t
#define u64 uint64_t

class ParallelServo: public Servo
{
public:
  ParallelServo(void);

  /*!
   * Attach the servo object to the specified pin on the Arduino board, it also
   * stores the min and max values that the other methods will use to know when
   * the movement should stop.
   * @param {uint8_t} pin - Board pin that the servo object needs to be attached
   * @param {uint8_t} min - Min value that this servo can move
   * @param {uint8_t} max - Max value that this servo can move
   */
  void begin(u8 pin, i16 min=0, i16 max=180);

  // todo: add a documentation for this methdos
  ParallelServo* move(bool condition, u8 deg, u8 speed);

  // todo: add a (better) documentation for this methdos
  ParallelServo* move(u8 deg, u8 speed);

  // todo: add a documentation for this methdos
  void reset(void);

  // todo: add a documentation for this methdos
  void afterDone(void routine(void));

  // Getters and setters to allow the user change/monitor some behavior of this
  // object attributes. The body of the `inline` methods will be declared right
  // here in this file.

  inline u8 getPin(void) { return _pin; }
  inline u8 getMin(void) { return _min; }
  inline u8 getMax(void) { return _max; }
  inline u8 getIndex(void) { return _index; } // the index attribute will add by one each movement done
  inline void setLock(bool isLocked) { _isLocked = isLocked; } // the servo will not do anything if the lock attribute is setted to true (starting with 0)

// warning: if you are just a normal user, all the code below will be a little
// useless to you, but if you think you need to be a hacker, go ahead. And
// remember, make a pull request if you found out a better way to write this
// library! <3

 private:
  u8 _pin, _min, _max, _index;
  bool _isDone, _isLocked, _isMoving;
  u64 _mpc; // stands for "multiprocessing counter"

  // todo: add a documentation for this methdos
  void _updateCurrentPosition(u8 deg, u8 speed);

  // todo: add a documentation for this methdos
  void _stopAndMarkMovementAsDone(void);
};
