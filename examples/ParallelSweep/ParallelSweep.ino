// todo: add doc description
// todo: add doc comments

// todo: create an example that uses the base servo strategy
// todo: create an example that uses the .afterDone() method

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
  servo_1.move(180, DELAY);
  servo_1.move(  0, DELAY, servo_1.getIndex() == 1);

  if (servo_1.getIndex() == 2 && servo_1.isDone())
  {
    servo_1.reset();
  }

  servo_2.move(90, DELAY);
  servo_2.move(45, DELAY, servo_2.getIndex() == 1);

  if (servo_2.getIndex() == 2 && servo_2.isDone())
  {
    servo_2.reset();
  }

  servo_3.move(180, DELAY);
  servo_3.move( 90, DELAY, servo_3.getIndex() == 1);

  if (servo_3.getIndex() == 2 && servo_3.isDone())
  {
    servo_3.reset();
  }
}
