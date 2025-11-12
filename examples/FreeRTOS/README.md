# FreeRTOS Examples

[日本語はこちら](README.ja.md)

These sketches cover Arduino-friendly wrappers for ESP-IDF subsystems that live under FreeRTOS.

- **Task (`EspHelperTask.h`)** – Lightweight facade around `xTaskCreatePinnedToCore` that lets you start/stop lambdas as FreeRTOS tasks with automatic cleanup. ([Docs](Task/README.md))
- **Queue (`EspHelperQueue.h`)** – Template wrapper over FreeRTOS queues with `send`/`receive` helpers. ([Docs](Queue/README.md))
- **Semaphore (`EspHelperSemaphore.h`)** – Binary and counting semaphores with convenient RAII handling. ([Docs](Semaphore/README.md))
- **Mutex (`EspHelperMutex.h`)** – Minimal wrapper over `xSemaphoreCreateMutex`. ([Docs](Mutex/README.md))
- **MessageBuffer (`EspHelperMessageBuffer.h`)** – Wrapper for FreeRTOS message buffers that preserves per-message framing for variable-length packets. ([Docs](MessageBuffer/README.md))
- **StreamBuffer (`EspHelperStreamBuffer.h`)** – Helper for FreeRTOS stream buffers when you need a byte-oriented pipe with optional ISR endpoints. ([Docs](StreamBuffer/README.md))
- **Ringbuffer (`EspHelperRingbuf.h`)** – RAII wrapper over the ESP-IDF `esp_ringbuf` component that simplifies creation (dynamic or static), zero-copy send/receive patterns, and ISR-safe operations. Choose between byte-buffer and item-buffer modes based on your data layout. ([Docs](Ringbuf/README.md))

## Buffer helper cheat sheet
- Reach for **StreamBuffer** when you just need a byte-oriented pipe between tasks/ISRs. Tune the `triggerLevel` to balance latency vs. wakeups.
- Choose **MessageBuffer** when each payload must stay intact (variable-length packets, config blobs, etc.). Leave extra headroom because FreeRTOS stores metadata per message.
- Stick with **Ringbuffer** for zero-copy transfers, fixed-size structs, or when you need the ESP-IDF split/no-split modes (see `Ringbuf/ByteBuffer` and `Ringbuf/FixedStruct`).

- `Task/SimpleTask` – Launches a FreeRTOS task to blink the onboard LED while leaving `loop()` idle.
- `Task/AdvancedParams` – Shows how to set custom stack size, priority, and core affinity (`tskNO_AFFINITY`, `PRO_CPU_NUM`, `APP_CPU_NUM`).
- `Queue/SimpleQueue` – Producer/consumer example passing integers between tasks.
- `Queue/PollingQueue` – Shows how to poll (`wait = 0`) while doing other work between reads.
- `Queue/TimeoutQueue` – Demonstrates finite waits and handling timeout events.
- `Queue/BlockingQueue` – Uses `portMAX_DELAY` on both sides to block until space/data is available.
- `Semaphore/Binary` – Two tasks alternating access via a binary semaphore.
- `Semaphore/Counting` – Uses a counting semaphore to cap the number of concurrent workers.
- `Semaphore/IsrSignal` – Timer ISR gives a semaphore to wake a task safely.
- `Mutex/SimpleMutex` – Demonstrates guarding shared state with a mutex.
- `Mutex/TryLock` – Shows how to use `lock(0)` to attempt a non-blocking critical section.
- `Mutex/BlockingMutex` – Both producer/consumer block with `portMAX_DELAY` to serialize access to shared data.
- `MessageBuffer/SimpleMessageBuffer` – Shows variable-length messages hopping between producer/consumer tasks.
- `StreamBuffer/SimpleStreamBuffer` – Demonstrates a telemetry-style byte pipe between two tasks.
- `Ringbuf/ByteBuffer` – Creates a byte-style ring buffer, pushes formatted strings, and immediately pops data for printing.
- `Ringbuf/FixedStruct` – Demonstrates a statically-allocated no-split buffer for fixed-size structs, mimicking a sensor producer/consumer pipeline.
