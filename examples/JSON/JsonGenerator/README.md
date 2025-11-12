# JsonGenerator Examples

[日本語はこちら](README.ja.md)

This folder contains standalone Arduino sketches that demonstrate how to use `EspHelper::JsonGenerator` with ESP32 boards. Each example focuses on a specific style of usage so you can copy only what you need.

## Key Concepts

- **Header-only helper** – `JsonGenerator` wraps the ESP-IDF `json_generator` component. Include `src/EspHelperJsonGenerator.h` in your sketch after installing this library in `~/Arduino/libraries/`.
- **Manual pairing of APIs** – `startObject()` / `endObject()` and `startArray()` / `endArray()` open or close anonymous containers such as the root object/array (`startArray(); …; endArray();` is all you need when the entire document is an array). To add a named member like `"sensor": { … }`, use `pushObject("sensor"); …; popObject();` instead—`push*` takes care of emitting the `"sensor":` prefix, so you do not call `setString("sensor", …)` yourself. Always close whatever you open so the nesting stays balanced.
- **Reset before reuse** – `JsonGenerator` is stateful. After emitting JSON with `finish()`, call one of the `reset(...)` overloads to clear the internal state and (optionally) switch buffers or flush callbacks. If you forget to reset, subsequent writes will append to the previous document and the comma tracking will be incorrect.
- **Buffer ownership vs streaming** – You can supply your own `char[]` buffer for maximum control, or construct the generator with a `Print` reference (`JsonGenerator(Print &out, size_t chunkSize)`) to stream data through the flush callback using a small internal buffer. Even in streaming mode, a chunk buffer is required because ESP-IDF’s generator always writes into a memory region before flushing.

## Detailed Usage

| Goal | Call sequence | JSON emitted |
| ---- | ------------- | ------------ |
| Root object | `startObject(); …; endObject();` | `{ … }` |
| Root array | `startArray(); …; endArray();` | `[ … ]` |
| Named object | `pushObject("cfg"); …; popObject();` | `"cfg":{ … }` |
| Named array | `pushArray("pins"); …; popArray();` | `"pins":[ … ]` |
| Object value | `setString("tag","esp32")` | `"tag":"esp32"` |
| Array value | `arrayAddInt(42)` (after `startArray()`/`pushArray()`) | `42` |
| Null value | `setNull("error")` or `arrayAddNull()` | `"error":null` or `null` |

1. **Initialize** – Construct with a user buffer (`char buf[256]; JsonGenerator json(buf);`) or a `Print` (`JsonGenerator json(Serial, 128);`).
2. **Build** – Combine the start/end/push/pop helpers to shape the JSON. Call the appropriate `set*` or `arrayAdd*` for each value.
3. **Finish** – `finish()` flushes outstanding data, terminates with `'\0'`, and returns the total bytes (including the null terminator). After `finish()` you can read `c_str()` or rely on the flush callback output.
4. **Reset** – Before the next document call `reset()` (reuse same buffer), `reset(newBuffer, size)`, or `reset(flushCb, priv)` to change the backing buffer or flush behavior.

### Example Snippets

```cpp
// Root object with named members
json.reset();
json.startObject();
json.setString("device", "ESP32");
json.pushArray("pins");
json.arrayAddInt(2);
json.arrayAddInt(4);
json.popArray();
json.endObject();
json.finish();  // -> {"device":"ESP32","pins":[2,4]}
```

```cpp
// Root array streaming to Serial
EspHelper::JsonGenerator streamJson(Serial, 96);
streamJson.startArray();
streamJson.pushObject("meta");
streamJson.setInt("cycle", 1);
streamJson.popObject();
streamJson.arrayAddBool(true);
streamJson.endArray();
streamJson.finish();  // Serial prints: [{"meta":{"cycle":1}},true]
```

## Example Overview

- `AllFunctions/AllFunctions.ino` – Exercises every public method: unnamed/named containers, object/array setters, `reset` overloads, flush callbacks, `raw()` access, and Print-based streaming.
- `StaticJsonBuffer/StaticJsonBuffer.ino` – Preallocates a stack buffer and rebuilds the JSON document on every loop iteration, printing the result via `Serial`.
- `StreamingToSerial/StreamingToSerial.ino` – Streams JSON directly to `Serial` with a small internal buffer so RAM usage stays minimal.

Each sketch starts with `Serial.begin(115200);` and runs out of the box on ESP32 Arduino core v2.0.0 or later. Feel free to duplicate and trim one of these sketches as a baseline for your own project.
