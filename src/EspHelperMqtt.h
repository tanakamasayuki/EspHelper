#pragma once

#include <Arduino.h>
#include <functional>

extern "C" {
#include <mqtt_client.h>
}

namespace EspHelper {

class MqttClient {
 public:
  using EventCallback = std::function<void(const esp_mqtt_event_t &event)>;

  MqttClient() = default;
  ~MqttClient() { end(); }

  bool begin(const esp_mqtt_client_config_t &config)
  {
    end();
    esp_mqtt_client_config_t cfg = config;
    handle_ = esp_mqtt_client_init(&cfg);
    if (!handle_)
    {
      return false;
    }
    esp_err_t err = esp_mqtt_client_register_event(handle_, MQTT_EVENT_ANY, &MqttClient::eventThunk, this);
    if (err != ESP_OK)
    {
      esp_mqtt_client_destroy(handle_);
      handle_ = nullptr;
      return false;
    }
    return true;
  }

  bool begin(const char *uri)
  {
    if (!uri)
    {
      return false;
    }
    esp_mqtt_client_config_t config = {};
    config.broker.address.uri = uri;
    return begin(config);
  }

  bool start()
  {
    return handle_ && esp_mqtt_client_start(handle_) == ESP_OK;
  }

  bool stop()
  {
    return handle_ && esp_mqtt_client_stop(handle_) == ESP_OK;
  }

  void end()
  {
    if (handle_)
    {
      esp_mqtt_client_unregister_event(handle_, MQTT_EVENT_ANY, &MqttClient::eventThunk);
      esp_mqtt_client_destroy(handle_);
      handle_ = nullptr;
    }
    connected_ = false;
  }

  bool publish(const char *topic,
               const char *payload,
               int qos = 0,
               bool retain = false)
  {
    if (!handle_ || !topic || !payload)
    {
      return false;
    }
    int msg_id = esp_mqtt_client_publish(handle_, topic, payload, 0, qos, retain);
    return msg_id >= 0;
  }

  bool publish(const char *topic,
               const uint8_t *payload,
               size_t length,
               int qos = 0,
               bool retain = false)
  {
    if (!handle_ || !topic || (!payload && length > 0))
    {
      return false;
    }
    int msg_id = esp_mqtt_client_publish(handle_, topic, reinterpret_cast<const char *>(payload), length, qos, retain);
    return msg_id >= 0;
  }

  bool subscribe(const char *topic, int qos = 0)
  {
    if (!handle_ || !topic)
    {
      return false;
    }
    return esp_mqtt_client_subscribe(handle_, topic, qos) >= 0;
  }

  bool unsubscribe(const char *topic)
  {
    if (!handle_ || !topic)
    {
      return false;
    }
    return esp_mqtt_client_unsubscribe(handle_, topic) >= 0;
  }

  void setEventCallback(EventCallback cb) { callback_ = std::move(cb); }

  bool connected() const { return connected_; }
  esp_mqtt_client_handle_t raw() const { return handle_; }

 private:
  static void eventThunk(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
  {
    MqttClient *self = static_cast<MqttClient *>(handler_args);
    if (!self || event_data == nullptr)
    {
      return;
    }
    auto *event = static_cast<esp_mqtt_event_handle_t>(event_data);
    if (event->event_id == MQTT_EVENT_CONNECTED)
    {
      self->connected_ = true;
    }
    else if (event->event_id == MQTT_EVENT_DISCONNECTED)
    {
      self->connected_ = false;
    }
    if (self->callback_)
    {
      self->callback_(*event);
    }
  }

  esp_mqtt_client_handle_t handle_ = nullptr;
  EventCallback callback_{};
  bool connected_ = false;
};

}  // namespace EspHelper
