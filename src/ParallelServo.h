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

#define DEFAULT_MIN 0
#define DEFAULT_MAX 180

// todo: mention on the description how the movements is counted
// todo: add a propper documentation block for each example
// todo: fix jsdoc typos of the public methods

class ParallelServo: public Servo
{
public:
  ParallelServo(void);

  /*!
   * Attach the servo object to the specified pin on the Arduino board, it also
   * stores the min and max values that the other methods will use to know when
   * the movement should stop.
   * @param {uint8_t} pin - Board pin that the servo object needs to be attached
   * @param {int16_t} min - Min value that this servo can move, 0 if it's less than 0
   * @param {int16_t} max - Max value that this servo can move, 180 if it's greater than 180
   */
  void begin(u8 pin, i16 min=0, i16 max=180);

  /*!
   * Given a deg and a speed value, this function will do all the checks and
   * convertions to see if the servo is ok to move and if the user condition,
   * which could be "only moves if the index is 2, or something like that", is
   * also true. If every thing is valid, then it will pass that deg and speed
   * values to the routine that counts the millis() and write the position each
   * interval.
   * @param {uint8_t} deg       - Target position that the servo should move to
   * @param {uint8_t} speed     - Number of milliseconds that the servo should wait for each degree moved
   * @param {bool}    condition - Will dict if the servo should our should not start the move process
   */
  ParallelServo* move(u8 deg, u8 speed, bool condition);

  /*!
   * That's a wrapper for the previous function, it does the exact same thing,
   * but the user condition is replaced by the statement: this.getIndex() == 0, 
   * which means that it will only move if the movement index is 0, therefore,
   * if the it is the first movement that the servo should do before passing
   * to the next ones.
   * @param {uint8_t} deg   - Target position that the servo should move to
   * @param {uint8_t} speed - Number of milliseconds that the servo should wait for each degree moved
   */
  ParallelServo* move(u8 deg, u8 speed);

  /*!
   * You can use this function to reset all the states of the servo object,
   * including the movement counter (the _index). It is useful when you want to
   * make an loop of movements or create a user input that resets the servo's
   * state.
   */
  void reset(void);

  /*!
   * That's a function that recives another function as parameter (a.k.a:
   * a lambda function) and only run this function if this servo object is
   * marked as done. It is used when you want to reset this object or do
   * something at the end of the movement.
   * @param {void (*)(void)} routine - Function that will be ran when the _isDone attribute is true
   */
  void afterDone(void routine(void));

  // Getters and setters to allow the user change/monitor some behavior of this
  // object attributes. The body of the `inline` methods will be declared right
  // here in this file.

  inline u8 getIndex(void) { return _index; } // the index attribute will add by one each movement done
  inline bool isDone(void) { return _isDone; } // it will return true when the movement is finished and the servo is locked
  inline bool isLocked(void) { return _isLocked; }
  inline void setLock(bool isLocked) { _isLocked = isLocked; } // the servo will not do anything if the lock attribute is setted to true (starting with 0)

  inline u8 getPin(void) { return _pin; }
  inline u8 getMin(void) { return _min; }
  inline u8 getMax(void) { return _max; }
  inline u8 getPos(void) { return _pos; }

// warning: if you are just a normal user, all the code below will be a little
// useless to you, but if you think you need to be a hacker, go ahead. And
// remember, make a pull request if you found out a better way to write this
// library! <3
private:
  bool _isDone, _isLocked, _isMoving;
  u8 _pin, _min, _max, _index, _pos;
  u64 _mpc; //stands for "multiprocessing counter"

  /*!
   * This function should be called inside a loop event (the loop() or while).
   * This function will count the millis() output and update the current
   * position, writing that value for each degree - remembering that each
   * degree waits for the specified number of milliseconds before moving to the
   * next one.
   * @param {uint8_t} deg   - Target position that the servo should move to.
   * @param {uint8_t} speed - Number of milliseconds that the servo should wait for each degree moved
   */
  void _updateCurrentPosition(u8 deg, u8 speed);

  /*!
   * This method has no logic; it only changes the private attributes of this
   * object: it will mark the servo as done, mark it as not moving, and
   * increment the _index attribute by one. That's all.
   */
  void _stopAndMarkMovementAsDone(void);
};
