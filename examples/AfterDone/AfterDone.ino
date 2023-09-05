/*!
 * Warning! Maybe you'll need to checkout the other examples to fully
 * understand how this library works.
 *
 * Checkout the other examples:
 * + Sweep/
 * + Arrow/
 */

#include <ParallelServo.h>

ParallelServo myservo;

void setup()
{
  myservo.begin(7, 0, 180);
}

void loop()
{
  myservo.move(180, 15)
    ->move(0, 15, myservo.getIndex() == 1)
    ->afterDone([](){                       // Note that this function block
      if (myservo.getIndex())               // will only be executed on the
      {                                     // servo's position is updated,
        myservo.reset();                    // this method will help you to
      }                                     // write a more consise code and
    });                                     // more readable.
}
