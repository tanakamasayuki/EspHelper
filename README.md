# EspHelper

[日本語はこちら](README.ja.md)

EspHelper is a collection of single-header Arduino helpers that expose ESP-IDF capabilities with lightweight, idiomatic APIs. Drop the `.h` you need into a sketch whenever you want Arduino-style ergonomics but still reach for the power of the underlying ESP-IDF components.

## Features
- Header-only wrappers: drop the `.h` file you need into a sketch without pulling extra dependencies.
- Arduino-friendly defaults: utilities work with `Print`, `String`, and familiar Arduino idioms.
- Works alongside the ESP-IDF components that are already bundled in current Arduino-ESP32 releases.
- Examples kept minimal so you can copy/paste straight into an existing project.

## Example Categories
- **JSON**: [JsonGenerator](examples/JSON/JsonGenerator/README.md), [JsonParser](examples/JSON/JsonParser/README.md), [cJSON](examples/JSON/CJson/README.md)
- **FreeRTOS**: [Ringbuffer](examples/FreeRTOS/Ringbuf/README.md), [Task](examples/FreeRTOS/Task/README.md)
- **Utility**: [QrCode](examples/Utility/QrCode/README.md), [RgbLed](examples/Utility/RgbLed/README.md), [HttpServer](examples/Utility/HttpServer/README.md)

## Modules
- `EspHelperJsonGenerator.h`: Arduino-style facade over `espressif/json_generator`, including static buffers, streaming, and reset patterns.
- `EspHelperJsonParser.h`: Thin wrapper for `espressif/json_parser` that manages token buffers and exposes typed getters & navigation helpers.
- `EspHelperCJson.h`: RAII convenience layer for ESP-IDF's `cJSON`, enabling complex manipulations, parsing, and pretty-printing without manual memory handling.
- `EspHelperQrCode.h`: Captures QR bitmaps generated via `espressif/qrcode` so you can render them as ASCII or paint them onto any display.
- `EspHelperRingbuf.h`: RAII helpers for FreeRTOS `ringbuf`, covering dynamic/static creation, ISR-safe send/receive, and auto-returned items.
- `EspHelperHttpServer.h`: Lightweight wrapper around `esp_http_server` with WebServer-like route registration helpers.
- `EspHelperTask.h`: RAII convenience wrapper for FreeRTOS tasks (start/stop with C++ lambdas).
- `EspHelperRgbStrip.h`: Blocking convenience class that fans out `rgbLedWrite()` calls across discrete RGB LEDs using an Adafruit_NeoPixel-like API.

## Requirements
- Arduino core for ESP32 (v2.0.0 or newer) or a PlatformIO environment targeting `esp32`.
- A C++17 capable toolchain (the default for modern Arduino-ESP32).

## Installation
### Arduino IDE / Arduino CLI
1. Clone or download this repository into your Arduino `libraries` directory so that the folder becomes `~/Arduino/libraries/EspHelper`.
2. Include the header you need from `src/` in your sketch. The ESP-IDF components leveraged by EspHelper are already part of recent Arduino ESP32 cores, so no additional setup is necessary.

## License
MIT License – see [LICENSE](LICENSE).
