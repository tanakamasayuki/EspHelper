// en: Signal a task from a hardware timer interrupt
// ja: Hardware タイマー割り込みからタスクへ合図する
#include <EspHelperSemaphore.h>
#include <EspHelperTask.h>

EspHelper::BinarySemaphore isrSignal;
EspHelper::Task ledTask;
hw_timer_t *timer = nullptr;

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

// en: Interrupt context: signal/copy only; do not wait or print here.
// ja: 割り込み側では合図や短いコピーだけを行い、待機や表示をしないようにします。
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
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  isrSignal.create();

  timer = timerBegin(1000000); // 1 MHz resolution (1 µs tick)
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 500000, true, 0); // fire every 500 ms

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
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

  isrSignal.give(); // allow first take
}

void loop()
{
}
