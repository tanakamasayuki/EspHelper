# FreeRTOS サンプル

[English README](README.md)

本ディレクトリではFreeRTOS系のESP-IDF機能をArduinoから扱いやすくするヘルパーを紹介します。現時点ではリングバッファ用ラッパーを収録しています。

- **Ringbuffer (`EspHelperRingbuf.h`)** – ESP-IDFコンポーネント`esp_ringbuf`をRAII化し、動的／静的メモリの生成、ゼロコピー送受信、ISR対応APIをまとめて提供します。データ形態に応じてBYTEBUF・NoSplit・AllowSplitを選択可能です。

## 使い分けのヒント
- タスク間で**バイトストリームや可変長パケット**を流したい → BYTEBUFモード（`Ringbuf/ByteBuffer`）。
- **固定サイズ構造体**を複数タスクで共有したい、静的メモリで完結させたい → No-Split＋静的領域（`Ringbuf/FixedStruct`）。
- ISRとタスク間でデータをやり取りしたい場合も、提供している`sendFromISR()`/`receiveFromISR()`を利用できます。

今後、キュー／StreamBuffer等のラッパーも追加された場合はこのカテゴリに配置されます。
