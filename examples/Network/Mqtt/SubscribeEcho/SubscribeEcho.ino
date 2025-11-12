#include <WiFi.h>
#include <EspHelperMqtt.h>
#include <cstring>

const char *kSsid = "REPLACE_WITH_SSID";
const char *kPassword = "REPLACE_WITH_PASSWORD";

EspHelper::MqttClient mqtt;
bool pendingCommand = false;
char lastPayload[64] = {0};

void handleMqttEvent(const esp_mqtt_event_t &event)
{
  switch (event.event_id)
  {
    case MQTT_EVENT_CONNECTED:
      Serial.println("MQTT connected, subscribing...");
      mqtt.subscribe("esphelper/command/#", 1);
      break;
    case MQTT_EVENT_DATA:
      if (event.data_len > 0)
      {
        size_t copyLen = std::min(static_cast<size_t>(event.data_len), sizeof(lastPayload) - 1);
        memcpy(lastPayload, event.data, copyLen);
        lastPayload[copyLen] = '\0';
        pendingCommand = true;
        Serial.printf("Topic: %.*s\n", event.topic_len, event.topic);
        Serial.printf("Payload: %s\n", lastPayload);
      }
      break;
    default:
      break;
  }
}

void connectWifi()
{
  WiFi.begin(kSsid, kPassword);
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
  pinMode(LED_BUILTIN, OUTPUT);
  connectWifi();

  esp_mqtt_client_config_t config = {};
  config.broker.address.uri = "mqtt://broker.emqx.io";
  config.credentials.client_id = "EspHelperSubscriber";

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
  if (pendingCommand)
  {
    pendingCommand = false;
    if (strcmp(lastPayload, "on") == 0)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      mqtt.publish("esphelper/command/echo", "LED ON", 1);
    }
    else if (strcmp(lastPayload, "off") == 0)
    {
      digitalWrite(LED_BUILTIN, LOW);
      mqtt.publish("esphelper/command/echo", "LED OFF", 1);
    }
    else
    {
      mqtt.publish("esphelper/command/echo", "UNKNOWN", 1);
    }
  }
}
