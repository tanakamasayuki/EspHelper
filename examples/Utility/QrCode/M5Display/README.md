# M5Display

> 日本語版: [README.ja.md](README.ja.md)

Render generated QR modules on an M5 display.

## Prepare and run

1. Check the [example guide](../../../../docs/GUIDE_EXAMPLES.md) for setup and hardware. Use the root README for supported boards and dependencies.
2. Open [M5Display.ino](M5Display.ino) and select the actual board/port. Prepare the dependencies used by these includes:

   `<M5Unified.h>`, `<EspHelperQrCode.h>`

3. After upload, observe the display or other output used by this example. If using Serial, match its initialization in the source.

## Follow the sketch

These APIs are listed in their first source order. Registering a callback does not execute its body at that point.

1. `qr.generate(...)` — Check generation success before reading symbol size or module data.

## API usage and precautions

Include only the wrappers and external hardware libraries used by the selected example. Configure devices before starting tasks and check create/begin/start results when adapting the minimum code. The FreeRTOS wrappers use TickType_t waits, not the millisecond convention of ESP32SyncKit: use `pdMS_TO_TICKS()` when converting a desired duration.

A false/zero result can mean timeout, no room or no data; inspect the relevant API before consuming output. Queue items are copied by value, stream buffers retain bytes without message boundaries, and message buffers retain whole messages. RingbufferItem returns borrowed storage through RAII; copy data before the item leaves scope if it must outlive it.

Network and event callbacks can run outside loop. Keep their work short and retain application-owned copies of data needed later.

## Verify and troubleshoot

Render generated QR modules on an M5 display and verify the result on its output. First use the supplied input, then change one configuration or data source at a time.

| Symptom | First check |
|---|---|
| No output | Board/dependencies, initialization results, output destination and Serial baud |
| Starts but stops making progress | Wait conditions, buffer space, peer/input readiness and service calls |
| Unexpected values | Lengths/units, format, data lifetime, shared state and partial results |

See the [guide](../../../../docs/GUIDE_EXAMPLES.md) for shared principles and the [example index](../../../README.md) for the next sketch.
