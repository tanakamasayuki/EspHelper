// en: Handle a receive timeout without using stale data
// ja: Receiveの時間切れを検出し、古い値を使わない
#include <EspHelperQueue.h>
#include <EspHelperTask.h>

EspHelper::Queue<const char *> queue;
EspHelper::Task producer;
EspHelper::Task timeoutConsumer;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  queue.create(3);

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  producer.start("SlowProducer",
                 []
                 {
                   const char *messages[] = {"one", "two", "three"};
                   size_t index = 0;
                   while (true)
                   {
                     // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
                     // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
                     queue.send(messages[index]);
                     index = (index + 1) % 3;
                     delay(1500); // intentionally slow so the consumer times out sometimes
                   }
                 });

  timeoutConsumer.start("TimeoutConsumer",
                        []
                        {
                          const TickType_t waitTicks = 750; // milliseconds in Arduino builds
                          const uint32_t waitMs = 750;
                          const char *msg = nullptr;
                          while (true)
                          {
                            // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
                            // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
                            if (queue.receive(msg, waitTicks))
                            {
                              Serial.printf("[timeout] received: %s\n", msg);
                            }
                            else
                            {
                              Serial.printf("[timeout] waited %lu ms, no message\n", waitMs);
                            }
                          }
                        });
}

void loop()
{
}
