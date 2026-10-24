// en: Receive a scoped view of ring-buffered bytes
// ja: Ringbufferのバイト列を寿命付きviewで受け取る
#include <EspHelperRingbuf.h>

EspHelper::Ringbuffer ringbuf(256, RINGBUF_TYPE_BYTEBUF);
uint32_t counter = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Ringbuffer byte-buffer example");
}

void loop()
{
  char message[64];
  size_t len = snprintf(message, sizeof(message), "msg=%lu millis=%lu", static_cast<unsigned long>(counter++),
                        static_cast<unsigned long>(millis()));
  // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
  // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
  ringbuf.send(message, len);

  while (true)
  {
    // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
    // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
    auto item = ringbuf.receive(0);
    if (!item.valid())
    {
      break;
    }
    Serial.print("Received size=");
    Serial.print(item.size());
    Serial.print(" data=");
    Serial.write(item.data(), item.size());
    Serial.println();
    // item destructor returns buffer automatically
  }

  delay(500);
}
