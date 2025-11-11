# JsonParser サンプル

[English README](README.md)

ESP-IDFの`json_parser`コンポーネントをArduinoスケッチから扱いやすくする`EspHelper::JsonParser`の例をまとめています。

## 基本の考え方

- **トークンバッファが必須** – `JsonParser parser(128);` のようにトークン数を指定して生成するか、`json_tok_t tokens[128]; JsonParser parser(tokens);` のように自前バッファを渡します。トークンはJSONの各プリミティブやオブジェクト／配列1つにつき少なくとも1個（オブジェクトなら自身1つ＋子要素分）消費するので、フィールド1つあたり4〜5トークンを目安に余裕を持って確保すると安定します。
- **Parse→Query→End** – `parse(json)`でトークン化し、`get*`や`enterObject/enterArray`で値を取得、作業が終わったら`end()`で後片付けします。2回目の`parse()`を呼ぶ前にも`end()`されるので、連続利用も簡単です。
- **オブジェクトと配列のヘルパー** – 現在のオブジェクトからフィールドを読むときは`getInt(\"foo\", value)`などを使います。配列内の値は`enterArray(\"pins\")`で入ってから`arrayGetInt(index, value)`で取得し、最後に`leaveArray()`で抜けます。必ず入ったら出る、を徹底してください。
- **文字列の扱い** – `String`に受ける場合は必要な長さを先に問い合わせてから読み取るので、バッファサイズを予測する必要はありません。固定長バッファを使いたい場合は`char *`と`size`を引数に取るオーバーロードを利用してください。

## 収録スケッチ

- `BasicParse/BasicParse.ino` – ネストしたJSONからオブジェクト／配列を辿り、bool/int/float/stringを読み出して`Serial`へ表示します。

どのスケッチもArduino-ESP32 v2.0.0以降を想定しており、追加のコンポーネント導入は不要です。このリポジトリを`~/Arduino/libraries`へ配置し、サンプルをそのままビルドしてください。
