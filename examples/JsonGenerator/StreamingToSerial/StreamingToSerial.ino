#include <EspHelperJsonGenerator.h>

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  EspHelper::JsonGenerator json(Serial);
  json.startObject();
  json.setInt("uptime_ms", millis());
  json.setBool("streamed", true);
  json.pushArray("last_samples");
  for (int i = 0; i < 3; ++i)
  {
    json.arrayAddInt(i * 10);
  }
  json.popArray();
  json.endObject();
  json.finish();

  Serial.println();
  delay(5000);
}
