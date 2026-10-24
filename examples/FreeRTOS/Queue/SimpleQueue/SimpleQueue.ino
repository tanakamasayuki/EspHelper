// en: Copy values between a producer and consumer
// ja: 生成側と受信側で値をコピーして受け渡す
#include <EspHelperQueue.h>
#include <EspHelperTask.h>

EspHelper::Queue<int> queue;
EspHelper::Task producer;
EspHelper::Task consumer;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  queue.create(5);

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  producer.start("Producer", []
                 {
    int value = 0;
    while (true)
    {
      // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
      // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
      queue.send(++value);
      Serial.printf("Produced %d\n", value);
      delay(500);
    } });

  consumer.start("Consumer", []
                 {
    int received;
    while (true)
    {
      // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
      // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
      if (queue.receive(received, 1000))
      {
        Serial.printf("Consumed %d\n", received);
      }
    } });
}

void loop()
{
}
