#include <EspHelperSodium.h>

void setup()
{
  Serial.begin(115200);
  if (!EspHelper::Sodium::init())
  {
    Serial.println(F("libsodium init failed"));
    while (true)
    {
      delay(1000);
    }
  }

  Serial.println(F("Random hex samples (16-byte each):"));
  for (int i = 0; i < 5; ++i)
  {
    String hex = EspHelper::Sodium::randomHex(16);
    Serial.println(hex);
    delay(1000);
  }
}

void loop()
{
}
