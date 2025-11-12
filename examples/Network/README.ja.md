# Network サンプル

[English README](README.md)

ESP-IDFのネットワーク機能（MQTTやHTTPサーバーなど）をArduinoライクに扱うヘルパーをまとめています。各サブディレクトリにAPIリファレンスとサンプルスケッチを収録しています。

- **Mqtt (`EspHelperMqtt.h`)** – `esp-mqtt`クライアントをRAIIで管理し、イベントコールバックとpublish/subscribeをシンプルにするラッパー。([Docs](Mqtt/README.ja.md))
- **HttpServer (`EspHelperHttpServer.h`)** – `esp_http_server`をラップし、WebServer風のハンドラ登録とレスポンス送信を扱いやすくしたヘルパー。([Docs](HttpServer/README.ja.md))

詳細は各サブディレクトリを参照してください。
