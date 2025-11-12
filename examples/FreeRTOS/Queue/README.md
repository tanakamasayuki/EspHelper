# Queue Examples

[日本語はこちら](README.ja.md)

`EspHelper::Queue<T>` wraps FreeRTOS queues with a simple C++ interface.

## API Reference
- `Queue()` / `explicit Queue(UBaseType_t length)`
- `bool create(UBaseType_t length)`
- `bool send(const T &item, TickType_t wait = portMAX_DELAY)`
- `bool receive(T &out, TickType_t wait = portMAX_DELAY)`
- `bool reset()`
- `QueueHandle_t raw() const`

## Example Overview
- `SimpleQueue/SimpleQueue.ino` – producer/consumer demo passing integers between tasks.
