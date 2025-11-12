#include <EspHelperCbor.h>

uint8_t buffer[128];

void encodeSample()
{
  EspHelper::CborWriter writer;
  writer.begin(buffer, sizeof(buffer));
  writer.startMap(3);
  writer.addKeyValue("device", "esp32");
  writer.addKeyValue("temperature", 25);
  writer.addKeyValue("ok", true);
  writer.endContainer();
}

void setup()
{
  Serial.begin(115200);
  encodeSample();

  EspHelper::CborReader reader;
  if (!reader.begin(buffer, sizeof(buffer)) || !reader.isMap())
  {
    Serial.println("Failed to parse CBOR payload");
    return;
  }

  String device;
  int64_t temp = 0;
  bool ok = false;

  if (reader.getString("device", device))
  {
    Serial.print("device: ");
    Serial.println(device);
  }
  if (reader.getInt("temperature", temp))
  {
    Serial.print("temperature: ");
    Serial.println(static_cast<int>(temp));
  }
  if (reader.getBool("ok", ok))
  {
    Serial.print("ok: ");
    Serial.println(ok ? "true" : "false");
  }
}

void loop()
{
}
