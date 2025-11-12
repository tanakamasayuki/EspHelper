#include <EspHelperJsonGenerator.h>

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  char jsonBuffer[256];
  EspHelper::JsonGenerator json(jsonBuffer);
  json.startObject();
  json.setString("app", "EspHelper");
  json.setInt("heap", ESP.getFreeHeap());
  json.pushArray("pins");
  json.arrayAddInt(2);
  json.arrayAddInt(4);
  json.arrayAddInt(5);
  json.popArray();
  json.endObject();
  json.finish();

  Serial.println(json.c_str());

  delay(5000);
}
