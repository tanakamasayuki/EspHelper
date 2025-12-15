#include <WiFi.h>
#include <EspHelperMqtt.h>

#if __has_include("arduino_secrets.h")
#include "arduino_secrets.h"
#else
#define WIFI_SSID "YourSSID"     // Enter your Wi-Fi SSID here / Wi-FiのSSIDを入力
#define WIFI_PASS "YourPassword" // Enter your Wi-Fi password here / Wi-Fiのパスワードを入力
#endif

EspHelper::MqttClient mqtt;
unsigned long lastPublish = 0;
uint32_t counter = 0;

void handleMqttEvent(const esp_mqtt_event_t &event)
{
  switch (event.event_id)
  {
  case MQTT_EVENT_CONNECTED:
    Serial.println("MQTT connected");
    break;
  case MQTT_EVENT_DISCONNECTED:
    Serial.println("MQTT disconnected");
    break;
  case MQTT_EVENT_ERROR:
    Serial.printf("MQTT error: %d\n", event.error_handle ? event.error_handle->error_type : -1);
    break;
  default:
    break;
  }
}

void connectWifi()
{
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println(" connected");
}

void setup()
{
  Serial.begin(115200);
  delay(200);
  connectWifi();

  esp_mqtt_client_config_t config = {};
  config.broker.address.uri = "mqtt://broker.emqx.io";
  config.credentials.client_id = "EspHelperBasicPublisher";

  mqtt.setEventCallback(handleMqttEvent);
  if (!mqtt.begin(config) || !mqtt.start())
  {
    Serial.println("Failed to start MQTT client");
    while (true)
    {
      delay(1000);
    }
  }
}

void loop()
{
  if (!mqtt.connected())
  {
    delay(100);
    return;
  }

  const unsigned long now = millis();
  if (now - lastPublish >= 5000)
  {
    lastPublish = now;
    char payload[64];
    snprintf(payload, sizeof(payload), "count=%lu uptime=%lus", ++counter, now / 1000UL);
    mqtt.publish("esphelper/demo", payload, 0, false);
    Serial.printf("Published: %s\n", payload);
  }
}
