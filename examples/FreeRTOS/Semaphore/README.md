# Semaphore Examples

`EspHelper::BinarySemaphore` and `EspHelper::CountingSemaphore` simplify the ESP-IDF binary/counting semaphore APIs with RAII semantics.

## API Reference
### BinarySemaphore
- `bool create()`
- `bool give()` / `bool take(TickType_t ticks = portMAX_DELAY)`
- `SemaphoreHandle_t raw() const`

### CountingSemaphore
- `bool create(UBaseType_t maxCount, UBaseType_t initialCount)`
- `bool give()` / `bool take(TickType_t ticks = portMAX_DELAY)`
- `SemaphoreHandle_t raw() const`

## Example Overview
- `Binary/Binary.ino` – two tasks sharing a binary semaphore to serialize access to `Serial` output.
- `Counting/Counting.ino` – counting semaphore limiting how many worker tasks can hold a slot simultaneously.
- `IsrSignal/IsrSignal.ino` – binary semaphore released from a timer ISR to wake a task (shows how to call `xSemaphoreGiveFromISR` via `raw()`).
