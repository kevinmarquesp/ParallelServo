#include <AUnitVerbose.h>
#include <ParallelServo.h>

#define PRINT(str)  Serial.print(str)
#define PRINTLN(str) Serial.println(str)

using namespace aunit;

void setup(void)
{
  #if !defined(EPOXY_DUINO)
    delay(1000);
  #endif

  Serial.begin(115200);
  while (not Serial);

  #if defined(EPOXY_DUINO)
    Serial.setLineModeUnix();
  #endif

  TestRunner::exclude("*");
  // TestRunner::include("check_default_attributes", "*");
  // TestRunner::include("single_servo_movement", "*");
  // TestRunner::include("multiple_servo_movements", "*");
}

void loop(void)
{
  TestRunner::run();
}
