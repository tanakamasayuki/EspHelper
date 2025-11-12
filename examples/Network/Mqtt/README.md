# Mqtt Examples

[日本語はこちら](README.ja.md)

`EspHelperMqtt.h` wraps the ESP-IDF `esp-mqtt` client in a tiny RAII class so sketches can create a client, attach a single event callback, and use Arduino-friendly helpers for publish/subscribe.

## API Reference
- `bool begin(const esp_mqtt_client_config_t &config)` / `bool begin(const char *uri)` – initialize the client and register an internal event dispatcher.
- `bool start()` / `bool stop()` / `void end()` – manage the lifecycle (destroying the client in `end`).
- `void setEventCallback(EventCallback cb)` – receive every MQTT event (`esp_mqtt_event_t`).
- `bool publish(topic, payload, qos = 0, retain = false)` – overloads for C strings or raw byte buffers.
- `bool subscribe(topic, qos)` / `bool unsubscribe(topic)`.
- `bool connected() const` – reflects the latest CONNECTED/DISCONNECTED events.
- `esp_mqtt_client_handle_t raw() const` – drop down to the native API when you need advanced features.

Usage notes:
- `esp_mqtt_client_config_t` expects pointers (URI, credentials) that must outlive the client. Stick to string literals or other static storage.
- The helper registers a single event callback (`MQTT_EVENT_ANY`). Use a `switch` inside your lambda/function to respond to `MQTT_EVENT_DATA`, `MQTT_EVENT_ERROR`, etc.
- Remember to bring up Wi-Fi (or Ethernet) before calling `start()`. The helper deliberately stays agnostic of the transport layer.

## Example overview
- `BasicPublish/BasicPublish.ino` – Connects to a public broker and publishes a counter every 5 seconds once connected.
- `SubscribeEcho/SubscribeEcho.ino` – Subscribes to `esphelper/command/#`, toggles the built-in LED based on payloads, and echoes responses to another topic.
