# FreeRTOS サンプル

[English README](README.md)

本ディレクトリではFreeRTOS系のESP-IDF機能をArduinoから扱いやすくするヘルパーを紹介します。

- **Ringbuffer (`EspHelperRingbuf.h`)** – ESP-IDFコンポーネント`esp_ringbuf`をRAII化し、動的／静的メモリの生成、ゼロコピー送受信、ISR対応APIをまとめて提供します。データ形態に応じてBYTEBUF・NoSplit・AllowSplitを選択可能です。
- **Task (`EspHelperTask.h`)** – `xTaskCreatePinnedToCore` をラップし、ラムダ関数でFreeRTOSタスクを起動/停止できる軽量ヘルパー。
- **Queue (`EspHelperQueue.h`)** – FreeRTOSキューをテンプレートで扱えるラッパー。
- **Semaphore (`EspHelperSemaphore.h`)** – バイナリ/カウンティングセマフォをRAIIで扱えるラッパー。
- **Mutex (`EspHelperMutex.h`)** – ミューテックス（`xSemaphoreCreateMutex`）をシンプルなAPIで提供。

## 使い分けのヒント
- タスク間で**バイトストリームや可変長パケット**を流したい → BYTEBUFモード（`Ringbuf/ByteBuffer`）。
- **固定サイズ構造体**を複数タスクで共有したい、静的メモリで完結させたい → No-Split＋静的領域（`Ringbuf/FixedStruct`）。
- ISRとタスク間でデータをやり取りしたい場合も、提供している`sendFromISR()`/`receiveFromISR()`を利用できます。

## 収録サンプル
- `Ringbuf/ByteBuffer` – BYTEBUFリングバッファへ文字列を流し、直ちに読み戻す例。
- `Ringbuf/FixedStruct` – No-Splitかつ静的メモリで固定サイズ構造体をやり取りする例。
- `Task/SimpleTask` – FreeRTOSタスクを起動してLEDを点滅させる最小例。
- `Task/AdvancedParams` – スタックサイズ・優先度・コア割り当て（`tskNO_AFFINITY`/`PRO_CPU_NUM`/`APP_CPU_NUM`）の指定方法を示す例。
- `Queue/SimpleQueue` – プロデューサー/コンシューマー間で整数をやり取りする例。
- `Semaphore/Binary` – バイナリセマフォでタスク同士の排他制御を行う例。
- `Mutex/SimpleMutex` – ミューテックスで共有変数を保護する例。
