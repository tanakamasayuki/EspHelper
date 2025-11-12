# EspHelper

[日本語はこちら](README.ja.md)

EspHelper is a collection of single-header Arduino helpers that expose ESP-IDF capabilities with lightweight, idiomatic APIs. Drop the `.h` you need into a sketch whenever you want Arduino-style ergonomics but still reach for the power of the underlying ESP-IDF components.

## Features
- Header-only wrappers: drop the `.h` file you need into a sketch without pulling extra dependencies.
- Arduino-friendly defaults: utilities work with `Print`, `String`, and familiar Arduino idioms.
- Works alongside the ESP-IDF components that are already bundled in current Arduino-ESP32 releases.
- Examples kept minimal so you can copy/paste straight into an existing project.

## Example Categories
- **JSON**: [JsonGenerator](examples/JSON/JsonGenerator/README.md), [JsonParser](examples/JSON/JsonParser/README.md), [cJSON](examples/JSON/CJson/README.md), [CBOR](examples/JSON/Cbor/README.md)
- **FreeRTOS**: [Task](examples/FreeRTOS/Task/README.md), [Queue](examples/FreeRTOS/Queue/README.md), [Semaphore](examples/FreeRTOS/Semaphore/README.md), [Mutex](examples/FreeRTOS/Mutex/README.md), [MessageBuffer](examples/FreeRTOS/MessageBuffer/README.md), [StreamBuffer](examples/FreeRTOS/StreamBuffer/README.md), [Ringbuffer](examples/FreeRTOS/Ringbuf/README.md)
- **Utility**: [QrCode](examples/Utility/QrCode/README.md), [Dsp](examples/Utility/Dsp/README.md), [Event](examples/Utility/Event/README.md), [Sodium](examples/Utility/Sodium/README.md), [RgbLed](examples/Utility/RgbLed/README.md)
- **Network**: [Mqtt](examples/Network/Mqtt/README.md), [HttpServer](examples/Network/HttpServer/README.md)

## Modules
- `EspHelperJsonGenerator.h`: Arduino-style facade over `espressif/json_generator`, including static buffers, streaming, and reset patterns.
- `EspHelperJsonParser.h`: Thin wrapper for `espressif/json_parser` that manages token buffers and exposes typed getters & navigation helpers.
- `EspHelperCJson.h`: RAII convenience layer for ESP-IDF's `cJSON`, enabling complex manipulations, parsing, and pretty-printing without manual memory handling.
- `EspHelperCbor.h`: JSON-like builder/reader utilities on top of the ESP-IDF `espressif/cbor` (TinyCBOR) component so you can emit compact CBOR payloads.
- `EspHelperQrCode.h`: Captures QR bitmaps generated via `espressif/qrcode` so you can render them as ASCII or paint them onto any display.
- `EspHelperDsp.h`: Real-valued FFT and FIR helpers on top of `esp_dsp`, complete with Hann windows and FIR delay-line management.
- `EspHelperEvent.h`: Minimal RAII interface around `esp_event`, covering default/custom loops, handler registration, and posting helpers.
- `EspHelperSodium.h`: Convenience wrappers for libsodium randomness, `crypto_secretbox`, and Ed25519 signatures.
- `EspHelperMqtt.h`: Wrapper over `esp-mqtt` with Arduino-style lifecycle, single event callback, and helpers for publish/subscribe operations.
- `EspHelperHttpServer.h`: Lightweight wrapper around `esp_http_server` with WebServer-like route registration helpers.
- `EspHelperRgbStrip.h`: Blocking convenience class that fans out `rgbLedWrite()` calls across discrete RGB LEDs using an Adafruit_NeoPixel-like API.
- `EspHelperTask.h`: RAII convenience wrapper for FreeRTOS tasks (start/stop with C++ lambdas).
- `EspHelperQueue.h`: Template FreeRTOS queue helper that wraps `xQueueSend`/`xQueueReceive` with C++ ergonomics.
- `EspHelperSemaphore.h`: Binary/counting semaphore wrapper with RAII creation and typed `give`/`take`.
- `EspHelperMutex.h`: Thin RAII mutex helper built atop `xSemaphoreCreateMutex`.
- `EspHelperMessageBuffer.h`: Convenience layer over FreeRTOS message buffers that preserves per-message framing and exposes peek/space helpers.
- `EspHelperStreamBuffer.h`: Arduino wrapper for FreeRTOS stream buffers, ideal for byte pipes between tasks or ISRs (with optional trigger levels and static allocation).
- `EspHelperRingbuf.h`: RAII helpers for FreeRTOS `ringbuf`, covering dynamic/static creation, ISR-safe send/receive, and auto-returned items.

## Requirements
- Arduino core for ESP32 (v2.0.0 or newer) or a PlatformIO environment targeting `esp32`.
- A C++17 capable toolchain (the default for modern Arduino-ESP32).

## Installation
### Arduino IDE / Arduino CLI
1. Clone or download this repository into your Arduino `libraries` directory so that the folder becomes `~/Arduino/libraries/EspHelper`.
2. Include the header you need from `src/` in your sketch. The ESP-IDF components leveraged by EspHelper are already part of recent Arduino ESP32 cores, so no additional setup is necessary.

## License
MIT License – see [LICENSE](LICENSE).
