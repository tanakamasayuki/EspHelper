#include <EspHelperMutex.h>

EspHelper::Mutex mutex;
EspHelper::Task writerA;
EspHelper::Task writerB;
int sharedValue = 0;

void setup()
{
  Serial.begin(115200);
  mutex.create();

  writerA.start("WriterA", [] {
    while (true)
    {
      if (mutex.lock(100))
      {
        ++sharedValue;
        Serial.printf("WriterA value=%d\n", sharedValue);
        mutex.unlock();
      }
      delay(200);
    }
  });

  writerB.start("WriterB", [] {
    while (true)
    {
      if (mutex.lock(100))
      {
        sharedValue += 2;
        Serial.printf("WriterB value=%d\n", sharedValue);
        mutex.unlock();
      }
      delay(250);
    }
  });
}

void loop()
{
}
