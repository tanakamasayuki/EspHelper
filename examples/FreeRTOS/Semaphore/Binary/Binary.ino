// en: Coordinate tasks using a single pending signal
// ja: 最大1件の保留信号でタスクを同期する
#include <EspHelperSemaphore.h>
#include <EspHelperTask.h>

EspHelper::BinarySemaphore semaphore;
EspHelper::Task taskOne;
EspHelper::Task taskTwo;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  semaphore.create();

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  taskOne.start("TaskOne", []
                {
    while (true)
    {
      semaphore.take();
      Serial.println("TaskOne got semaphore");
      delay(300);
      semaphore.give();
      delay(300);
    } });

  taskTwo.start("TaskTwo", []
                {
    while (true)
    {
      semaphore.take();
      Serial.println("TaskTwo got semaphore");
      delay(300);
      semaphore.give();
      delay(300);
    } });

  semaphore.give();
}

void loop()
{
}
