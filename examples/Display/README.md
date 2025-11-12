# Display Examples

[日本語はこちら](README.ja.md)

Display-oriented helpers live here. Today this includes the SPI/I2C LCD helper (`EspHelperLcd.h`) and the RGB LED strip helper (`EspHelperRgbStrip.h`).

## Subdirectories
- [Lcd](Lcd/README.md)
- [RgbStrip](RgbStrip/README.md)

- **Lcd (`EspHelperLcd.h`)** – wraps `esp_lcd` panel APIs (currently ST7789 over SPI and SSD1306 over I2C), exposing Arduino-style drawing helpers.
- **RgbStrip (`EspHelperRgbStrip.h`)** – blocking `rgbLedWrite()` helper that fans out pixels across a daisy-chained strip with color presets and fill helpers.

See the individual subdirectories for API references and sketches.
