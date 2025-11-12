#include <EspHelperMutex.h>
#include <EspHelperTask.h>

EspHelper::Mutex mutex;
EspHelper::Task loggerTask;
EspHelper::Task sensorTask;
char lastMessage[64] = {0};

void setup()
{
  Serial.begin(115200);
  mutex.create();

  sensorTask.start("SensorTask",
                   []
                   {
                     uint32_t counter = 0;
                     while (true)
                     {
                       if (mutex.lock(portMAX_DELAY))
                       {
                         snprintf(lastMessage, sizeof(lastMessage), "sensor reading %lu", ++counter);
                         delay(300);  // pretend measurement time
                         mutex.unlock();
                       }
                       delay(100);
                     }
                   });

  loggerTask.start("LoggerTask",
                   []
                   {
                     while (true)
                     {
                       if (mutex.lock(portMAX_DELAY))
                       {
                         Serial.printf("[logger] %s\n", lastMessage);
                         delay(150);
                         mutex.unlock();
                       }
                       delay(200);
                     }
                   });
}

void loop()
{
}
