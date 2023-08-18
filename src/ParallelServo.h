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

  // Getters and setters to allow the user change/monitor some behavior of this
  // object attributes. The body of the `inline` methods will be declared right
  // here in this file.

  inline u8 getPin(void) { return _pin; }
  inline u8 getMin(void) { return _min; }
  inline u8 getMax(void) { return _max; }

private:
  u8 _pin, _min, _max;
};
