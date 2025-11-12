# Display サンプル

[English README](README.md)

ディスプレイ関連のヘルパーをまとめています。現在は `esp_lcd` ベースのLCDラッパー (`EspHelperLcd.h`) とRGB LEDストリップラッパー (`EspHelperRgbStrip.h`) を収録しています。

## サブディレクトリ
- [Lcd](Lcd/README.ja.md)
- [RgbStrip](RgbStrip/README.ja.md)

- **Lcd (`EspHelperLcd.h`)** – ST7789(SPI) / SSD1306(I2C) をArduino風APIで扱える`esp_lcd`ラッパー。
- **RgbStrip (`EspHelperRgbStrip.h`)** – `rgbLedWrite()` ベースで直列RGB LEDを制御するラッパー。

詳細は各ディレクトリのREADMEを参照してください。
