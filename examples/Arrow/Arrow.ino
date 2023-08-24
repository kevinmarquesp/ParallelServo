// todo: add doc description

#include <ParallelServo.h>

ParallelServo myservo;

void setup()
{
  myservo.begin(7, 0, 180);
}

void loop()
{
  myservo.move(180, 15)
    ->move(0, 15, myservo.getIndex() == 1);

  /* How you can see, this is the exat same thing as the Sweep example, this
   * code will be translated to this:
   *   myservo.move(180, 15);
   *   myservo.move(0, 15, myservo.getIndex() == 1);
   * But the desition is up to you, I preffer the arrow syntax, but that's my
   * choice... */

  if (myservo.getIndex() == 2 && myservo.isDone())
  {
    myservo.reset();
  }
}
