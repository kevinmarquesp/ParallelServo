test(begin_assigns_pin_value)
{
  typedef struct Case
  {
    uint8_t pin;
    uint8_t epin; // expected value
  } Case;

  Case testCases[] = {
    {8,   8},   // valid value
    {10,  10},  // another valid value
    {0,   0},   // minimum value
    {255, 255}, // maximum value
    {256, 0},   // overflow value
    {-1,  255}  // underflow value
  };

  for (uint8_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i)
  {
    auto c = testCases[i];

    ParallelServo s;
    s.begin(c.pin); // min and max are default values

    assertEqual(s.getPin(), c.epin);
    assertEqual(s.getMin(), 0);
    assertEqual(s.getMax(), 180);

    assertTrue(s.attached());
    assertEqual(s.read(), 0);
  }
}

test(begin_assigns_min_and_max_values)
{
  typedef struct Case
  {
    int16_t min, max;
    uint8_t emin, emax; // expected values
  } Case;

  Case testCases[] = {
    {-10, 200, 0,  180}, // more than the valid range
    {0,   180, 0,  180}, // same as default values
    {20,  160, 20, 160}, // within valid range
    {180, 10,  0,  180}, // reversed order
    {200, -20, 0,  180}, // both invalid values
    {90,  90,  0,  180}, // same value for min and max
  };

  for (uint8_t i = 0; i < sizeof(testCases) / sizeof(testCases[0]); ++i)
  {
    auto c = testCases[i];

    ParallelServo s;
    s.begin(12, c.min, c.max); // pin is fixed at 12

    assertEqual(s.getPin(), 12);
    assertEqual(s.getMin(), c.emin);
    assertEqual(s.getMax(), c.emax);

    assertTrue(s.attached());
    assertEqual(s.read(), c.emin);
  }
}
