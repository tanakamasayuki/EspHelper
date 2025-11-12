# Task サンプル

[English README](README.md)

`EspHelper::Task` は FreeRTOS のタスクをRAIIで扱えるようにするラッパーです。

## API リファレンス
- `start(name, func, stackSize = 4096, priority = 1, core = tskNO_AFFINITY)`
- `stop()` / `running()`

### コア指定メモ
- `tskNO_AFFINITY` – スケジューラに任せ、任意のコアで実行。
- `PRO_CPU_NUM (0)` – PRO CPU 固定。
- `APP_CPU_NUM (1)` – APP CPU 固定。

## 収録スケッチ
- `SimpleTask/SimpleTask.ino` – 最小構成のタスク例。LEDを点滅させるだけの関数をタスク化。
- `AdvancedParams/AdvancedParams.ino` – スタックサイズや優先度、コア番号を指定する方法を関数版・ラムダ版それぞれで紹介。
