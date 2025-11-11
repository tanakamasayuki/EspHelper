# EspHelper

[English README](README.md)

EspHelperはESP32向けArduino環境からESP-IDFコンポーネントを扱いやすくするための薄いヘッダーオンリーのラッパー集です。必要な`.h`ファイルを1つインクルードするだけで、`espressif/json_generator`や`espressif/json_parser`などの機能をArduinoらしい書き味で使えます。

## 特長
- **ヘッダーオンリー**: 依存関係の少ない`.h`だけのユーティリティーなので、スケッチにそのままコピー可能。
- **Arduinoフレンドリー**: `Print`や`String`など馴染みの型と連携するAPIを用意。
- **ESP-IDFコンポーネントを活用**: Arduino-ESP32にビルトイン済みのESP-IDFコンポーネントを手軽に呼び出し。
- **JSON生成/解析を網羅**: `EspHelperJsonGenerator.h`と`EspHelperJsonParser.h`の両方を提供し、同じ感覚で扱えるAPIを用意。
- **最小限のサンプル**: まず動かすことに集中できるシンプルなexamplesを同梱。

## 必要環境
- Arduino-ESP32 v2.0.0以降、またはPlatformIOの`framework = arduino`環境。
- C++17に対応したツールチェーン。

## インストール
### Arduino IDE / Arduino CLI
1. 本リポジトリを`~/Arduino/libraries/EspHelper`になるように配置します。
2. スケッチで`src/`配下のヘッダーをインクルードします。利用するESP-IDFコンポーネントはArduinoコア側に既に同梱されているため、追加導入は不要です。

## サンプルスケッチ
- `examples/JsonGenerator/AllFunctions` : `JsonGenerator`の全メソッド（reset系やストリーミング含む）をまとめて試せる例。
- `examples/JsonGenerator/StaticJsonBuffer` : 固定長バッファを使ってJSONを生成し、`Serial`へ出力する基本例。
- `examples/JsonGenerator/StreamingToSerial` : `Print`ベースのコンストラクタでトークンを逐次`Serial`に流すストリーミング例。
- `examples/JsonParser/BasicParse` : `JsonParser`でネストしたJSONを解析し、配列やオブジェクトから型付きで値を取得する例。
- それぞれ最小限のコードで構成されているため、必要な部分だけを既存スケッチにコピーできます。

## ライセンス
MIT License（[LICENSE](LICENSE)参照）。
