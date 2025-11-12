# StreamBuffer サンプル

[English README](README.md)

`EspHelper::StreamBuffer` は FreeRTOS のストリームバッファAPIをArduino風に扱えるラッパーです。タスク間やISRから任意のバイト列をパイプのように受け渡せます。

## APIリファレンス
- `create(capacity, triggerLevel = 1)`
- `createStatic(capacity, storage, control, triggerLevel = 1)`
- `send(data, length, wait)` / `sendFromISR(...)`
- `receive(data, maxLength, wait)` / `receiveFromISR(...)`
- `bytesAvailable()` / `spacesAvailable()`
- `reset()` / `raw()`

## 使いどころメモ
- ストリームバッファはメッセージ境界を保持しません。1件ずつ確実に切り分けたい場合は MessageBuffer を使ってください。
- `triggerLevel` は読者タスクを起こす閾値です。レイテンシを重視するなら 1、まとまった塊で処理したいなら大きめに設定します。
- `createStatic` で PSRAM/DRAM の任意領域を使えば、ヒープ断片化を避けられます。

## 収録スケッチ
- `SimpleStreamBuffer/SimpleStreamBuffer.ino` – タスク間でテレメトリ文字列を渡し、滞留バイト数をシリアルへ表示する例。
