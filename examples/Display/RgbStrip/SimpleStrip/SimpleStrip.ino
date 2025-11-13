#include <EspHelperRgbStrip.h>

constexpr uint8_t kStripPin = 2;
constexpr size_t kLedCount = 25;
EspHelper::RgbStrip strip(kStripPin, kLedCount, 200, 0);

uint32_t wheel(uint8_t pos)
{
  pos = 255 - pos;
  if (pos < 85)
  {
    return ((255 - pos * 3) << 16) | (pos * 3);
  }
  if (pos < 170)
  {
    pos -= 85;
    return ((pos * 3) << 8) | (255 - pos * 3);
  }
  pos -= 170;
  return ((pos * 3) << 16) | ((255 - pos * 3) << 8);
}

void setup()
{
  Serial.begin(115200);
}

void fillWithPalette()
{
  strip.fill(EspHelper::RgbColor::White);
  strip.show();
  delay(400);

  strip.fill(EspHelper::RgbColor::Blue);
  strip.show();
  delay(400);
}

void rainbow(uint8_t wait)
{
  for (uint16_t j = 0; j < 256; ++j)
  {
    for (size_t i = 0; i < strip.size(); ++i)
    {
      strip.setPixelColor(i, wheel((i + j) & 0xFF));
    }
    strip.show();
    delay(wait);
  }
}

void loop()
{
  fillWithPalette();

  for (size_t i = 0; i < strip.size(); ++i)
  {
    strip.setPixelColor(i, 0, 0, 128); // manual RGB tuple
  }
  strip.show();
  delay(400);

  rainbow(15);
}
