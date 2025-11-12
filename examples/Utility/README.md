# Utility Examples

[日本語はこちら](README.ja.md)

Utility examples collect helpers that do not fall into JSON or FreeRTOS buckets. Currently this includes QR code rendering via the ESP-IDF `espressif/qrcode` component and a simple wrapper around the Arduino `rgbLedWrite()` helper.

- **QrCode (`EspHelperQrCode.h`)** – generate QR codes once and reuse the captured bitmap for ASCII output, serial printing, or custom displays such as M5Unified.
- **RgbStrip (`EspHelperRgbStrip.h`)** – drive a strip of RGB LEDs chained on a single pin using a blocking API similar to Adafruit_NeoPixel, backed by repeated `rgbLedWrite()` calls.

See `QrCode/` and `RgbLed/` for concrete sketches.
