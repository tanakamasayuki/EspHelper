# Lcd Examples

[日本語はこちら](README.ja.md)

`EspHelperLcd.h` provides Arduino-friendly glue for the display models supported by `esp_lcd_panel_vendor` today: ST7789 (SPI) and SSD1306 (I2C). The class hides bus setup, panel creation, and offers helpers (`drawBitmap`, `drawPixel`, `fillScreen`, `setBacklight`).

## API Reference (St7789Panel)
- `bool begin(const Config &cfg)` – configure SPI pins, panel size, offsets, and backlight GPIO.
- `void end()` – delete the panel, IO handle, and SPI bus (if owned).
- `bool drawBitmap(int x, int y, int width, int height, const void *pixels)` – push RGB565 pixels.
- `bool drawPixel(int x, int y, uint16_t color)` – convenience helper.
- `bool fillScreen(uint16_t color)` – fills the display using an internal line buffer.
- `void setBacklight(bool on)` – toggles backlight GPIO (if provided).

## Example overview
- `SimpleGradient/SimpleGradient.ino` – demonstrates the minimal config required to bring up an ST7789 panel and render a gradient line-by-line.
- `Ssd1306Checker/Ssd1306Checker.ino` – brings up an SSD1306 over I2C and renders a checker-board style pattern.
