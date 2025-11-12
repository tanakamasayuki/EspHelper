# EspHelper

[日本語はこちら](README.ja.md)

EspHelper is a collection of single-header Arduino helpers that expose ESP-IDF capabilities with lightweight, idiomatic APIs. Drop the `.h` you need into a sketch whenever you want Arduino-style ergonomics but still reach for the power of the underlying ESP-IDF components.

## Features
- Header-only wrappers: drop the `.h` file you need into a sketch without pulling extra dependencies.
- Arduino-friendly defaults: utilities work with `Print`, `String`, and familiar Arduino idioms.
- Works alongside the ESP-IDF components that are already bundled in current Arduino-ESP32 releases.
- Examples kept minimal so you can copy/paste straight into an existing project.

## Modules
- `EspHelperJsonGenerator.h`: Arduino-style facade over `espressif/json_generator`, including static buffers, streaming, and reset patterns.
- `EspHelperJsonParser.h`: Thin wrapper for `espressif/json_parser` that manages token buffers and exposes typed getters & navigation helpers.
- `EspHelperRingbuf.h`: RAII helpers for FreeRTOS `ringbuf`, covering dynamic/static creation, ISR-safe send/receive, and auto-returned items.

## Requirements
- Arduino core for ESP32 (v2.0.0 or newer) or a PlatformIO environment targeting `esp32`.
- A C++17 capable toolchain (the default for modern Arduino-ESP32).

## Installation
### Arduino IDE / Arduino CLI
1. Clone or download this repository into your Arduino `libraries` directory so that the folder becomes `~/Arduino/libraries/EspHelper`.
2. Include the header you need from `src/` in your sketch. The ESP-IDF components leveraged by EspHelper are already part of recent Arduino ESP32 cores, so no additional setup is necessary.

## Examples
- `examples/JSON/JsonGenerator/AllFunctions` – exercises every `JsonGenerator` method (including reset variations and streaming) in one sketch.
- `examples/JSON/JsonGenerator/StaticJsonBuffer` – builds a JSON document into a fixed stack buffer and prints it to `Serial`.
- `examples/JSON/JsonGenerator/StreamingToSerial` – streams JSON tokens directly to `Serial` via the `Print`-based constructor for minimal RAM usage.
- `examples/JSON/JsonParser/BasicParse` – tokenizes and queries nested JSON using `JsonParser`, including arrays, nested objects, and typed getters.
- `examples/FreeRTOS/Ringbuf/ByteBuffer` – uses `EspHelper::Ringbuffer` to push formatted strings into a BYTEBUF ring buffer and read them back immediately.
- `examples/FreeRTOS/Ringbuf/FixedStruct` – statically allocates a no-split ring buffer for fixed-size structs, ideal for sensor pipelines or task-to-task messaging.
- More sketches can be added as additional helpers land; each example focuses on a single concern so you can copy only what you need.

## Roadmap
- Add more wrappers for frequently-used ESP-IDF components (NVS helpers, OTA utilities, Wi-Fi extras, etc.).
- Provide combined examples that show how different helpers can cooperate in a sketch.

## License
MIT License – see [LICENSE](LICENSE).
