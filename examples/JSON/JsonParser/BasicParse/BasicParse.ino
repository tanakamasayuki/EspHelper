#include <EspHelperJsonParser.h>

const char *kSample = R"JSON(
{
  "device": {
    "name": "EnvNode",
    "revision": 3,
    "calibration": {
      "ratio": 0.618,
      "enabled": true
    }
  },
  "pins": [2, 4, 5],
  "flags": [true, false, true]
}
)JSON";

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  EspHelper::JsonParser parser(128); // owns 128 tokens internally

  if (!parser.parse(kSample))
  {
    Serial.println("Failed to parse JSON");
    return;
  }

  if (parser.enterObject("device"))
  {
    String name;
    int revision = 0;
    if (parser.getString("name", name))
    {
      Serial.print("name: ");
      Serial.println(name);
    }
    if (parser.getInt("revision", revision))
    {
      Serial.print("revision: ");
      Serial.println(revision);
    }

    if (parser.enterObject("calibration"))
    {
      float ratio = 0;
      bool enabled = false;
      parser.getFloat("ratio", ratio);
      parser.getBool("enabled", enabled);
      Serial.printf("calibration ratio: %.3f enabled: %s\n", ratio, enabled ? "true" : "false");
      parser.leaveObject();
    }

    parser.leaveObject();
  }

  int pinCount = 0;
  if (parser.enterArray("pins", &pinCount))
  {
    Serial.print("pins: ");
    for (int i = 0; i < pinCount; ++i)
    {
      int pinValue = 0;
      if (parser.arrayGetInt(i, pinValue))
      {
        Serial.printf("%d ", pinValue);
      }
    }
    Serial.println();
    parser.leaveArray();
  }

  if (parser.enterArray("flags", nullptr))
  {
    Serial.print("flags: ");
    for (uint32_t idx = 0;; ++idx)
    {
      bool value = false;
      if (!parser.arrayGetBool(idx, value))
      {
        break;
      }
      Serial.print(value ? "true " : "false ");
    }
    Serial.println();
    parser.leaveArray();
  }

  parser.end();
  Serial.println();

  delay(5000);
}
