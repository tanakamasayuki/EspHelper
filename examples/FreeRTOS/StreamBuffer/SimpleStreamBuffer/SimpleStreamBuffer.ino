// en: Exchange byte chunks through a stream buffer
// ja: StreamBufferでバイト列を受け渡す
#include <EspHelperStreamBuffer.h>
#include <EspHelperTask.h>

constexpr size_t kStreamCapacity = 64;

EspHelper::StreamBuffer streamBuffer;
EspHelper::Task producerTask;
EspHelper::Task consumerTask;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  streamBuffer.create(kStreamCapacity);

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  producerTask.start("StreamWriter",
                     []
                     {
                       const char *chunk = "temp=24.8C;";
                       while (true)
                       {
                         // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
                         // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
                         streamBuffer.send(chunk, strlen(chunk));
                         Serial.println("[writer] chunk queued");
                         delay(300);
                       }
                     });

  consumerTask.start("StreamReader",
                     []
                     {
                       char buffer[32];
                       while (true)
                       {
                         // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
                         // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
                         size_t received = streamBuffer.receive(buffer, sizeof(buffer) - 1, 1000);
                         if (received > 0)
                         {
                           buffer[received] = '\0';
                           Serial.printf("[reader] %s (pending %u bytes)\n", buffer,
                                         static_cast<unsigned>(streamBuffer.bytesAvailable()));
                         }
                       }
                     });
}

void loop()
{
}
