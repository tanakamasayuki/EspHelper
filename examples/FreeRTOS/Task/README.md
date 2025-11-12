# Task Examples

[日本語はこちら](README.ja.md)

`EspHelper::Task` is a lightweight RAII wrapper around FreeRTOS tasks.

## API Reference
- `start(name, func, stackSize = 4096, priority = 1, core = tskNO_AFFINITY)`
- `stop()` / `running()`

### Core affinity hints
- `tskNO_AFFINITY` – let the scheduler run the task on any core.
- `PRO_CPU_NUM (0)` – pin to the PRO CPU.
- `APP_CPU_NUM (1)` – pin to the APP CPU.

## Example Overview
- `SimpleTask/SimpleTask.ino` – smallest possible task: toggles the built-in LED using a standalone function.
- `AdvancedParams/AdvancedParams.ino` – shows how to specify custom stack size, priority, and CPU core for both function-based and lambda-based tasks.
