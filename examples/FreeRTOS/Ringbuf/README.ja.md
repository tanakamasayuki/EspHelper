# Ringbuf サンプル

[English README](README.md)

ESP-IDFの`ringbuf`コンポーネントを`EspHelper::Ringbuffer`で扱う方法を紹介します。

## 使い方のポイント

- **バッファ種別を選ぶ** – `EspHelper::Ringbuffer`生成時に`RINGBUF_TYPE_NOSPLIT`/`ALLOWSPLIT`/`BYTEBUF`を指定します。BYTEBUFは単純なバイトストリームとして動作し、他のタイプはアイテム境界と32bitアラインメントを維持します。
- **受信したら必ず返却** – `receive()`が返す`EspHelper::RingbufferItem`はスコープから抜けると自動で`vRingbufferReturnItem()`を呼びます。ムーブした場合でも、最終的にデストラクタが走るか`release()`を明示的に呼んでバッファを空けてください。
- **待ち時間の指定** – `send()`/`receive()`はいずれも`TickType_t`の待ち時間を引数に取れます。`0`ならノンブロッキング、`portMAX_DELAY`で無限待ち、`pdMS_TO_TICKS(ms)`でミリ秒単位指定が可能です。
- **ISR用APIもカバー** – `sendFromISR()`/`receiveFromISR()`も公開しています。FreeRTOSの規約通り、必要なら`BaseType_t`フラグでコンテキストスイッチを要求してください。

## 収録スケッチ

- `ByteBuffer/ByteBuffer.ino` – BYTEBUFリングバッファへ文字列を流し込み、すぐ読み戻して`Serial`へ表示する最小例。
- `FixedStruct/FixedStruct.ino` – 静的メモリでNo-Splitリングバッファを作り、固定サイズ構造体（センサーデータ）を送受信する例。

このリポジトリを`~/Arduino/libraries`に配置し、Arduino-ESP32 v2.0.0以降を対象にスケッチを開いてビルドしてください。
