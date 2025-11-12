# Event Examples

[日本語はこちら](README.ja.md)

`EspHelper::EventLoop` hides the boilerplate around `esp_event` so sketches can create default or dedicated loops, register handlers, and post events without touching the raw C APIs.

## API Reference
- `bool createDefault()` – ensures the global default loop exists (creates it if necessary) and stores its handle.
- `bool createCustom(const esp_event_loop_args_t &args)` – builds an independent loop with your queue size, stack, priority, and core selection.
- `void end()` – deletes a custom loop (or the default loop if this instance created it).
- `bool registerHandler(base, id, handler, arg = nullptr, instance = nullptr)` / `bool unregisterHandler(...)` – add or remove handlers via `esp_event_handler_instance_*` helpers.
- `bool post(base, id, data = nullptr, size = 0, ticks = portMAX_DELAY)` – push events to the associated loop.
- `esp_event_loop_handle_t raw() const` – access the underlying handle when you need advanced features.

Usage notes:
- The wrapper only tracks one loop handle at a time. Call `end()` before switching from the default loop to a custom one.
- When sending structs as event data, pass a pointer to the struct and its `sizeof()`; the esp_event queue copies the payload for you.
- Handlers run on the loop's task context. Keep callbacks short or offload heavy work to another task.

## Example overview
- `DefaultLoop/DefaultLoop.ino` – Registers handlers on the global loop and posts periodic ticks/messages straight from `loop()`.
- `CustomLoop/CustomLoop.ino` – Creates an isolated event loop pinned to the APP CPU and feeds it pseudo sensor samples.
