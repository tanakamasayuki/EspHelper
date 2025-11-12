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
- `SimpleQueue/SimpleQueue.ino` – Minimal producer/consumer loop with default (non-blocking send, 1s receive timeout).
- `PollingQueue/PollingQueue.ino` – Demonstrates non-blocking polling (`wait = 0`) so the consumer can perform other work between checks.
- `TimeoutQueue/TimeoutQueue.ino` – Uses a finite wait (750 ms) to show how to react when the queue stays empty for too long.
- `BlockingQueue/BlockingQueue.ino` – Both producer and consumer use `portMAX_DELAY`, blocking indefinitely until space/data becomes available.
