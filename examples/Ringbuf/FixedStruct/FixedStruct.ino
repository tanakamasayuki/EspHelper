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
  ringbuf.send(&packet, sizeof(packet));

  auto item = ringbuf.receive(pdMS_TO_TICKS(10));
  if (item.valid() && item.size() == sizeof(SensorPacket))
  {
    auto *rx = reinterpret_cast<const SensorPacket *>(item.data());
    Serial.printf("seq=%lu temp=%.2fC hum=%.2f%%\n",
                  static_cast<unsigned long>(rx->sequence), rx->temperature, rx->humidity);
  }

  delay(600);
}
