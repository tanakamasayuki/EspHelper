# Event サンプル

[English README](README.md)

`EspHelper::EventLoop` は `esp_event` のデフォルトループ／カスタムループの生成、ハンドラ登録、イベント送信をArduino風のAPIでまとめたラッパーです。

## APIリファレンス
- `createDefault()` – グローバルのデフォルトループを確保し、そのハンドルを保持します。
- `createCustom(args)` – `esp_event_loop_args_t` でキューサイズやタスク属性を指定して独立したループを生成。
- `end()` – カスタムループを削除（本インスタンスが生成したデフォルトループなら削除）します。
- `registerHandler(base, id, handler, arg, instance)` / `unregisterHandler(...)` – `esp_event_handler_instance_*` を使いやすい形で呼び出します。
- `post(base, id, data, size, ticks)` – 対象ループへイベントをポストします。
- `raw()` – 低レベルAPIを使いたい場合にハンドルを取得。

使いどころメモ
- 1つの`EventLoop`インスタンスは1つのループのみ担当します。別ループへ切り替える前に`end()`してください。
- イベントデータの構造体は値コピーされるため、スタック上の一時構造体でも安全です。
- ハンドラはループ専用タスク上で実行されます。重い処理は別タスクに逃がすか、イベント内で最小限にとどめてください。

## 収録スケッチ
- `DefaultLoop/DefaultLoop.ino` – グローバルループにハンドラを登録し、`loop()`から定期的にtick／メッセージイベントを送信。
- `CustomLoop/CustomLoop.ino` – APP CPUにピン留めしたカスタムループを作成し、疑似センサー値を処理させる例。
