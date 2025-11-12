#include <EspHelperMutex.h>
#include <EspHelperTask.h>

EspHelper::Mutex mutex;
EspHelper::Task fastTask;
EspHelper::Task slowTask;
int sharedValue = 0;

void setup()
{
  Serial.begin(115200);
  mutex.create();

  slowTask.start("SlowTask",
                 []
                 {
                   while (true)
                   {
                     if (mutex.lock(portMAX_DELAY))
                     {
                       Serial.println("SlowTask entered critical section");
                       delay(600);
                       ++sharedValue;
                       Serial.printf("SlowTask value=%d\n", sharedValue);
                       mutex.unlock();
                     }
                     delay(100);
                   }
                 });

  fastTask.start("FastTask",
                 []
                 {
                   while (true)
                   {
                     if (mutex.lock(0))
                     {
                       --sharedValue;
                       Serial.printf("FastTask value=%d\n", sharedValue);
                       delay(50);
                       mutex.unlock();
                     }
                     else
                     {
                       Serial.println("FastTask skipping work (mutex busy)");
                     }
                     delay(100);
                   }
                 });
}

void loop()
{
}
