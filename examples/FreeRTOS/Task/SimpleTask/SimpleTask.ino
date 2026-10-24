// en: Start a simple worker task
// ja: 単純なワーカータスクを開始する
#include <EspHelperTask.h>

EspHelper::Task blinker;

#ifndef LED_BUILTIN
#define LED_BUILTIN 2
#endif

void setup()
{
  Serial.begin(115200);
  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
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
