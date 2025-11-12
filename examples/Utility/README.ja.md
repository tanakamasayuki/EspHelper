# Utility サンプル

[English README](README.md)

JSONやFreeRTOSカテゴリに属さないユーティリティ向けヘルパーのサンプルをまとめています。現時点ではQRコード表示と`rgbLedWrite()`ラッパーを掲載しています。

- **QrCode (`EspHelperQrCode.h`)** – ESP-IDFコンポーネント`espressif/qrcode`を使ってQRコードを生成し、ASCII表示やM5Unifiedなどの任意ディスプレイへ描画できます。
- **RgbStrip (`EspHelperRgbStrip.h`)** – Arduinoコアの`rgbLedWrite()`を連続で呼び、1本のピンに直列接続した複数のRGB LEDを簡単に制御するラッパー。

詳細は `QrCode/` および `RgbLed/` ディレクトリを参照してください。
