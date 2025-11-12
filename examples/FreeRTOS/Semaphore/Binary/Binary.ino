#include <EspHelperSemaphore.h>

EspHelper::BinarySemaphore semaphore;
EspHelper::Task taskOne;
EspHelper::Task taskTwo;

void setup()
{
  Serial.begin(115200);
  semaphore.create();

  taskOne.start("TaskOne", [] {
    while (true)
    {
      semaphore.take();
      Serial.println("TaskOne got semaphore");
      delay(300);
      semaphore.give();
      delay(300);
    }
  });

  taskTwo.start("TaskTwo", [] {
    while (true)
    {
      semaphore.take();
      Serial.println("TaskTwo got semaphore");
      delay(300);
      semaphore.give();
      delay(300);
    }
  });

  semaphore.give();
}

void loop()
{
}
