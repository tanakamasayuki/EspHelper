# Mqtt サンプル

[English README](README.md)

`EspHelperMqtt.h` は ESP-IDF の `esp-mqtt` クライアントをRAIIクラスで包み、イベントコールバックと publish/subscribe をArduinoから簡潔に扱えるようにします。

## APIリファレンス
- `begin(config)` / `begin(uri)` – `esp_mqtt_client_config_t` からクライアントを生成。
- `start()` / `stop()` / `end()` – ライフサイクル管理。`end()`でクライアントを破棄します。
- `setEventCallback(cb)` – `esp_mqtt_event_t` をすべて受け取るコールバックを登録。
- `publish(topic, payload, qos, retain)` – 文字列またはバイト列を送信。
- `subscribe(topic, qos)` / `unsubscribe(topic)` – トピック購読を制御。
- `connected()` – 直近の接続状態を確認。
- `raw()` – ネイティブAPIを直接扱いたい場合のハンドル取得。

使いどころメモ
- `esp_mqtt_client_config_t` 内のURIや証明書ポインタはクライアント存続中に有効である必要があります。文字列リテラルやstatic領域を使うと安全です。
- コールバック内で `switch(event.event_id)` を使い、接続・切断・データ受信などをハンドリングしてください。
- Wi-Fi/Ethernetの接続確立はラッパーの外で行います。`start()`前にネットワークを準備してください。

## 収録スケッチ
- `BasicPublish/BasicPublish.ino` – 公開ブローカーに接続し、5秒おきにカウンタをpublish。
- `SubscribeEcho/SubscribeEcho.ino` – `esphelper/command/#` にサブスクライブし、LEDのON/OFFコマンドを受信して応答トピックにエコーする例。
