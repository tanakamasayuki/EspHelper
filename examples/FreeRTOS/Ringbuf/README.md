# Ringbuf Examples

[日本語はこちら](README.ja.md)

`EspHelper::Ringbuffer` is an RAII wrapper around the ESP-IDF `ringbuf` component with Arduino-friendly helpers.

## API Reference
- **Construction**: dynamic (`Ringbuffer(bytes, type)`), no-split factory (`Ringbuffer::NoSplit(itemSize, itemCount)`), static (`Ringbuffer(storage, bytes, StaticRingbuffer_t&)`), or adopt an existing `RingbufHandle_t`.
- **Send/Receive**: `send`, `sendFromISR`, `receive`, `receiveFromISR`. Each `receive` call returns a `RingbufferItem` that automatically calls `vRingbufferReturnItem()` when destroyed (call `release()` to keep ownership).
- **Other helpers**: `reset()` (dynamic buffers), `adopt()`.

## Example Overview
- `ByteBuffer/ByteBuffer.ino` – pushes formatted strings into a byte buffer and immediately reads them back over `Serial`.
- `FixedStruct/FixedStruct.ino` – uses a statically allocated no-split buffer to pass fixed-size sensor packets between producer and consumer code.
