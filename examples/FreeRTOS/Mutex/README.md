# Mutex Examples

[日本語はこちら](README.ja.md)

`EspHelper::Mutex` wraps `xSemaphoreCreateMutex` in an RAII class.

## API Reference
- `bool create()`
- `bool lock(TickType_t wait = portMAX_DELAY)` / `bool unlock()`
- `SemaphoreHandle_t raw() const`

## Example Overview
- `SimpleMutex/SimpleMutex.ino` – Two writer tasks update shared state while guarding access with a mutex.
- `TryLock/TryLock.ino` – Demonstrates `lock(0)` for non-blocking attempts so a task can skip work if the mutex is busy.
- `BlockingMutex/BlockingMutex.ino` – Producer/consumer tasks both call `lock(portMAX_DELAY)` to block until the critical section becomes free.
