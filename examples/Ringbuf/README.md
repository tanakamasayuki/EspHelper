# Ringbuf Examples

[日本語はこちら](README.ja.md)

These sketches demonstrate how to push data through the ESP-IDF `ringbuf` component using the `EspHelper::Ringbuffer` wrapper.

## Key Notes

- **Buffer type matters** – Choose between `RINGBUF_TYPE_NOSPLIT`, `RINGBUF_TYPE_ALLOWSPLIT`, or `RINGBUF_TYPE_BYTEBUF` when constructing `EspHelper::Ringbuffer`. Byte buffers act like FIFO byte streams, while the other types preserve item boundaries and 32-bit alignment.
- **Always return received items** – `Ringbuffer::receive()` hands out an `EspHelper::RingbufferItem` that automatically calls `vRingbufferReturnItem()` when it goes out of scope. If you move the item elsewhere, make sure it is destroyed or call `release()` manually after processing the data.
- **Timing and blocking** – `send()`/`receive()` take an optional `TickType_t` timeout. Use `0` for non-blocking polls, `portMAX_DELAY` to wait forever, or `pdMS_TO_TICKS(ms)` for millisecond granularity.
- **ISR helpers** – `sendFromISR()` and `receiveFromISR()` keep the underlying FreeRTOS semantics. The wrapper does not manage higher priority wake-ups automatically, so pass a `BaseType_t` flag if you need to perform a context switch.

## Example Overview

- `ByteBuffer/ByteBuffer.ino` – Creates a byte-style ring buffer, pushes formatted strings, and immediately pops data for printing.
- `FixedStruct/FixedStruct.ino` – Demonstrates a statically-allocated no-split buffer for fixed-size structs, mimicking a sensor producer/consumer pipeline.

Place this repository under `~/Arduino/libraries`, open any sketch in the Arduino IDE, and build for an ESP32 board running Arduino-ESP32 v2.0.0 or newer.
