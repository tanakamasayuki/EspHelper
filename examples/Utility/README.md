# Utility Examples

[日本語はこちら](README.ja.md)

Utility examples collect helpers that do not fall into JSON, FreeRTOS, or networking buckets. Currently this includes QR code rendering via the ESP-IDF `espressif/qrcode` component, DSP helpers powered by `esp_dsp`, the generic `esp_event` wrapper, and an Arduino-style façade over `rgbLedWrite()`.

- **QrCode (`EspHelperQrCode.h`)** – generate QR codes once and reuse the captured bitmap for ASCII output, serial printing, or custom displays such as M5Unified.
- **Dsp (`EspHelperDsp.h`)** – real-valued FFT and FIR filters that wrap `esp_dsp` with Arduino-friendly buffers.
- **Event (`EspHelperEvent.h`)** – manage `esp_event` loops, handlers, and postings with a minimal RAII wrapper.
- **Sodium (`EspHelperSodium.h`)** – thin wrappers over libsodium for randomness, `crypto_secretbox`, and Ed25519 signatures.
- **RgbStrip (`EspHelperRgbStrip.h`)** – drive a strip of RGB LEDs chained on a single pin using a blocking API similar to Adafruit_NeoPixel, backed by repeated `rgbLedWrite()` calls.

See `QrCode/`, `Dsp/`, `Event/`, `Sodium/`, and `RgbLed/` for concrete sketches.
