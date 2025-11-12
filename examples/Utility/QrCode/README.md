# QrCode Examples

[日本語はこちら](README.ja.md)

`EspHelperQrCode.h` wraps the ESP-IDF `espressif/qrcode` component so you can capture a QR bitmap once and reuse it. Choose your rendering strategy:

- Use `toAscii()` to dump the QR code in a serial console (see `AsciiConsole`).
- Iterate with `forEachModule()` to paint pixels on displays such as M5Unified (see `M5Display`).

## Example overview
- `AsciiConsole/AsciiConsole.ino` – Generates a QR that encodes a URL and prints it using ASCII blocks.
- `M5Display/M5Display.ino` – Renders a Wi-Fi provisioning QR on an M5 device via M5Unified.

> **Note**: The display example depends on the [M5Unified](https://github.com/m5stack/M5Unified) library. Install it before building.
