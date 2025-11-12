# CBOR Examples

[日本語はこちら](README.ja.md)

`EspHelperCbor.h` exposes a tiny wrapper around the ESP-IDF `espressif/cbor` (TinyCBOR) component so you can build binary payloads in a JSON-like style and parse them back without leaving Arduino.

## API Reference
- `CborWriter`
  - `begin(buffer, length)` – initialise the encoder with a caller-provided buffer.
  - `startMap(length = CborIndefiniteLength)` / `startArray(length)` / `endContainer()` – nest maps & arrays similar to JSON objects/arrays.
  - `add(value)` overloads for strings, integers, unsigned integers, booleans, `null`, and byte strings.
  - `addKeyValue(key, value)` helpers to add JSON-style key/value pairs quickly.
  - `finish()` / `bytesWritten()` – finalise and retrieve the produced length.
- `CborReader`
  - `begin(buffer, length)` – parse a CBOR payload.
  - `isMap()` – quick type check for top-level objects.
  - `getString(key, out)`, `getInt(key, out)`, `getBool(key, out)` – convenience accessors for root-level maps.

## Example overview
- `EncodeStatus/EncodeStatus.ino` – builds a status object (device, firmware, uptime) and prints the CBOR bytes in hex.
- `DecodeStatus/DecodeStatus.ino` – encodes a sample map, parses it back, and prints the extracted fields.
