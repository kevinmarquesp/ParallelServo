#include <ParallelServo.h>

#define DELAY 5

ParallelServo sm1, sm2, sm3;
uint8_t currentScene = 0;

void gotoNextScene(uint8_t index_1, uint8_t index_2, uint8_t index_3)
{
  if (sm1.isDone() && sm2.isDone() && sm3.isDone() &&
      sm1.getIndex() >= index_1 && sm2.getIndex() >= index_2 &&
      sm3.getIndex() >= index_3)
  {
    sm1.reset();
    sm2.reset();
    sm3.reset();
    ++currentScene;
  }
}

void setup()
{
  sm1.begin(7, 0, 180);
  sm2.begin(6, 0, 180);
  sm3.begin(5, 0, 180);
}

void loop()
{
  switch (currentScene)
  {
    case 0:
      sm1.move(180,   DELAY);
      sm2.move( 90, 2*DELAY);
      sm3.move(180,   DELAY);

      gotoNextScene(1, 1, 1);
      break;

    case 1:
      sm1.move( 90, 3*DELAY, sm1.getIndex() % 2 == 0)
        ->move(180, 3*DELAY, sm1.getIndex() % 2 == 1);

      sm2.move(  0, 3*DELAY, sm2.getIndex() % 2 == 0)
        ->move( 90, 3*DELAY, sm2.getIndex() % 2 == 1);

      sm3.move( 90, 3*DELAY, sm3.getIndex() % 2 == 0)
        ->move(180, 3*DELAY, sm3.getIndex() % 2 == 1);

      gotoNextScene(2, 2, 2);
      break;

    case 2:
      sm1.move(135, DELAY);
      sm2.move( 45, DELAY);
      sm3.move(135, DELAY);

      gotoNextScene(1, 1, 1);
      break;

    case 3:
      sm1.move( 90, 3*DELAY);
      sm2.move( 90, 3*DELAY, sm1.getIndex() == 1);
      sm3.move( 90, 3*DELAY, sm2.getIndex() == 1);

      gotoNextScene(1, 1, 1);
      break;

    case 4:
      sm1.move(180, 2*DELAY);
      sm2.move(180, 2*DELAY, sm1.getIndex() == 1);
      sm3.move(180, 2*DELAY, sm2.getIndex() == 1);

      gotoNextScene(1, 1, 1);
      break;

    case 5:
      sm1.move(0, DELAY);
      sm2.move(0, DELAY, sm1.getIndex() == 1);
      sm3.move(0, DELAY, sm2.getIndex() == 1);

      gotoNextScene(1, 1, 1);
      break;

    default:
      currentScene = 0;
  }
}

