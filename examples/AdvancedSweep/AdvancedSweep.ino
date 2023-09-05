/*!
 * Warning! Maybe you'll need to checkout the other examples to fully
 * understand how this library works.
 *
 * Checkout the other examples:
 * + Sweep/
 * + Arrow/
 * + AfterDone/
 * + ParallelSweep/
 */

#include <ParallelServo.h>

#define DELAY 10

ParallelServo servo_1, servo_2, servo_3;

void setup()
{
  servo_1.begin(7,  0, 180);
  servo_2.begin(6, 45,  90);
  servo_3.begin(5, 90, 180);
}

void loop()
{
  /* Now it's a little more easy to distinguish each block of movements. */

  servo_1.move(180, DELAY)
    ->move(  0, DELAY, servo_1.getIndex() == 1)
    ->afterDone([](){
      if (servo_1.getIndex() == 2)
        servo_1.reset();
    });

  servo_2.move(90, DELAY * 3)
    ->move(45, DELAY * 3, servo_2.getIndex() == 1)
    ->afterDone([](){
      if (servo_2.getIndex() == 2)
        servo_2.reset();
    });

  servo_3.move(180, DELAY * 2)
    ->move( 90, DELAY * 2, servo_3.getIndex() == 1)
    ->afterDone([](){
      if (servo_3.getIndex() == 2)
        servo_3.reset();
    });
}
