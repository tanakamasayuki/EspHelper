# FreeRTOS Examples

[日本語はこちら](README.ja.md)

These sketches cover Arduino-friendly wrappers for ESP-IDF subsystems that live under FreeRTOS.

- **Ringbuffer (`EspHelperRingbuf.h`)** – RAII wrapper over the ESP-IDF `esp_ringbuf` component that simplifies creation (dynamic or static), zero-copy send/receive patterns, and ISR-safe operations. Choose between byte-buffer and item-buffer modes based on your data layout.
- **Task (`EspHelperTask.h`)** – Lightweight facade around `xTaskCreatePinnedToCore` that lets you start/stop lambdas as FreeRTOS tasks with automatic cleanup.
- **Queue (`EspHelperQueue.h`)** – Template wrapper over FreeRTOS queues with `send`/`receive` helpers.
- **Semaphore (`EspHelperSemaphore.h`)** – Binary and counting semaphores with convenient RAII handling.
- **Mutex (`EspHelperMutex.h`)** – Minimal wrapper over `xSemaphoreCreateMutex`.

## When to use the ring buffer
- You need a **byte stream** or mixed-size packets between tasks → use `RINGBUF_TYPE_BYTEBUF` (see `Ringbuf/ByteBuffer`).
- You pass **fixed-size structs** or want deterministic ownership of large items → use a no-split buffer with static storage (`Ringbuf/FixedStruct`).
- You require zero-copy semantics or plan to interact with ISR producers/consumers; the helper exposes `sendFromISR()` and `receiveFromISR()` to keep FreeRTOS rules intact.

## Example overview
- `Ringbuf/ByteBuffer` – Creates a byte-style ring buffer, pushes formatted strings, and immediately pops data for printing.
- `Ringbuf/FixedStruct` – Demonstrates a statically-allocated no-split buffer for fixed-size structs, mimicking a sensor producer/consumer pipeline.
- `Task/SimpleTask` – Launches a FreeRTOS task to blink the onboard LED while leaving `loop()` idle.
- `Task/AdvancedParams` – Shows how to set custom stack size, priority, and core affinity (`tskNO_AFFINITY`, `PRO_CPU_NUM`, `APP_CPU_NUM`).
- `Queue/SimpleQueue` – Producer/consumer example passing integers between tasks.
- `Semaphore/Binary` – Two tasks alternating access via a binary semaphore.
- `Mutex/SimpleMutex` – Demonstrates guarding shared state with a mutex.
