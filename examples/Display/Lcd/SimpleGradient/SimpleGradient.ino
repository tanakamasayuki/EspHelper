#include <EspHelperLcd.h>
#include <vector>

EspHelper::LcdPanel lcd;

void setup()
{
  Serial.begin(115200);
  EspHelper::LcdPanel::St7789Config cfg;
  cfg.mosi_pin = 13;
  cfg.sclk_pin = 14;
  cfg.dc_pin = 21;
  cfg.cs_pin = 15;
  cfg.rst_pin = 16;
  cfg.bl_pin = 4;
  cfg.width = 240;
  cfg.height = 240;
  cfg.pclk_hz = 40 * 1000 * 1000;

  if (!lcd.begin(cfg))
  {
    Serial.println("Failed to init ST7789");
    while (true)
    {
      delay(1000);
    }
  }

  drawGradient();
}

uint16_t color565(uint8_t r, uint8_t g, uint8_t b)
{
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void drawGradient()
{
  const int width = lcd.width();
  const int height = lcd.height();
  std::vector<uint16_t> line(width);
  for (int y = 0; y < height; ++y)
  {
    uint8_t red = (y * 255) / height;
    for (int x = 0; x < width; ++x)
    {
      uint8_t green = (x * 255) / width;
      uint8_t blue = 255 - green;
      line[x] = color565(red, green, blue);
    }
    lcd.drawBitmap(0, y, width, 1, line.data());
  }
}

void loop()
{
}
