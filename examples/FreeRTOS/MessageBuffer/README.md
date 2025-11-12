# MessageBuffer Examples

[日本語はこちら](README.ja.md)

`EspHelper::MessageBuffer` brings the FreeRTOS message buffer API to Arduino sketches, preserving per-message boundaries so you can pass variable-length packets safely.

## API Reference
- `bool create(size_t capacity)` / `bool createStatic(size_t capacity, uint8_t *storage, StaticMessageBuffer_t *control)`
- `size_t send(const void *data, size_t length, TickType_t wait = portMAX_DELAY)` / `size_t sendFromISR(...)`
- `size_t receive(void *data, size_t maxLength, TickType_t wait = portMAX_DELAY)` / `size_t receiveFromISR(...)`
- `size_t nextMessageSize() const` / `size_t spaceAvailable() const`
- `bool reset()` / `MessageBufferHandle_t raw() const`

## Usage notes
- Each call to `send` enqueues one complete message. A single `receive` call always returns exactly one message, making it ideal for framed protocols.
- Keep a small safety margin between the largest message size and the total capacity (FreeRTOS stores a few bytes of metadata per message).
- Use `nextMessageSize()` to peek at the pending payload size before allocating a buffer.

## Example overview
- `SimpleMessageBuffer/SimpleMessageBuffer.ino` – Sender/receiver tasks exchange null-terminated strings while printing queue depth information.
