#include <EspHelperSemaphore.h>
#include <EspHelperTask.h>

EspHelper::BinarySemaphore isrSignal;
EspHelper::Task ledTask;
hw_timer_t *timer = nullptr;

void IRAM_ATTR onTimer()
{
  BaseType_t higherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR(isrSignal.raw(), &higherPriorityTaskWoken);
  if (higherPriorityTaskWoken == pdTRUE)
  {
    portYIELD_FROM_ISR();
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  isrSignal.create();

  timer = timerBegin(0, 80, true);           // 1 µs tick
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 500000, true);      // 500 ms
  timerAlarmEnable(timer);

  ledTask.start("IsrBlink",
                []
                {
                  while (true)
                  {
                    if (isrSignal.take(portMAX_DELAY))
                    {
                      digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
                      Serial.println("ISR signal received");
                    }
                  }
                });

  isrSignal.give();  // allow first take
}

void loop()
{
}
