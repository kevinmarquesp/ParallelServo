// todo: add doc description
// todo: add doc comments

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
    ->afterDone([](){
      if (myservo.getIndex())
        myservo.reset();
    });
}
