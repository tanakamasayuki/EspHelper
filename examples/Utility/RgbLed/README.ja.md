# RgbLed サンプル

[English README](README.md)

`EspHelper::RgbStrip` は Arduino-ESP32 コアに含まれる `rgbLedWrite(pin, r, g, b)` をまとめて扱いやすくする簡易ラッパーです。コンストラクタにデータピンとLED数を渡すと各LEDの色を保持し、`show()`時に順番に `rgbLedWrite()` を呼んでいきます。

## 特長
- コンストラクタにデータピンとLED数を渡すと、各LEDの色を保持しつつ `show()` で順番に `rgbLedWrite()` を呼びます（呼び出し間に ~50µs のウェイト）。
- `setPixelColor()` で色を設定し、`show()` で全ピンに一括反映。`fill()`/`clear()`で一括更新、`setBrightness()`で全体の明るさ調整が可能。
- ピンごとにDMAやタスクを使わず順次書き込むため、動作がシンプルで予測しやすい構造です。

## 収録スケッチ
- `SimpleStrip/SimpleStrip.ino` – ピン2に接続した単体のRGB LEDで赤→緑→青を順番に点灯。
- `MultiStrip/MultiStrip.ino` – ピン2/4/5に接続した複数LEDでカラーWipeと一括点灯を行うデモ。
