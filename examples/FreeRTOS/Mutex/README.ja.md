# Mutex サンプル

[English README](README.md)

`EspHelper::Mutex` は `xSemaphoreCreateMutex` をRAIIで扱えるシンプルなラッパーです。

## APIリファレンス
- `create()`
- `lock(wait)` / `unlock()`
- `raw()`

## 収録スケッチ
- `SimpleMutex/SimpleMutex.ino` – 2つのタスクで共有データを書き換える際にミューテックスで排他制御を行う例。
- `TryLock/TryLock.ino` – `lock(0)`で非ブロッキングに試行し、取れなければ別処理へ戻る例。
- `BlockingMutex/BlockingMutex.ino` – `portMAX_DELAY`で取得を待ち、順番に共有データへアクセスする例。
