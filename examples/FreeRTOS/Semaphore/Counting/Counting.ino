#include <EspHelperSemaphore.h>
#include <EspHelperTask.h>

constexpr uint32_t kJobDurationMs = 800;
EspHelper::CountingSemaphore slots;
EspHelper::Task workers[3];

void setup()
{
  Serial.begin(115200);
  slots.create(2, 2);  // allow two concurrent jobs

  for (int i = 0; i < 3; ++i)
  {
    int id = i;
    workers[i].start("Worker", [id] {
      while (true)
      {
        if (slots.take(500))
        {
          Serial.printf("Worker %d acquired slot\n", id);
          delay(kJobDurationMs);
          Serial.printf("Worker %d releasing slot\n", id);
          slots.give();
        }
        else
        {
          Serial.printf("Worker %d timed out waiting\n", id);
        }
        delay(200);
      }
    });
  }
}

void loop()
{
}
