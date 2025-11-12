# QrCode サンプル

[English README](README.md)

`EspHelperQrCode.h` は ESP-IDF の `espressif/qrcode` を包み、生成済みのQRコードをASCIIやディスプレイへ簡単に描画できます。

## APIリファレンス
- `generate(text, maxVersion, eccLevel)` – 一度呼び出すと内部コールバックでビットマップをキャプチャ。
- `ready()` / `size()` – QRが利用可能か、何マス四方かを取得。
- `module(x, y)` – 個別モジュールが黒か白かをブーリアンで返す。
- `forEachModule(lambda)` – `(x, y, bool on)` 形式のラムダで全モジュールを走査。
- `toAscii(dark, light, border)` – シリアルに出力できるASCIIアートを生成。

## 収録スケッチ
- `AsciiConsole/AsciiConsole.ino` – URLをエンコードしてASCIIブロックで表示。
- `M5Display/M5Display.ino` – Wi-Fi情報をQR化し、M5Unifiedディスプレイへ描画。
