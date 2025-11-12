# CJson サンプル

[English README](README.md)

`EspHelper::CJsonDocument`はESP-IDFの`cJSON`をRAII化し、Arduino向けに使いやすいAPIを提供します。複雑なJSONを柔軟に操作したいが生ポインタ管理は避けたい場合に便利です。

## 特長
- `NewObject()`/`NewArray()`でcJSONノードを生成し、プリミティブ値やネストしたドキュメントを追加できます。
- `CJsonDocument::Parse()`で既存文字列を解析し、`getString`/`getNumber`/`getBool`で値を取得。
- `toString(true)`で整形表示、`toString(false)`でコンパクトな送信用文字列を生成。

## 収録スケッチ
- `BuildAndParse/BuildAndParse.ino` – JSONを構築してコンソール出力し、そのまま再パースして値を読む手順を示す例。
