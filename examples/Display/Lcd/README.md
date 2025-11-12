# Lcd Examples

[日本語はこちら](README.ja.md)

`EspHelperLcd.h` provides Arduino-friendly glue for the display models supported by `esp_lcd_panel_vendor` today: ST7789 (SPI) and SSD1306 (I2C). The class hides bus setup, panel creation, and offers helpers (`drawBitmap`, `drawPixel`, `fillScreen`, `setBacklight`).

- `bool begin(const St7789Config &cfg)` / `bool begin(const Ssd1306Config &cfg)` – configure SPI or I2C pins, panel geometry, brightness/backlight pins, etc.
- `void end()` – delete the panel, IO handle, and owned bus/driver resources.
- `bool drawBitmap(int x, int y, int width, int height, const void *pixels)` – push RGB565 (ST7789) or 1-bit (SSD1306) pixels.
- `bool drawPixel(int x, int y, uint16_t color)` – convenience helper (color treated as on/off for SSD1306).
- `bool fillScreen(uint16_t color)` – fills the display using an internal line buffer suited to the pixel format.
- `void setBacklight(bool on)` – toggles backlight GPIO when configured (ST7789).
- `int width() const / int height() const` – query the active resolution.

## Example overview
- `SimpleGradient/SimpleGradient.ino` – demonstrates the minimal config required to bring up an ST7789 panel and render a gradient line-by-line.
- `Ssd1306Checker/Ssd1306Checker.ino` – brings up an SSD1306 over I2C and renders a checker-board style pattern.
