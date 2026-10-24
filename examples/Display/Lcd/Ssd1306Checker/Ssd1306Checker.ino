// en: Draw a checker pattern on an SSD1306 display
// ja: SSD1306へ市松模様を描く
#include <EspHelperLcd.h>
#include <vector>

EspHelper::LcdPanel oled;

void setup()
{
  Serial.begin(115200);
  EspHelper::LcdPanel::Ssd1306Config cfg;
  cfg.i2c_port = I2C_NUM_0;
  cfg.sda_pin = 21;
  cfg.scl_pin = 22;
  cfg.width = 128;
  cfg.height = 64;
  cfg.address = 0x3C;

  // en: Initialize this component after its prerequisites; inspect the returned status where provided.
  // ja: 前提となる機器を準備してから初期化し、結果を返すAPIでは成否を確認します。
  if (!oled.begin(cfg))
  {
    Serial.println("Failed to init SSD1306");
    while (true)
    {
      delay(1000);
    }
  }

  drawChecker();
}

void drawChecker()
{
  const int width = oled.width();
  const int height = oled.height();
  const size_t bytes_per_row = (width + 7) / 8;
  std::vector<uint8_t> row(bytes_per_row);

  for (int y = 0; y < height; ++y)
  {
    bool row_on = (y / 8) % 2 == 0;
    for (size_t byte = 0; byte < bytes_per_row; ++byte)
    {
      uint8_t pattern = row_on ? 0xAA : 0x55;
      row[byte] = pattern;
    }
    oled.drawBitmap(0, y, width, 1, row.data());
  }
}

void loop()
{
}
