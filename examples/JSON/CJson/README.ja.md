# CJson サンプル

[English README](README.md)

`EspHelper::CJsonDocument`はESP-IDFの`cJSON`をRAII化したヘルパーです。複雑なJSONを柔軟に編集したり、整形出力したりする際に便利です。

## 基本ポイント
- **生成** – `NewObject()`/`NewArray()`で空のノードを作り、`Parse()`で文字列から構築できます。
- **所有権** – デストラクタで`cJSON_Delete`を呼びますが、`release()`で生ポインタを引き渡すことも可能。
- **文字列処理** – `String`に直接読み込むオーバーロードを用意し、バッファサイズを推測する必要がありません。

## API リファレンス
- ライフタイム: `valid()`, `reset()`, `release()`
- シリアライズ: `toString(bool pretty = false)`
- オブジェクト編集: `addString`, `addNumber`, `addBool`, `addNull`, `addObject`, `addArray`
- 配列編集: `arrayAddNumber`, `arrayAddString`, `arrayAddBool`, `arrayAddNull`, `arrayAdd(CJsonDocument&&)`
- アクセス: `getString`, `getNumber`, `getBool`, `arraySize`, `arrayItem`

## 収録スケッチ
- `BuildAndParse/BuildAndParse.ino` – JSONを構築してコンソールに出力し、そのまま再パースして値を読み出す一連の手順を示します。
