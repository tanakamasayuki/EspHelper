# CBOR サンプル

[English README](README.md)

`EspHelperCbor.h` は ESP-IDF の `espressif/cbor` (TinyCBOR) コンポーネントをArduino風に扱うラッパーです。JSONに近い感覚でオブジェクト/配列を組み立てつつ、バイナリCBORとして送受信できます。

## APIリファレンス
- `CborWriter`
  - `begin(buffer, length)` – 呼び出し側が用意したバッファにエンコードします。
  - `startMap(length)` / `startArray(length)` / `endContainer()` – JSONのobject/arrayに相当するネストを管理。
  - `add(value)` 系 – 文字列、整数、真偽値、null、バイト列などを追加。
  - `addKeyValue(key, value)` – キー/バリュー形式を簡潔に追加。
  - `finish()` / `bytesWritten()` – エンコード完了と書き込まれたバイト数の取得。
- `CborReader`
  - `begin(buffer, length)` – CBORバイナリをパース。
  - `isMap()` – ルートがマップかどうかを確認。
  - `getString(key, out)` / `getInt(key, out)` / `getBool(key, out)` – ルートマップのフィールドを手早く取得。

## 収録スケッチ
- `EncodeStatus/EncodeStatus.ino` – デバイス情報をCBORでエンコードし、シリアルへ16進表示。
- `DecodeStatus/DecodeStatus.ino` – サンプルマップをエンコード→即デコードし、各フィールドを出力。
