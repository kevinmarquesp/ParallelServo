// todo: add doc description
// todo: add doc comments

#include <ParallelServo.h>

#define DELAY 10

ParallelServo sv1, sv2, sv3;

void setup()
{
  sv1.begin(7,  0, 180);
  sv2.begin(6, 45,  90);
  sv3.begin(5, 90, 180);
}

void loop()
{
  sv1.move(180, DELAY)
    ->move(  0, DELAY, sv1.getIndex() == 1)
    ->afterDone([](){
      if (sv1.getIndex() == 2)
        sv1.reset();
    });

  sv2.move(90, DELAY * 3)
    ->move(45, DELAY * 3, sv2.getIndex() == 1)
    ->afterDone([](){
      if (sv2.getIndex() == 2)
        sv2.reset();
    });

  sv3.move(180, DELAY * 2)
    ->move( 90, DELAY * 2, sv3.getIndex() == 1)
    ->afterDone([](){
      if (sv3.getIndex() == 2)
        sv3.reset();
    });
}
