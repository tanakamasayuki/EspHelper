# FreeRTOS サンプル

[English README](README.md)

本ディレクトリではFreeRTOS系のESP-IDF機能をArduinoから扱いやすくするヘルパーを紹介します。

- **Ringbuffer (`EspHelperRingbuf.h`)** – ESP-IDFコンポーネント`esp_ringbuf`をRAII化し、動的／静的メモリの生成、ゼロコピー送受信、ISR対応APIをまとめて提供します。データ形態に応じてBYTEBUF・NoSplit・AllowSplitを選択可能です。
- **Task (`EspHelperTask.h`)** – `xTaskCreatePinnedToCore` をラップし、ラムダ関数でFreeRTOSタスクを起動/停止できる軽量ヘルパー。
- **StreamBuffer (`EspHelperStreamBuffer.h`)** – FreeRTOSのストリームバッファを扱うラッパー。バイトストリームをタスク/ISR間でやり取りする用途に最適です。
- **MessageBuffer (`EspHelperMessageBuffer.h`)** – FreeRTOSメッセージバッファをラップし、可変長のメッセージをフレームごとに配送できます。
- **Queue (`EspHelperQueue.h`)** – FreeRTOSキューをテンプレートで扱えるラッパー。
- **Semaphore (`EspHelperSemaphore.h`)** – バイナリ/カウンティングセマフォをRAIIで扱えるラッパー。
- **Mutex (`EspHelperMutex.h`)** – ミューテックス（`xSemaphoreCreateMutex`）をシンプルなAPIで提供。

## 使い分けのヒント
- タスク/ISR間に**単方向のバイトストリーム**を作りたい → StreamBuffer（`StreamBuffer/SimpleStreamBuffer`）。
- **1件ごとのメッセージ**を安全に届けたい → MessageBuffer（`MessageBuffer/SimpleMessageBuffer`）。`nextMessageSize()`で受信前に長さを確認できます。
- **固定サイズ構造体**やゼロコピー受け渡し、複雑なバッファモードが必要 → Ringbuffer（`Ringbuf/*`）。
- 典型的な**FIFO**用途には Queue、排他制御には Semaphore / Mutex を選択してください。

## 収録サンプル
- `Ringbuf/ByteBuffer` – BYTEBUFリングバッファへ文字列を流し、直ちに読み戻す例。
- `Ringbuf/FixedStruct` – No-Splitかつ静的メモリで固定サイズ構造体をやり取りする例。
- `Task/SimpleTask` – FreeRTOSタスクを起動してLEDを点滅させる最小例。
- `Task/AdvancedParams` – スタックサイズ・優先度・コア割り当て（`tskNO_AFFINITY`/`PRO_CPU_NUM`/`APP_CPU_NUM`）の指定方法を示す例。
- `StreamBuffer/SimpleStreamBuffer` – ストリームバッファを介してテレメトリ文字列を送受信する例。
- `MessageBuffer/SimpleMessageBuffer` – メッセージバッファでNULL終端文字列を渡し、次のメッセージ長を確認する例。
- `Queue/SimpleQueue` – プロデューサー/コンシューマー間で整数をやり取りする例。
- `Semaphore/Binary` – バイナリセマフォでタスク同士の排他制御を行う例。
- `Mutex/SimpleMutex` – ミューテックスで共有変数を保護する例。
