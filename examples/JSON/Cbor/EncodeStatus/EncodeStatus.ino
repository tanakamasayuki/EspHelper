// en: Encode a status map into a bounded CBOR buffer
// ja: 容量付きバッファへ状態をCBORで書き込む
#include <EspHelperCbor.h>

uint8_t buffer[128];

void printHex(const uint8_t *data, size_t length)
{
  for (size_t i = 0; i < length; ++i)
  {
    Serial.printf("%02X", data[i]);
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  EspHelper::CborWriter writer;
  // en: Initialize this component after its prerequisites; inspect the returned status where provided.
  // ja: 前提となる機器を準備してから初期化し、結果を返すAPIでは成否を確認します。
  if (!writer.begin(buffer, sizeof(buffer)))
  {
    Serial.println("Failed to init CborWriter");
    return;
  }

  writer.startMap(4);
  writer.addKeyValue("device", "esp32");
  writer.addKeyValue("firmware", 101);
  writer.addKeyValue("status", true);

  writer.addKeyValue("uptime", static_cast<uint64_t>(millis()));
  writer.endContainer();

  const size_t bytes = writer.bytesWritten();
  Serial.printf("CBOR bytes (%u):\n", static_cast<unsigned>(bytes));
  printHex(buffer, bytes);
}

void loop()
{
}
