# Utility サンプル

[English README](README.md)

JSONやFreeRTOSカテゴリに属さない汎用ユーティリティ向けヘルパーのサンプルをまとめています。現時点ではQRコード表示、`esp_dsp`ベースのDSPラッパー、`esp_event`ラッパー、libsodiumラッパーを掲載しています。

## サブディレクトリ
- [QrCode](QrCode/README.ja.md)
- [Dsp](Dsp/README.ja.md)
- [Event](Event/README.ja.md)
- [Sodium](Sodium/README.ja.md)

- **QrCode (`EspHelperQrCode.h`)** – ESP-IDFコンポーネント`espressif/qrcode`を使ってQRコードを生成し、ASCII表示やM5Unifiedなどの任意ディスプレイへ描画できます。
- **Dsp (`EspHelperDsp.h`)** – `esp_dsp`のFFTやFIRフィルタAPIをArduino流に扱えるラッパー。
- **Event (`EspHelperEvent.h`)** – `esp_event`のイベントループ／ハンドラ登録／ポストを簡単に扱えるラッパー。
- **Sodium (`EspHelperSodium.h`)** – libsodium の乱数・`crypto_secretbox`・Ed25519署名を手軽に扱うラッパー。

詳細は `QrCode/`、`Dsp/`、`Event/`、`Sodium/` ディレクトリを参照してください。
