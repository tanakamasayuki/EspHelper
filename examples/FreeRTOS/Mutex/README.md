# Mutex Examples

[日本語はこちら](README.ja.md)

`EspHelper::Mutex` wraps `xSemaphoreCreateMutex` in an RAII class.

## API Reference
- `bool create()`
- `bool lock(TickType_t wait = portMAX_DELAY)` / `bool unlock()`
- `SemaphoreHandle_t raw() const`

## Example Overview
- `SimpleMutex/SimpleMutex.ino` – Two writer tasks update shared state while guarding access with a mutex.
