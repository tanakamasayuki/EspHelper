# QrCode Examples

[日本語はこちら](README.ja.md)

`EspHelperQrCode.h` wraps the ESP-IDF `espressif/qrcode` component so you can generate once and render anywhere.

## API Reference
- `bool generate(const char *text, int maxVersion = 10, int eccLevel = ESP_QRCODE_ECC_MED)` – Runs `esp_qrcode_generate` and captures the bitmap via the internal callback.
- `bool ready() const` / `int size() const` – Inspect whether a QR bitmap is available and its side length.
- `bool module(int x, int y) const` – Read individual modules (true = black).
- `template <typename Fn> void forEachModule(Fn fn)` – Iterate through every module with a lambda `(x, y, bool on)`.
- `String toAscii(const char *dark = "██", const char *light = "  ", int border = 2)` – Render an ASCII representation with configurable glyphs/border.

## Example Overview
- `AsciiConsole/AsciiConsole.ino` – Generates a QR that encodes a URL and prints it as ASCII art over `Serial`.
- `M5Display/M5Display.ino` – Draws a Wi-Fi provisioning QR code on an M5 device using M5Unified.
