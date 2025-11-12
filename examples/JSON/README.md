# JSON Examples

[日本語はこちら](README.ja.md)

This folder groups Arduino sketches that demonstrate the two JSON helpers shipped with EspHelper:

- **JsonGenerator (`EspHelperJsonGenerator.h`)** – wrapper around the ESP-IDF `espressif/json_generator` component; build JSON documents using preallocated buffers or stream directly to any `Print` target when you need deterministic memory use.
- **JsonParser (`EspHelperJsonParser.h`)** – consume JSON payloads with a light wrapper around ESP-IDF's `json_parser`, complete with token-buffer management and typed getters. Use this when you parse responses from web services, BLE characteristics, or configuration blobs.

## Choosing a helper
- Need to **produce** JSON (telemetry, config export, streaming logs)? Start with the JsonGenerator examples (`JsonGenerator/…`).
- Need to **consume** JSON (HTTP responses, remote config) or walk nested structures? Check the JsonParser examples (`JsonParser/…`).
- Projects frequently require both: generate status objects locally while parsing commands from the cloud. The helpers are header-only, so you can mix them freely in the same sketch.

## Example overview
- `JsonGenerator/AllFunctions` – exhaustive tour of every Generator method, covering reset patterns and streaming to `Serial`.
- `JsonGenerator/StaticJsonBuffer` – simplest fixed-buffer document builder.
- `JsonGenerator/StreamingToSerial` – streams JSON tokens to `Serial` with a tiny chunk buffer.
- `JsonParser/BasicParse` – traverses nested objects/arrays, retrieving typed values and printing them.

Place this repository under `~/Arduino/libraries/EspHelper`, open any of these sketches, and build for your ESP32 board running Arduino-ESP32 v2.0.0 or newer.
