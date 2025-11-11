# EspHelper

[日本語はこちら](README.ja.md)

EspHelper is a collection of single-header Arduino helpers that expose selected ESP-IDF components with lightweight, idiomatic APIs. Use it when you want to keep the productivity of the Arduino core on ESP32 boards but still reach for ESP-IDF features such as the `espressif/json_generator` component.

## Features
- Header-only wrappers: drop the `.h` file you need into a sketch without pulling extra dependencies.
- Arduino-friendly defaults: utilities work with `Print`, `String`, and familiar Arduino idioms.
- Works alongside the ESP-IDF components that are already bundled in current Arduino-ESP32 releases.
- Examples kept minimal so you can copy/paste straight into an existing project.

## Requirements
- Arduino core for ESP32 (v2.0.0 or newer) or a PlatformIO environment targeting `esp32`.
- A C++17 capable toolchain (the default for modern Arduino-ESP32).

## Installation
### Arduino IDE / Arduino CLI
1. Clone or download this repository into your Arduino `libraries` directory so that the folder becomes `~/Arduino/libraries/EspHelper`.
2. Include the header you need from `src/` in your sketch. The ESP-IDF components leveraged by EspHelper are already part of recent Arduino ESP32 cores, so no additional setup is necessary.

## Examples
- `examples/JsonGenerator/AllFunctions` – exercises every `JsonGenerator` method (including reset variations and streaming) in one sketch.
- `examples/JsonGenerator/StaticJsonBuffer` – builds a JSON document into a fixed stack buffer and prints it to `Serial`.
- `examples/JsonGenerator/StreamingToSerial` – streams JSON tokens directly to `Serial` via the `Print`-based constructor for minimal RAM usage.
- More sketches can be added as additional helpers land; each example focuses on a single concern so you can copy only what you need.

## Roadmap
- Add more wrappers for frequently-used ESP-IDF components (NVS helpers, OTA utilities, Wi-Fi extras, etc.).
- Provide combined examples that show how different helpers can cooperate in a sketch.

## License
MIT License – see [LICENSE](LICENSE).
