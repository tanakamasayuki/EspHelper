// en: Check a queue without waiting
// ja: Queueを待機せずに確認する
#include <EspHelperQueue.h>
#include <EspHelperTask.h>

EspHelper::Queue<int> queue;
EspHelper::Task producer;
EspHelper::Task pollingConsumer;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  queue.create(5);

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  producer.start("PollProducer",
                 []
                 {
                   int value = 100;
                   while (true)
                   {
                     // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
                     // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
                     queue.send(value++);
                     delay(700);
                   }
                 });

  pollingConsumer.start("PollConsumer",
                        []
                        {
                          int received;
                          while (true)
                          {
                            // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
                            // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
                            if (queue.receive(received, 0))
                            {
                              Serial.printf("[poll] got %d\n", received);
                            }
                            else
                            {
                              Serial.println("[poll] no data, doing other work...");
                              delay(200);
                            }
                          }
                        });
}

void loop()
{
}
