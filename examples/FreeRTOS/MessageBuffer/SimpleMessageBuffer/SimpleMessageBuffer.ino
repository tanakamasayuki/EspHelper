// en: Transfer whole messages through a message buffer
// ja: MessageBufferでメッセージ単位のデータを渡す
#include <EspHelperMessageBuffer.h>
#include <EspHelperTask.h>

constexpr size_t kMessageBufferBytes = 128;

EspHelper::MessageBuffer messageBuffer;
EspHelper::Task senderTask;
EspHelper::Task receiverTask;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  messageBuffer.create(kMessageBufferBytes);

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  senderTask.start("MsgSender",
                   []
                   {
                     uint32_t counter = 0;
                     while (true)
                     {
                       char payload[32];
                       snprintf(payload, sizeof(payload), "event:%lu", ++counter);
                       // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
                       // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
                       messageBuffer.send(payload, strlen(payload) + 1);
                       Serial.printf("[sender] queued %s (free %u bytes)\n", payload,
                                     static_cast<unsigned>(messageBuffer.spaceAvailable()));
                       delay(700);
                     }
                   });

  receiverTask.start("MsgReceiver",
                     []
                     {
                       char buffer[32];
                       while (true)
                       {
                         // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
                         // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
                         size_t received = messageBuffer.receive(buffer, sizeof(buffer), 1000);
                         if (received > 0)
                         {
                           Serial.printf("[receiver] got %s (%u bytes, next message %u bytes)\n", buffer,
                                         static_cast<unsigned>(received),
                                         static_cast<unsigned>(messageBuffer.nextMessageSize()));
                         }
                       }
                     });
}

void loop()
{
}
