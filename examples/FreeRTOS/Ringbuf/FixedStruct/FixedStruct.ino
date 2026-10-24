// en: Transfer a fixed structure using a no-split ring buffer
// ja: 分割しないRingbufferで固定構造体を渡す
#include <EspHelperRingbuf.h>

struct SensorPacket
{
  uint32_t sequence;
  float temperature;
  float humidity;
};

StaticRingbuffer_t staticControl;
uint8_t staticStorage[sizeof(SensorPacket) * 8 + 32];
EspHelper::Ringbuffer ringbuf(staticStorage, sizeof(staticStorage), staticControl, RINGBUF_TYPE_NOSPLIT);

SensorPacket packet{};

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Ringbuffer fixed-struct example");
}

void loop()
{
  packet.sequence++;
  packet.temperature = 24.5f + (millis() % 1000) / 1000.0f;
  packet.humidity = 40.0f + (millis() % 500) / 1000.0f;
  // en: Submit the supplied data and check the API-specific result; acceptance is different from later processing.
  // ja: データを渡して対象APIの結果を確認します。受理されたことと後の処理完了は別です。
  ringbuf.send(&packet, sizeof(packet));

  // en: Consume output only after a successful receive; a timeout does not produce a new valid item.
  // ja: 受信成功を確認してから出力を使います。時間切れでは新しい有効値は得られません。
  auto item = ringbuf.receive(10);
  if (item.valid() && item.size() == sizeof(SensorPacket))
  {
    auto *rx = reinterpret_cast<const SensorPacket *>(item.data());
    Serial.printf("seq=%lu temp=%.2fC hum=%.2f%%\n",
                  static_cast<unsigned long>(rx->sequence), rx->temperature, rx->humidity);
  }

  delay(600);
}
