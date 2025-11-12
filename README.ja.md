# EspHelper

[English README](README.md)

EspHelperはESP32向けArduino環境からESP-IDFコンポーネントを扱いやすくするための薄いヘッダーオンリーのラッパー集です。必要な`.h`ファイルを1つインクルードするだけで、ESP-IDFの各種機能をArduinoらしい書き味で使えるようになります。

## 特長
- **ヘッダーオンリー**: 依存関係の少ない`.h`だけのユーティリティーなので、スケッチにそのままコピー可能。
- **Arduinoフレンドリー**: `Print`や`String`など馴染みの型と連携するAPIを用意。
- **ESP-IDFコンポーネントを活用**: Arduino-ESP32にビルトイン済みのESP-IDFコンポーネントを手軽に呼び出し。
- **最小限のサンプル**: まず動かすことに集中できるシンプルなexamplesを同梱。

## 提供機能
- `EspHelperJsonGenerator.h`: `espressif/json_generator`をArduino流のAPIで利用するためのラッパー。固定バッファ、ストリーミング、リセットパターンをカバー。
- `EspHelperJsonParser.h`: `espressif/json_parser`を薄く包み、トークンバッファ管理と型付きゲッターを提供。
- `EspHelperCJson.h`: ESP-IDFの`cJSON`をRAII化し、柔軟な編集や整形出力、再パースを安全に行えるようにするラッパー。
- `EspHelperQrCode.h`: `espressif/qrcode`で生成したQRコードをキャプチャし、ASCII表示や任意ディスプレイ描画に利用しやすくするラッパー。
- `EspHelperRingbuf.h`: FreeRTOSの`ringbuf`に対して所有権管理・RAII受信アイテム・ISR対応ヘルパーを提供。
- `EspHelperRgbStrip.h`: `rgbLedWrite()`を用いて複数のRGB LEDを順次駆動するための簡易ストリップAPI。

## 必要環境
- Arduino-ESP32 v2.0.0以降、またはPlatformIOの`framework = arduino`環境。
- C++17に対応したツールチェーン。

## インストール
### Arduino IDE / Arduino CLI
1. 本リポジトリを`~/Arduino/libraries/EspHelper`になるように配置します。
2. スケッチで`src/`配下のヘッダーをインクルードします。利用するESP-IDFコンポーネントはArduinoコア側に既に同梱されているため、追加導入は不要です。

## サンプルスケッチ
- `examples/JSON/JsonGenerator/AllFunctions` : `JsonGenerator`の全メソッド（reset系やストリーミング含む）をまとめて試せる例。
- `examples/JSON/JsonGenerator/StaticJsonBuffer` : 固定長バッファを使ってJSONを生成し、`Serial`へ出力する基本例。
- `examples/JSON/JsonGenerator/StreamingToSerial` : `Print`ベースのコンストラクタでトークンを逐次`Serial`に流すストリーミング例。
- `examples/JSON/JsonParser/BasicParse` : `JsonParser`でネストしたJSONを解析し、配列やオブジェクトから型付きで値を取得する例。
- `examples/JSON/CJson/BuildAndParse` : cJSONラッパーでJSONを構築・整形・再パースする例。
- `examples/FreeRTOS/Ringbuf/ByteBuffer` : `EspHelper::Ringbuffer`でBYTEBUFを生成し、文字列データをプッシュ＆読み戻しする例。
- `examples/FreeRTOS/Ringbuf/FixedStruct` : 静的メモリ＋No-Splitリングバッファに固定サイズ構造体を流す例で、センサーデータの受け渡しなどに応用可能。
- `examples/Utility/QrCode/AsciiConsole` : 生成したQRコードをASCIIアートとして`Serial`に表示する例。
- `examples/Utility/QrCode/M5Display` : M5UnifiedデバイスへWi-Fi設定QRコードを描画する例。
- `examples/Utility/RgbLed/SimpleStrip` : 1個のRGB LEDを順番に点灯させる最小例。
- `examples/Utility/RgbLed/MultiStrip` : 3個のRGB LEDでカラーWipeや一括点灯を行う例。
- それぞれ最小限のコードで構成されているため、必要な部分だけを既存スケッチにコピーできます。

## ライセンス
MIT License（[LICENSE](LICENSE)参照）。
