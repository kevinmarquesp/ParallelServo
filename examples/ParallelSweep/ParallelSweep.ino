/*!
 * Warning! Maybe you'll need to checkout the other examples to fully
 * understand how this library works.
 *
 * Checkout the other examples:
 * + Sweep/
 */

#include <ParallelServo.h>

#define DELAY 10

ParallelServo servo_1;
ParallelServo servo_2;
ParallelServo servo_3;

void setup()
{
  servo_1.begin(7,  0, 180);
  servo_2.begin(6, 45,  90);
  servo_3.begin(5, 90, 180);
}

void loop()
{
  /* It's important to note that each servo is handled quite the same way, look
   * how this block of code repeats itself three times. The code below
   * controls the servo_1. */

  servo_1.move(180, DELAY);
  servo_1.move(  0, DELAY, servo_1.getIndex() == 1);

  if (servo_1.getIndex() == 2 && servo_1.isDone())
  {
    servo_1.reset();
  }

  /* The code below controls the servo_2. */

  servo_2.move(90, DELAY);
  servo_2.move(45, DELAY, servo_2.getIndex() == 1);

  if (servo_2.getIndex() == 2 && servo_2.isDone())
  {
    servo_2.reset();
  }

  /* And the code below controls the servo_3. */

  servo_3.move(180, DELAY);
  servo_3.move( 90, DELAY, servo_3.getIndex() == 1);

  if (servo_3.getIndex() == 2 && servo_3.isDone())
  {
    servo_3.reset();
  }
}
