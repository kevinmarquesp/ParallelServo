test(single_servo_movement, go_from_min_to_max)
{
  PRINTLN("--------- --- -- -");

  double buff, margin = 15.0;
  ParallelServo s;

  s.begin(7);

  buff = millis();

  while (!s.isDone())
    s.move(180, 10);

  assertNear((double)millis(), buff, 1800.0 + margin);
  assertEqual(s.getPos(), 180);
  assertEqual(s.getIndex(), 1);

  s.reset();
  assertEqual(s.getIndex(), 0);

  buff = millis();

  while (!s.isDone())
    s.move(0, 10);

  assertNear((double)millis(), buff, 1800.0 + margin);
  assertEqual(s.getPos(), 0);
  assertEqual(s.getIndex(), 1);

  s.detach();
}

test(single_servo_movement, cascating_a_sequence_of_movements)
{
  PRINTLN("--------- --- -- -");

  double buff, margin = 15.0;
  ParallelServo s;

  s.begin(6, 45, 135);

  buff = millis();

  while (!(s.getIndex() == 3 && s.isDone()))
    s.move(135, 20)
      ->move(45, 10, s.getIndex() == 1)
      ->move(90, 30, s.getIndex() == 2);

  assertNear((double)millis(), buff, 4050.0 + margin);

  s.detach();
}

test(single_servo_movement, locking_in_the_middle_of_an_movement)
{
  PRINTLN("--------- --- -- -");

  double buff, margin = 15.0;
  ParallelServo s;

  s.begin(5);

  buff = millis();
  while (!s.isDone())
  {
    s.move(180, 30);

    if (millis() - buff >= 2700 && millis() - buff < 3200)
      s.setLock(true);

    if (millis() - buff >= 3200)
      s.setLock(false);
  }

  assertNear((double)millis(), buff, 5900.0 + margin);

  s.detach();
}
