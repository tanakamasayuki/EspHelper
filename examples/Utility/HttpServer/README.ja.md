# HttpServer サンプル

[English README](README.md)

`EspHelper::HttpServer` は ESP-IDF の `esp_http_server` をArduinoらしい書き味で扱えるようにしたラッパーです。`WebServer` や `ESPAsyncWebServer` に近い感覚でルートを登録できます。

## APIリファレンス
- `HttpServer(config)` – `HTTPD_DEFAULT_CONFIG()`をベースにポートやスレッド優先度をカスタマイズ可能。
- `start()` / `stop()` / `started()`
- `on(uri, method, handler)` に加え `onGet`、`onPost`、`onPut`、`onDelete`
- 静的ヘルパー: `sendText`、`sendJson`、`sendChunk`、`sendEmpty`
- `raw()` で `httpd_handle_t` を取得し、低レベルAPIと併用可能。

## 収録スケッチ
- `SimpleServer/SimpleServer.ino` – Wi-Fiに接続し、HTMLページの配信とPOSTボディのエコーエンドポイントを実装。
