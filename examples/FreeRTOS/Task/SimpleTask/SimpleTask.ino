#include <EspHelperTask.h>

EspHelper::Task blinker;

void setup()
{
  Serial.begin(115200);
  blinker.start("BlinkTask",
                []
                {
                  pinMode(LED_BUILTIN, OUTPUT);
                  while (true)
                  {
                    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
                    delay(500);
                  }
                });
}

void loop()
{
}
