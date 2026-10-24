# EspHelper — Example workflow

> 日本語版: [GUIDE_EXAMPLES.ja.md](GUIDE_EXAMPLES.ja.md)

Use focused wrappers for ESP-IDF components.

Check installation and platform requirements in the [library README](../README.md), then choose a sketch from the [example index](../examples/README.md). Version/support tables and internal capacity defaults stay in their original reference rather than being duplicated here.

## From setup to a verified result

1. Choose the smallest relevant sketch and check its board, hardware, dependencies and bundled files.
2. Match pins, peers and input files to your actual setup. Each README identifies important placeholders.
3. Open the .ino, select board/port and upload. Match Serial baud where used.
4. Locate the last completed stage: initialization, input, processing or output. Compilation does not test hardware I/O.
5. Reproduce the supplied example before changing one setting at a time.

## API and data handling

Include only the wrappers and external hardware libraries used by the selected example. Configure devices before starting tasks and check create/begin/start results when adapting the minimum code. The FreeRTOS wrappers use TickType_t waits, not the millisecond convention of ESP32SyncKit: use `pdMS_TO_TICKS()` when converting a desired duration.

A false/zero result can mean timeout, no room or no data; inspect the relevant API before consuming output. Queue items are copied by value, stream buffers retain bytes without message boundaries, and message buffers retain whole messages. RingbufferItem returns borrowed storage through RAII; copy data before the item leaves scope if it must outlive it.

Network and event callbacks can run outside loop. Keep their work short and retain application-owned copies of data needed later.

## When adapting it

- Distinguish bool status, processed counts and handles; do not use stale output after failure.
- Registered callbacks run later from their documented context. Decide synchronization and retained-data lifetime.
- Keep bytes, samples, frames and pixels distinct; capacity is different from valid length.
- Retain views/pointers/buffers for the required period. Copying a pointer does not copy its payload.
- Add application-specific failure handling, retry and cleanup that a minimal example may omit.

## Read the individual README

Use Prepare and run for hardware and steps, Follow the sketch for the actual APIs and precautions for feature-specific constraints. If output is missing, check initialization first, continued service calls next and input/peer readiness after that.
