# Utility サンプル

[English README](README.md)

JSONやFreeRTOSカテゴリに属さない汎用ユーティリティ向けヘルパーのサンプルをまとめています。現時点ではQRコード表示、`esp_dsp`ベースのDSPラッパー、`esp_event`ラッパー、`rgbLedWrite()`ラッパーを掲載しています。

- **QrCode (`EspHelperQrCode.h`)** – ESP-IDFコンポーネント`espressif/qrcode`を使ってQRコードを生成し、ASCII表示やM5Unifiedなどの任意ディスプレイへ描画できます。
- **Dsp (`EspHelperDsp.h`)** – `esp_dsp`のFFTやFIRフィルタAPIをArduino流に扱えるラッパー。
- **Event (`EspHelperEvent.h`)** – `esp_event`のイベントループ／ハンドラ登録／ポストを簡単に扱えるラッパー。
- **RgbStrip (`EspHelperRgbStrip.h`)** – Arduinoコアの`rgbLedWrite()`を連続で呼び、1本のピンに直列接続した複数のRGB LEDを簡単に制御するラッパー。

詳細は `QrCode/`、`Dsp/`、`Event/`、`RgbLed/` ディレクトリを参照してください。
