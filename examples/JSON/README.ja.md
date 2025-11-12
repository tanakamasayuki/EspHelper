# JSON サンプル

[English README](README.md)

EspHelperに含まれるJSON関連ヘルパーを試すスケッチをまとめています。

- **JsonGenerator (`EspHelperJsonGenerator.h`)** – ESP-IDFコンポーネント`espressif/json_generator`を包んだラッパー。固定バッファやストリーミング出力でJSONを生成し、メモリ使用量を制御しつつテレメトリやログを出力できます。
- **JsonParser (`EspHelperJsonParser.h`)** – ESP-IDFコンポーネント`espressif/json_parser`を薄く包み、トークンバッファ管理と型付きゲッターを提供。HTTPレスポンスや設定JSONを安全に読みたいときに使います。
- **CJson (`EspHelperCJson.h`)** – ESP-IDFの`cJSON`実装をRAII化し、柔軟な編集や整形出力を行いたいときに便利なヘルパーです。

## 使い分けのヒント
- JSONを**生成**したい（ステータス送信、設定エクスポート、ストリーミングログなど）→ `JsonGenerator/…`配下の例へ。
- JSONを**解析**したい（Web APIの応答、クラウド設定、コマンド受信など）→ `JsonParser/…`配下の例へ。
- よりリッチなcJSON APIで細かな加工や整形を行いたい → `CJson/…`配下の例へ。
- 送受信両方行うプロジェクトも多いので、ヘッダーを併用しても問題ありません。

## 収録スケッチ
- `JsonGenerator/AllFunctions` – Generatorの全APIを網羅。
- `JsonGenerator/StaticJsonBuffer` – 固定長バッファで最小限のJSON生成。
- `JsonGenerator/StreamingToSerial` – 小さなチャンクで`Serial`へストリーミング。
- `JsonParser/BasicParse` – ネストしたオブジェクト／配列を辿って値を取り出す例。
- `CJson/BuildAndParse` – cJSONで構築したデータを出力し、そのまま再パースして値を読み出す例。

このリポジトリを`~/Arduino/libraries/EspHelper`に配置し、Arduino-ESP32 v2.0.0以降をターゲットに各スケッチをビルドしてください。
