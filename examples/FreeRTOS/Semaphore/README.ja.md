# Semaphore サンプル

`EspHelper::BinarySemaphore` と `EspHelper::CountingSemaphore` はESP-IDFのセマフォAPIをRAIIで扱いやすくするラッパーです。

## APIリファレンス
### BinarySemaphore
- `create()`
- `give()` / `take(ticks)`
- `raw()`

### CountingSemaphore
- `create(maxCount, initialCount)`
- `give()` / `take(ticks)`
- `raw()`

## 収録スケッチ
- `Binary/Binary.ino` – 2つのタスクでバイナリセマフォを共有し、シリアル出力をシリアライズします。
