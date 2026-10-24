// en: Generate JSON into caller-owned fixed storage
// ja: 自分で用意した固定領域へJSONを生成する
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
  // en: Finalize the generated structure and check capacity/error status before using the output.
  // ja: 生成中の構造を完了し、容量／Errorを確認してから出力を使います。
  json.finish();

  Serial.println(json.c_str());

  delay(5000);
}
