# Utility Examples

[日本語はこちら](README.ja.md)

Utility examples collect helpers that do not fall into JSON or FreeRTOS buckets. Currently this includes QR code rendering via the ESP-IDF `espressif/qrcode` component.

- **QrCode (`EspHelperQrCode.h`)** – generate QR codes once and reuse the captured bitmap for ASCII output, serial printing, or custom displays such as M5Unified.

See `QrCode/` for concrete sketches.
