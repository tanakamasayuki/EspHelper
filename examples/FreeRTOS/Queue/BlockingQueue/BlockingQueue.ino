// en: Wait until a queued item arrives
// ja: Queueの要素が届くまで待つ
#include <EspHelperQueue.h>
#include <EspHelperTask.h>

EspHelper::Queue<int> queue;
EspHelper::Task producer;
EspHelper::Task blockingConsumer;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  queue.create(1); // keep it small so the producer also blocks when the consumer is slow

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  producer.start("BlockingProducer",
                 []
                 {
                   int value = 0;
                   while (true)
                   {
                     // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
                     // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
                     queue.send(++value, portMAX_DELAY);
                     Serial.printf("[blocking] sent %d\n", value);
                     delay(1200);
                   }
                 });

  blockingConsumer.start("BlockingConsumer",
                         []
                         {
                           int received;
                           while (true)
                           {
                             // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
                             // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
                             queue.receive(received, portMAX_DELAY);
                             Serial.printf("[blocking] received %d\n", received);
                             delay(2000); // deliberately slower than producer to show blocking behavior
                           }
                         });
}

void loop()
{
}
