# JsonParser サンプル

[English README](README.md)

ESP-IDFの`json_parser`コンポーネントをArduinoスケッチから扱いやすくする`EspHelper::JsonParser`の例をまとめています。

## 基本の考え方

- **トークンバッファが必須** – `JsonParser parser(128);` のようにトークン数を指定するか、`json_tok_t tokens[128]; JsonParser parser(tokens);` のように自前の配列を渡します。フィールド数 × 4〜5 個を目安に余裕を持って確保してください。
- **Parse → Query → End** – `parse(json)`でトークナイズし、`get*` や `enterObject/enterArray` で値を取得したら `end()` でクリーンアップします。2回目の `parse()` は自動的に前回の状態を `end()` します。
- **オブジェクト/配列ヘルパー** – `getInt("foo", value)` は現在のオブジェクトのフィールドを読む関数です。配列内の値は `enterArray("pins")` で入ったあと `arrayGetInt(index, value)` で取得し、最後に `leaveArray()` を忘れずに。
- **文字列ヘルパー** – `String` へ読み込む場合は必要な長さを先に問い合わせてからコピーするため、バッファサイズを推測する必要がありません。固定長バッファを使う場合は `char *` と `size` を引数に取るオーバーロードを利用してください。

## APIリファレンス

### コンストラクタ
| シグネチャ | 説明 |
|------------|------|
| `JsonParser(json_tok_t *tokens, size_t tokenCount)` | 外部トークンバッファを借用 |
| `JsonParser(json_tok_t (&tokens)[N])` | スタック配列を渡すテンプレート |
| `JsonParser(size_t tokenCount)` | 内部的にトークンを確保 |

### ライフサイクル/ナビゲーション
- `parse(const char *json, size_t length = 0)` / `parse(const String&)`
- `end()` – パーサ状態を解放
- `enterObject(name)` / `leaveObject()`
- `enterArray(name, int *numElements)` / `leaveArray()`
- `arrayEnter(index)` / `arrayLeave()` など、ESP-IDFの関数に対応するAPIを提供

### 値アクセス
- オブジェクト: `getBool` / `getInt` / `getInt64` / `getFloat` / `getString`
- 配列: `arrayGetBool` / `arrayGetInt` / `arrayGetFloat` / `arrayGetString`
- 文字列取得は `json_obj_get_strlen` などで長さを問い合わせてからコピーするため安全です。

## 収録スケッチ

- `BasicParse/BasicParse.ino` – ネストしたJSONからオブジェクト／配列を辿り、bool/int/float/stringを読み出して`Serial`へ出力します。
