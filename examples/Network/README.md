# Network Examples

[日本語はこちら](README.ja.md)

Network examples cover helpers that sit on top of the ESP-IDF networking stack (MQTT, HTTP server, and more in the future). Each subdirectory includes sketches plus an API mini-reference for the matching header.

## Subdirectories
- [Mqtt](Mqtt/README.md)
- [HttpServer](HttpServer/README.md)

- **Mqtt (`EspHelperMqtt.h`)** – RAII wrapper for `esp-mqtt` with a single event callback, easy publish/subscribe helpers, and connection tracking.
- **HttpServer (`EspHelperHttpServer.h`)** – Arduino-style façade over `esp_http_server` that lets you register handlers with lambdas and send text/JSON responses.

See the individual subdirectories for API details and sketches.
