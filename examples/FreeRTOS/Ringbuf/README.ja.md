# Ringbuf サンプル

[English README](README.md)

`EspHelper::Ringbuffer` は ESP-IDF の `ringbuf` をRAII化したラッパーです。Arduinoスケッチから`send`/`receive`を扱いやすくします。

## APIリファレンス
- **生成方法**: 動的 (`Ringbuffer(bytes, type)`)、`Ringbuffer::NoSplit(itemSize, itemCount)`、静的 (`Ringbuffer(storage, bytes, StaticRingbuffer_t&)`)、既存ハンドルの `adopt()`。
- **送受信**: `send` / `sendFromISR` / `receive` / `receiveFromISR`。`receive` は `RingbufferItem` を返し、破棄時に `vRingbufferReturnItem()` が自動呼び出しされます（`release()`で手動管理も可能）。
- **その他**: `reset()`（動的バッファのみ）、`adopt()`。

## 収録スケッチ
- `ByteBuffer/ByteBuffer.ino` – バイトバッファに文字列を流し込み、そのまま`Serial`へ再出力。
- `FixedStruct/FixedStruct.ino` – 静的メモリ＋No-Splitリングバッファで固定サイズ構造体をやり取りする例。
