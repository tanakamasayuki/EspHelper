# Mutex サンプル

[English README](README.md)

`EspHelper::Mutex` は `xSemaphoreCreateMutex` をRAIIで扱えるシンプルなラッパーです。

## APIリファレンス
- `create()`
- `lock(wait)` / `unlock()`
- `raw()`

## 収録スケッチ
- `SimpleMutex/SimpleMutex.ino` – 2つのタスクで共有データを書き換える際にミューテックスで排他制御を行う例。
