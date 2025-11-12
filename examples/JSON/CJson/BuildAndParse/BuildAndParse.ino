#include <EspHelperCJson.h>

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  // Build a JSON document using cJSON helper
  EspHelper::CJsonDocument doc = EspHelper::CJsonDocument::NewObject();
  doc.addString("device", "esp32");
  doc.addNumber("uptime_ms", millis());
  doc.addBool("connected", true);
  auto metrics = EspHelper::CJsonDocument::NewArray();
  metrics.arrayAddNumber(3.14);
  metrics.arrayAddNumber(0.618);
  doc.addArray("metrics", std::move(metrics));

  Serial.println("Generated JSON (compact):");
  Serial.println(doc.toString(false));
  Serial.println("Generated JSON (pretty):");
  Serial.println(doc.toString(true));

  // Parse back and access fields
  EspHelper::CJsonDocument parsed = EspHelper::CJsonDocument::Parse(doc.toString());
  if (parsed.valid() && parsed.isObject())
  {
    String name;
    double uptime = 0;
    bool connected = false;
    parsed.getString("device", name);
    parsed.getNumber("uptime_ms", uptime);
    parsed.getBool("connected", connected);
    Serial.printf("Parsed: device=%s uptime=%.0f connected=%s\n", name.c_str(), uptime, connected ? "true" : "false");
  }

  delay(5000);
}
