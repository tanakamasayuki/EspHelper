# JSON Examples

[日本語はこちら](README.ja.md)

This folder groups Arduino-friendly helpers that cover JSON-style workflows (even if the output isn't strict JSON):

- **JsonGenerator (`EspHelperJsonGenerator.h`)** – wrapper around the ESP-IDF `espressif/json_generator` component; build JSON documents using preallocated buffers or stream directly to any `Print` target when you need deterministic memory use. ([Docs](JsonGenerator/README.md))
- **JsonParser (`EspHelperJsonParser.h`)** – consume JSON payloads with a light wrapper around the ESP-IDF `espressif/json_parser` component, complete with token-buffer management and typed getters. Use this when you parse responses from web services, BLE characteristics, or configuration blobs. ([Docs](JsonParser/README.md))
- **CJson (`EspHelperCJson.h`)** – RAII helper around ESP-IDF's `cJSON` implementation for advanced manipulation, pretty-printing, or when you need the full cJSON feature-set without manual memory handling. ([Docs](CJson/README.md))
- **Cbor (`EspHelperCbor.h`)** – Lightweight wrapper for `espressif/cbor` (TinyCBOR). CBOR isn't JSON, but the API mirrors JSON-style builders/readers so you can emit compact binary payloads while writing Arduino code that feels like JSON manipulation. ([Docs](Cbor/README.md))

## Choosing a helper
- Need to **produce** JSON (telemetry, config export, streaming logs)? Start with the JsonGenerator examples (`JsonGenerator/…`).
- Need to **consume** JSON (HTTP responses, remote config) or walk nested structures? Check the JsonParser examples (`JsonParser/…`).
- Need full **cJSON** flexibility (deep copies, arbitrary insertion, pretty-printing)? Explore the CJson examples (`CJson/…`).
- Need compact, binary **CBOR** payloads but still want a JSON-like authoring flow? See the Cbor examples (`Cbor/…`).
- Projects frequently require both: generate status objects locally while parsing commands from the cloud. The helpers are header-only, so you can mix them freely in the same sketch.

## Example overview
- `JsonGenerator/AllFunctions` – exhaustive tour of every Generator method, covering reset patterns and streaming to `Serial`.
- `JsonGenerator/StaticJsonBuffer` – simplest fixed-buffer document builder.
- `JsonGenerator/StreamingToSerial` – streams JSON tokens to `Serial` with a tiny chunk buffer.
- `JsonParser/BasicParse` – traverses nested objects/arrays, retrieving typed values and printing them.
- `CJson/BuildAndParse` – builds a complex object with cJSON, prints it (compact & pretty), then parses it back to read fields.
- `Cbor/EncodeStatus` – constructs a CBOR map from JSON-like key/value helpers and prints the binary blob.
- `Cbor/DecodeStatus` – decodes a CBOR payload and pulls fields back out via `CborReader`.

Place this repository under `~/Arduino/libraries/EspHelper`, open any of these sketches, and build for your ESP32 board running Arduino-ESP32 v2.0.0 or newer.
