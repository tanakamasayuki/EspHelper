#include <EspHelperRgbStrip.h>

EspHelper::RgbStrip stripA(2, 16, 180, 50);
EspHelper::RgbStrip stripB(4, 10, 180, 50);

void setup()
{
  Serial.begin(115200);
}

void fillBoth(uint32_t colorA, uint32_t colorB)
{
  stripA.fill(colorA);
  stripB.fill(colorB);
  stripA.show();
  stripB.show();
}

void runningPixel(EspHelper::RgbStrip &strip, uint32_t color, uint16_t wait)
{
  strip.clear();
  for (size_t i = 0; i < strip.size(); ++i)
  {
    strip.clear();
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

void loop()
{
  fillBoth(EspHelper::RgbColor::Orange, 0x10A0FF); // mix named and manual RGB
  delay(500);

  runningPixel(stripA, EspHelper::RgbColor::Purple, 80);
  runningPixel(stripB, EspHelper::RgbColor::Green, 60);

  fillBoth(EspHelper::RgbColor::Black, EspHelper::RgbColor::Black);
  delay(500);
}
