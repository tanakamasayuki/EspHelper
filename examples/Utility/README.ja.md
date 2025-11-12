# Utility サンプル

[English README](README.md)

JSONやFreeRTOSカテゴリに属さないユーティリティ向けヘルパーのサンプルをまとめています。現時点ではQRコード表示、`esp_dsp`ベースのDSPラッパー、`rgbLedWrite()`ラッパー、`esp_http_server`ラッパーを掲載しています。

- **QrCode (`EspHelperQrCode.h`)** – ESP-IDFコンポーネント`espressif/qrcode`を使ってQRコードを生成し、ASCII表示やM5Unifiedなどの任意ディスプレイへ描画できます。
- **Dsp (`EspHelperDsp.h`)** – `esp_dsp`のFFTやFIRフィルタAPIをArduino流に扱えるラッパー。
- **Event (`EspHelperEvent.h`)** – `esp_event`のイベントループ／ハンドラ登録／ポストを簡単に扱えるラッパー。
- **RgbStrip (`EspHelperRgbStrip.h`)** – Arduinoコアの`rgbLedWrite()`を連続で呼び、1本のピンに直列接続した複数のRGB LEDを簡単に制御するラッパー。
- **HttpServer (`EspHelperHttpServer.h`)** – `esp_http_server`のルート登録とレスポンス送信をArduino風のAPIで扱えるラッパー。

詳細は `QrCode/`、`Dsp/`、`Event/`、`RgbLed/`、`HttpServer/` ディレクトリを参照してください。
