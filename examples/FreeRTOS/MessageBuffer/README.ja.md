# MessageBuffer サンプル

[English README](README.md)

`EspHelper::MessageBuffer` は FreeRTOS のメッセージバッファAPIをラップし、可変長のメッセージを枠ごと受け渡しできます。

## APIリファレンス
- `create(capacity)` / `createStatic(capacity, storage, control)`
- `send(data, length, wait)` / `sendFromISR(...)`
- `receive(data, maxLength, wait)` / `receiveFromISR(...)`
- `nextMessageSize()` / `spaceAvailable()`
- `reset()` / `raw()`

## 使いどころメモ
- `send` 1回がそのまま1メッセージになります。固定長でも可変長でも、受信側は `receive` 1回でちょうど1件を取り出せます。
- FreeRTOSは各メッセージにメタデータを数バイト追加するため、最大メッセージサイズより少し余裕のある容量を確保してください。
- 受信前に必要なバッファサイズを知りたい場合は `nextMessageSize()` を参照します。

## 収録スケッチ
- `SimpleMessageBuffer/SimpleMessageBuffer.ino` – Null終端文字列をタスク間でやりとりし、空き容量や次メッセージサイズをシリアル表示する例。
