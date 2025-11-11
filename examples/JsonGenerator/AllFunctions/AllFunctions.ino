#include <EspHelperJsonGenerator.h>

namespace
{

  constexpr size_t kPrimarySize = 512;
  constexpr size_t kSecondarySize = 128;

  char primaryBuffer[kPrimarySize];
  char secondaryBuffer[kSecondarySize];

  EspHelper::JsonGenerator generator(primaryBuffer);
  int cycle = 0;

  void serialFlush(char *buf, void *priv)
  {
    if (!buf || !priv)
    {
      return;
    }
    static_cast<Print *>(priv)->print(buf);
  }

  void buildPrimaryDocument()
  {
    if (!generator.valid())
    {
      Serial.println("JsonGenerator is not ready");
      return;
    }

    generator.reset();
    generator.startArray(); // root array using startArray()/endArray()

    generator.startObject();                         // first element (object)
    generator.setString("example", "AllFunctions");  // const char * overload
    generator.setString("version", String("0.1.0")); // String overload
    generator.setBool("enabled", true);
    generator.setInt("cycle", cycle);
    generator.setFloat("ratio", 0.618f);
    generator.setNull("placeholder");

    generator.pushObject("device");
    generator.setString("chip", String(ESP.getChipModel()));
    generator.setInt("revision", ESP.getChipRevision());
    generator.popObject();

    generator.pushArray("pins");
    generator.arrayAddInt(2);
    generator.arrayAddFloat(3.3f);
    generator.arrayAddBool(false);
    generator.arrayAddString("GPIO12");
    String dynamicTag = String("ADC1_CH") + String(cycle % 8);
    generator.arrayAddString(dynamicTag); // String overload
    generator.arrayAddNull();
    generator.popArray();

    generator.pushArray("flags");
    generator.arrayAddBool(true);
    generator.arrayAddBool(false);
    generator.popArray();

    generator.startArray(); // unnamed nested array (second element inside root)
    generator.arrayAddString("nested");
    generator.arrayAddInt(42);
    generator.endArray();

    json_gen_push_object_str(generator.raw(), "pre_encoded", "{\"foo\":1}");

    generator.endObject();

    generator.startObject(); // third element inside the root array
    generator.setString("note", "tail");
    generator.endObject();

    generator.endArray(); // end root array

    int totalWithNull = generator.finish();
    Serial.printf("\n[cycle %d] buffer=%p capacity=%u bytes\n", cycle, static_cast<void *>(generator.data()),
                  static_cast<unsigned>(generator.capacity()));
    Serial.printf("finish() -> %d bytes, length() -> %u chars\n", totalWithNull, static_cast<unsigned>(generator.length()));
    Serial.println(generator.c_str());

    ++cycle;
  }

  void demonstrateResetVariants()
  {
    Serial.println("\n--- reset(json_gen_flush_cb_t, void*) ---");
    generator.reset(&serialFlush, &Serial);
    generator.startObject();
    generator.setString("mode", "flush-primary");
    generator.endObject();
    generator.finish();
    Serial.println();

    Serial.println("\n--- reset(char*, size_t, json_gen_flush_cb_t, void*) ---");
    generator.reset(secondaryBuffer, kSecondarySize, &serialFlush, &Serial);
    generator.startObject();
    generator.setString("buffer", "secondary");
    generator.setBool("streamed", true);
    generator.endObject();
    generator.finish();
    Serial.println();

    Serial.println("\n--- reset(char (&)[N]) template overload ---");
    char tempBuffer[64];
    generator.reset(tempBuffer);
    generator.startArray();
    generator.arrayAddString("temp");
    generator.endArray();
    generator.finish();
    Serial.println();

    generator.reset(primaryBuffer); // restore original buffer without a flush callback
  }

  void demonstrateStreamingConstructor()
  {
    Serial.println("\n--- JsonGenerator(Print&, chunkSize) ---");
    EspHelper::JsonGenerator streamingJson(Serial, 64);
    streamingJson.startObject();
    streamingJson.setString("streaming", "enabled");
    streamingJson.pushArray("sequence");
    streamingJson.arrayAddInt(1);
    streamingJson.arrayAddFloat(2.5f);
    streamingJson.arrayAddBool(true);
    streamingJson.popArray();
    streamingJson.endObject();
    streamingJson.finish();
    Serial.println();
  }

} // namespace

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  buildPrimaryDocument();
  demonstrateResetVariants();
  demonstrateStreamingConstructor();
  delay(4000);
}
