# StreamBuffer Examples

[日本語はこちら](README.ja.md)

`EspHelper::StreamBuffer` wraps the FreeRTOS stream buffer API so you can push arbitrary byte streams between tasks (or ISRs) using Arduino-style code.

## API Reference
- `bool create(size_t capacity, size_t triggerLevel = 1)`
- `bool createStatic(capacity, uint8_t *storage, StaticStreamBuffer_t *control, size_t triggerLevel = 1)`
- `size_t send(const void *data, size_t length, TickType_t wait = portMAX_DELAY)` / `size_t sendFromISR(...)`
- `size_t receive(void *data, size_t maxLength, TickType_t wait = portMAX_DELAY)` / `size_t receiveFromISR(...)`
- `size_t bytesAvailable() const` / `size_t spacesAvailable() const`
- `bool reset()` / `StreamBufferHandle_t raw() const`

## Usage notes
- Stream buffers behave like byte pipes. They do not preserve message boundaries—use a message buffer if you need framing.
- `triggerLevel` defines how many bytes must accumulate before a reader task is woken. Keep it small (1) for low-latency streams or bump it to reduce context switches.
- Static creation is handy when you want to keep the buffer in PSRAM/DRAM that you manage yourself.

## Example overview
- `SimpleStreamBuffer/SimpleStreamBuffer.ino` – Producer/consumer tasks share telemetry chunks and print how much data is buffered.
