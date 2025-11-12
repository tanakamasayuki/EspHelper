# FreeRTOS Examples

[日本語はこちら](README.ja.md)

These sketches cover Arduino-friendly wrappers for ESP-IDF subsystems that live under FreeRTOS, starting with the ring buffer helper.

- **Ringbuffer (`EspHelperRingbuf.h`)** – RAII wrapper over the ESP-IDF `esp_ringbuf` component that simplifies creation (dynamic or static), zero-copy send/receive patterns, and ISR-safe operations. Choose between byte-buffer and item-buffer modes based on your data layout.

## When to use the ring buffer
- You need a **byte stream** or mixed-size packets between tasks → use `RINGBUF_TYPE_BYTEBUF` (see `Ringbuf/ByteBuffer`).
- You pass **fixed-size structs** or want deterministic ownership of large items → use a no-split buffer with static storage (`Ringbuf/FixedStruct`).
- You require zero-copy semantics or plan to interact with ISR producers/consumers; the helper exposes `sendFromISR()` and `receiveFromISR()` to keep FreeRTOS rules intact.

More FreeRTOS-centric helpers can live here later (queues, stream buffers, etc.).
