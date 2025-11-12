# HttpServer Examples

[日本語はこちら](README.ja.md)

`EspHelper::HttpServer` is a light wrapper around ESP-IDF's `esp_http_server` API that feels similar to Arduino's `WebServer` or `ESPAsyncWebServer` interfaces.

## API Reference
- `HttpServer(const httpd_config_t &config = HTTPD_DEFAULT_CONFIG())`
- `bool start()` / `void stop()` / `bool started() const`
- Route registration: `on(uri, method, handler)`, plus helpers `onGet`, `onPost`, `onPut`, `onDelete`
- Static helpers: `sendText`, `sendJson`, `sendChunk`, `sendEmpty`
- Access raw handle with `raw()` to register advanced handlers directly.

Handlers receive the raw `httpd_req_t *` so you can call any ESP-IDF API (e.g., `httpd_resp_send`).

## Example Overview
- `SimpleServer/SimpleServer.ino` – Connects to Wi-Fi, serves a basic HTML page, and echoes POST bodies back to the client.
