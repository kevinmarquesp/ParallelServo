// todo: add doc description

// todo: create an example that shows the arrow sintax

#include <ParallelServo.h>

ParallelServo myservo;

void setup()
{
  myservo.begin(7, 0, 180);  // This line says that the servo should be attached
                             // to the pin 7 and it can move from 0 to 180 degree.
}

void loop()
{
  myservo.move(180, 15);  // This line will move the servo to the 180 position,
                          // waiting 15 milliseconds for each degree. But this
                          // will only be executed if it's the FIRST MOVEMENT
                          // of this servo - in other words, if the index of
                          // this motor is 0.

  /* Important note: when this movement is finished, the index will be incremented
   * by one. So, on the next movement, the .getIndex() function will return 1. */

  myservo.move(0, 15, myservo.getIndex() == 1);  // This line will move the servo
                                                 // again to the position 0, waiting
                                                 // for 15 milliseconds for each
                                                 // degree. But this code will be
                                                 // executed only if the condition
                                                 // on the last parameter is true.
                                                 // In this case, only if the index
                                                 // is 1 (seccond movement).

  /* When your servo already reached the limit that you want - in this case, when
   * it's reached the index 2 - you can make an condition to reset the servo state
   * back to index 0, in order to make it start over and over again. */

  if (myservo.getIndex() == 2 && myservo.isDone())
  {
    myservo.reset();
  }
}
