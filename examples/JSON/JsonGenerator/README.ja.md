# JsonGenerator サンプル

[English README](README.md)

`EspHelper::JsonGenerator`の使い方を示すArduinoスケッチをまとめたディレクトリです。各フォルダは単体でArduino IDE / CLIに読み込める構成になっています。

## 基本の考え方

- **ヘッダーオンリー** – `JsonGenerator`はESP-IDFの`json_generator`をラップしたヘッダーのみのヘルパーです。ライブラリを`~/Arduino/libraries/EspHelper`に配置し、スケッチで`src/EspHelperJsonGenerator.h`をインクルードします。
- **start/endとpush/popの違い** – `startObject()`/`endObject()`や`startArray()`/`endArray()`は、`[`や`{`で始まる無名のコンテナを開閉するときに使います（例: ルートを配列にしたい場合は `startArray(); …; endArray();` のみを呼べばOK）。一方で、既存のオブジェクトに `"sensor": { … }` のような名前付き要素を追加したい場合は `pushObject("sensor"); …; popObject();` を使います。`push*`は内部で `"sensor":` までを自動生成してくれるため、二重で `setString("sensor", …)` などを呼ばない点がポイントです。それぞれの開始関数と終了関数は必ずペアにしてください。
- **再利用時は必ず`reset()`** – `finish()`で出力した後は、`reset()`あるいは`reset(buffer, size, ...)`などのオーバーロードを呼んで内部状態を初期化してから次のJSONを生成してください。リセットしないまま書き足すと、カンマ挿入ルールやバッファ内容が壊れます。
- **バッファ vs ストリーミング** – 固定長バッファを自前で用意して制御する方法と、`JsonGenerator(Print &out, size_t chunkSize)`で`Print`（Serialなど）へストリーミングする方法の2種類があります。ストリーミング時もESP-IDFの仕様上、小さな作業用バッファ（chunkSize）が必要です。

## API リファレンス

### コンストラクタ
| シグネチャ | 説明 |
|------------|------|
| `JsonGenerator(char *buffer, size_t capacity, json_gen_flush_cb_t flush = nullptr, void *priv = nullptr)` | 手持ちバッファを利用 |
| `JsonGenerator(char (&buffer)[N], ...)` | 配列をテンプレートで渡す補助 |
| `JsonGenerator(Print &out, size_t chunkSize = 128)` | `Print`へ直接ストリーミング |

### 状態管理 / アクセス
- `reset(...)` – バッファ/フラッシュコールバックを変更したい場合に使用
- `finish()` – JSONを閉じて`c_str()`で読める状態にしつつ総バイト数を返す
- `data()` / `c_str()` / `raw()` – 生成中のバッファや生の `json_gen_str_t` へアクセス

### オブジェクト操作
- `startObject()`, `endObject()`
- `pushObject(name)`, `popObject()`
- `setBool(name, value)`, `setInt`, `setFloat`, `setString`, `setNull`

### 配列操作
- `startArray()`, `endArray()`
- `pushArray(name)`, `popArray()`
- `arrayAddBool(value)`, `arrayAddInt`, `arrayAddFloat`, `arrayAddString`, `arrayAddNull`

### ストリーミング利用
- `JsonGenerator(Print &, chunkSize)` で`rgbLedWrite`のように直接 `Print`（`Serial`など）へ書き出す
- 最後に必ず `finish()` を呼んで最終チャンクをフラッシュし、必要なら `Serial.println()` などで改行を挿入する

## 詳しい使い方

| 目的 | 呼び出し例 | 生成されるJSON |
| ---- | ---------- | ------------- |
| ルートをオブジェクトにする | `startObject(); …; endObject();` | `{ … }` |
| ルートを配列にする | `startArray(); …; endArray();` | `[ … ]` |
| 名前付きオブジェクト | `pushObject("cfg"); …; popObject();` | `"cfg":{ … }` |
| 名前付き配列 | `pushArray("pins"); …; popArray();` | `"pins":[ … ]` |
| オブジェクトの値 | `setString("tag","esp32")` | `"tag":"esp32"` |
| 配列の値 | `arrayAddInt(42)`（配列を開始した後） | `42` |
| null値 | `setNull("error")` または `arrayAddNull()` | `"error":null` / `null` |

1. **初期化** – 固定バッファなら `char buf[256]; JsonGenerator json(buf);`、ストリーミングなら `JsonGenerator json(Serial, 128);` のようにコンストラクトします。
2. **組み立て** – start/end/push/popで構造を作り、各フィールドに対して`set*`または`arrayAdd*`を呼びます。
3. **完了** – `finish()`が未出力分をflushし、終端ヌルを付けて総バイト数を返します。`c_str()`でバッファを読むか、flushコールバック経由で処理できます。
4. **再利用** – 連続で使う場合は必ず `reset()`、`reset(newBuffer, size)`、`reset(flushCb, priv)` などを呼んで状態を初期化します。

### ミニサンプル

```cpp
// ルートがオブジェクト
json.reset();
json.startObject();
json.setString("device", "ESP32");
json.pushArray("pins");
json.arrayAddInt(2);
json.arrayAddInt(4);
json.popArray();
json.endObject();
json.finish();  // -> {"device":"ESP32","pins":[2,4]}
```

```cpp
// ルートが配列 + Serialへストリーミング
EspHelper::JsonGenerator streamJson(Serial, 96);
streamJson.startArray();
streamJson.pushObject("meta");
streamJson.setInt("cycle", 1);
streamJson.popObject();
streamJson.arrayAddBool(true);
streamJson.endArray();
streamJson.finish();  // Serial出力: [{"meta":{"cycle":1}},true]
```

## 収録されているスケッチ

- `AllFunctions/AllFunctions.ino` – すべてのメソッド（reset各種、flushコールバック、`raw()`アクセス、ストリーミングなど）を一度に試せる総合例。
- `StaticJsonBuffer/StaticJsonBuffer.ino` – スタック上の固定バッファを再利用しながらJSONを生成し、`Serial`へ出力する最小パターン。
- `StreamingToSerial/StreamingToSerial.ino` – 小さなチャンクバッファ＋`Print`コンストラクタを使って逐次`Serial`へ送るRAM節約パターン。

どのスケッチも`Serial.begin(115200);`で初期化し、Arduino-ESP32 v2.0.0以降でそのまま動作します。自分の用途に合わせて必要な部分だけをコピーしてご利用ください。
