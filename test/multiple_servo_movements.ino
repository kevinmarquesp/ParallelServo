test(multiple_servo_movements, parallel_and_independent_movements)
{
  PRINTLN("--------- --- -- -");

  const uint8_t LIMIT = 5;

  ParallelServo s1, s2, s3;
  uint8_t s1i, s2i, s3i;

  s1.begin(7,  0, 180);
  s2.begin(6, 90, 180);
  s3.begin(5,  0,  90);

  while (s1.getIndex() < LIMIT || s2.getIndex() < LIMIT ||
         s3.getIndex() < LIMIT)
  {
    s1i = s1.getIndex();
    s2i = s2.getIndex();
    s3i = s3.getIndex();

    s1.move(s1i % 2 == 0 ? 180 :  0,  5,  s1i < LIMIT);
    s2.move(s2i % 2 == 0 ? 180 : 90, 10, s2i < LIMIT);
    s3.move(s3i % 2 == 0 ?  90 :  0, 20, s3i < LIMIT);
  }

  assertTrue(s1.isDone());
  assertTrue(s2.isDone());
  assertTrue(s3.isDone());

  assertEqual(s1.getIndex(), LIMIT);
  assertEqual(s2.getIndex(), LIMIT);
  assertEqual(s3.getIndex(), LIMIT);

  assertEqual(s1.getPos(), LIMIT % 2 == 0 ?  0 : 180);
  assertEqual(s2.getPos(), LIMIT % 2 == 0 ? 90 : 180);
  assertEqual(s3.getPos(), LIMIT % 2 == 0 ?  0 :  90);
}

test(multiple_servo_movements, start_the_next_when_the_previous_terminate)
{
  PRINTLN("--------- --- -- -");

  ParallelServo s1, s2, s3;

  s1.begin(7);
  s2.begin(6);
  s3.begin(5);

  while (!(s3.isDone() && s3.getIndex() >= 1))
  {
    s1.move(180, 5);
    s2.move(180, 5, s1.getIndex() == 1);
    s3.move(180, 5, s2.getIndex() == 1);
  }

  assertTrue(s1.isDone());
  assertTrue(s2.isDone());
  assertTrue(s3.isDone());

  assertEqual(s1.getIndex(), 1);
  assertEqual(s2.getIndex(), 1);
  assertEqual(s3.getIndex(), 1);

  assertEqual(s1.getPos(), 180);
  assertEqual(s2.getPos(), 180);
  assertEqual(s3.getPos(), 180);
}

test(multiple_servo_movements, cascating_a_sequence_of_movements)
{
  PRINTLN("--------- --- -- -");

  static ParallelServo s1, s2, s3;

  s1.begin(7);
  s2.begin(6);
  s3.begin(5);

  while (!(s3.isDone() && s3.getIndex() >= 1))
    s1.move(180, 5)
      ->afterDone([](){
        s2.move(180, 5, s1.getIndex() == 1)
          ->afterDone([](){
            s3.move(180, 5, s2.getIndex() == 1);
          });
      });

  assertTrue(s1.isDone());
  assertTrue(s2.isDone());
  assertTrue(s3.isDone());

  assertEqual(s1.getIndex(), 1);
  assertEqual(s2.getIndex(), 1);
  assertEqual(s3.getIndex(), 1);

  assertEqual(s1.getPos(), 180);
  assertEqual(s2.getPos(), 180);
  assertEqual(s3.getPos(), 180);
}
