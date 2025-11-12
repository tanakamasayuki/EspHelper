# Utility Examples

[日本語はこちら](README.ja.md)

Utility examples collect helpers that do not fall into JSON or FreeRTOS buckets. Currently this includes QR code rendering via the ESP-IDF `espressif/qrcode` component, a simple wrapper around the Arduino `rgbLedWrite()` helper, and a WebServer-style façade over `esp_http_server`.

- **QrCode (`EspHelperQrCode.h`)** – generate QR codes once and reuse the captured bitmap for ASCII output, serial printing, or custom displays such as M5Unified.
- **RgbStrip (`EspHelperRgbStrip.h`)** – drive a strip of RGB LEDs chained on a single pin using a blocking API similar to Adafruit_NeoPixel, backed by repeated `rgbLedWrite()` calls.
- **HttpServer (`EspHelperHttpServer.h`)** – register GET/POST routes with lambdas and send responses using helper methods like `sendText`/`sendJson`.

See `QrCode/`, `RgbLed/`, and `HttpServer/` for concrete sketches.
