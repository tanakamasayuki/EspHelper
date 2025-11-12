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
- `Counting/Counting.ino` – カウンティングセマフォで同時実行数を制限し、空きが出るまで待つパターン。
- `IsrSignal/IsrSignal.ino` – タイマーISRで`xSemaphoreGiveFromISR`を呼び、タスクを起床させる例。
