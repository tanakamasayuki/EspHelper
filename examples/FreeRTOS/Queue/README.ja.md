# Queue サンプル

[English README](README.md)

`EspHelper::Queue<T>` は FreeRTOS のキューAPIをC++ラッパーで扱いやすくしたものです。

## APIリファレンス
- `Queue()` / `Queue(length)`
- `create(length)`
- `send(item, wait)` / `receive(out, wait)`
- `reset()`
- `raw()`

## 収録スケッチ
- `SimpleQueue/SimpleQueue.ino` – プロデューサー/コンシューマーのタスク間で整数を受け渡しする例。
