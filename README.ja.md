# EspHelper

[English README](README.md)

EspHelperはESP32向けArduino環境からESP-IDFコンポーネントを扱いやすくするための薄いヘッダーオンリーのラッパー集です。必要な`.h`ファイルを1つインクルードするだけで、ESP-IDFの各種機能をArduinoらしい書き味で使えるようになります。

## 特長
- **ヘッダーオンリー**: 依存関係の少ない`.h`だけのユーティリティーなので、スケッチにそのままコピー可能。
- **Arduinoフレンドリー**: `Print`や`String`など馴染みの型と連携するAPIを用意。
- **ESP-IDFコンポーネントを活用**: Arduino-ESP32にビルトイン済みのESP-IDFコンポーネントを手軽に呼び出し。
- **最小限のサンプル**: まず動かすことに集中できるシンプルなexamplesを同梱。

## カテゴリ別リンク
- **JSON**: [JsonGenerator](examples/JSON/JsonGenerator/README.ja.md)、[JsonParser](examples/JSON/JsonParser/README.ja.md)、[cJSON](examples/JSON/CJson/README.ja.md)
- **FreeRTOS**: [Ringbuffer](examples/FreeRTOS/Ringbuf/README.ja.md)、[Task](examples/FreeRTOS/Task/README.ja.md)、[StreamBuffer](examples/FreeRTOS/StreamBuffer/README.ja.md)、[MessageBuffer](examples/FreeRTOS/MessageBuffer/README.ja.md)、[Queue](examples/FreeRTOS/Queue/README.ja.md)、[Semaphore](examples/FreeRTOS/Semaphore/README.ja.md)、[Mutex](examples/FreeRTOS/Mutex/README.ja.md)
- **Utility**: [QrCode](examples/Utility/QrCode/README.ja.md)、[RgbLed](examples/Utility/RgbLed/README.ja.md)、[HttpServer](examples/Utility/HttpServer/README.ja.md)
- 各READMEにAPIリファレンスとサンプルコードがまとまっているので、必要なセクションへ直接アクセスしてください。

## 提供機能
- `EspHelperJsonGenerator.h`: `espressif/json_generator`をArduino流のAPIで利用するためのラッパー。固定バッファ、ストリーミング、リセットパターンをカバー。
- `EspHelperJsonParser.h`: `espressif/json_parser`を薄く包み、トークンバッファ管理と型付きゲッターを提供。
- `EspHelperCJson.h`: ESP-IDFの`cJSON`をRAII化し、柔軟な編集や整形出力、再パースを安全に行えるようにするラッパー。
- `EspHelperQrCode.h`: `espressif/qrcode`で生成したQRコードをキャプチャし、ASCII表示や任意ディスプレイ描画に利用しやすくするラッパー。
- `EspHelperRingbuf.h`: FreeRTOSの`ringbuf`に対して所有権管理・RAII受信アイテム・ISR対応ヘルパーを提供。
- `EspHelperStreamBuffer.h`: FreeRTOSストリームバッファを簡潔に扱い、トリガーレベル設定や静的確保をサポートするラッパー。
- `EspHelperMessageBuffer.h`: FreeRTOSメッセージバッファを包み、メッセージ境界を保ったまま送受信できるヘルパー。
- `EspHelperHttpServer.h`: `esp_http_server`をArduinoライクに扱うためのシンプルなHTTPサーバーラッパー。
- `EspHelperTask.h`: FreeRTOSタスクをラムダで生成・停止できる軽量なRAIIラッパー。
- `EspHelperRgbStrip.h`: `rgbLedWrite()`を用いて複数のRGB LEDを順次駆動するための簡易ストリップAPI。

## 必要環境
- Arduino-ESP32 v2.0.0以降、またはPlatformIOの`framework = arduino`環境。
- C++17に対応したツールチェーン。

## インストール
### Arduino IDE / Arduino CLI
1. 本リポジトリを`~/Arduino/libraries/EspHelper`になるように配置します。
2. スケッチで`src/`配下のヘッダーをインクルードします。利用するESP-IDFコンポーネントはArduinoコア側に既に同梱されているため、追加導入は不要です。

## ライセンス
MIT License（[LICENSE](LICENSE)参照）。
