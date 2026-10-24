// en: Write generated JSON directly to Serial
// ja: 生成するJSONをシリアルへ直接出力する
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
  // en: Finalize the generated structure and check capacity/error status before using the output.
  // ja: 生成中の構造を完了し、容量／Errorを確認してから出力を使います。
  json.finish();

  Serial.println();
  delay(5000);
}
