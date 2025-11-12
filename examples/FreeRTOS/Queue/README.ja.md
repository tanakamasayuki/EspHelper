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
- `SimpleQueue/SimpleQueue.ino` – もっとも基本的なプロデューサー/コンシューマー例（送信は即時、受信は1秒待ち）。
- `PollingQueue/PollingQueue.ino` – `wait = 0`でポーリングし、キューが空なら別処理を挟むパターン。
- `TimeoutQueue/TimeoutQueue.ino` – 750msの有限待ちを設定し、タイムアウト時のリカバリーをログ出力。
- `BlockingQueue/BlockingQueue.ino` – `portMAX_DELAY`で無限待ちを行い、バッファ不足/空待ちをブロッキングで吸収する例。
