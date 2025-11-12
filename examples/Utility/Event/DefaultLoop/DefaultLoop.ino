#include <EspHelperEvent.h>

ESP_EVENT_DECLARE_BASE(APP_EVENT_BASE);
ESP_EVENT_DEFINE_BASE(APP_EVENT_BASE);

enum : int32_t
{
  APP_EVENT_TICK = 0,
  APP_EVENT_MESSAGE = 1,
};

struct MessageEvent
{
  uint32_t counter;
  char text[24];
};

EspHelper::EventLoop eventLoop;
esp_event_handler_instance_t tickInstance = nullptr;
uint32_t tickCount = 0;
uint32_t messageCount = 0;
unsigned long lastPost = 0;

void onTick(void *, esp_event_base_t, int32_t, void *)
{
  Serial.printf("[default] tick #%lu on core %d\n", ++tickCount, xPortGetCoreID());
}

void onMessage(void *, esp_event_base_t, int32_t, void *event_data)
{
  const MessageEvent *msg = static_cast<const MessageEvent *>(event_data);
  Serial.printf("[default] message %lu: %s\n", msg->counter, msg->text);
}

void setup()
{
  Serial.begin(115200);
  if (!eventLoop.createDefault())
  {
    Serial.println("Failed to create default event loop");
    while (true)
    {
      delay(1000);
    }
  }

  eventLoop.registerHandler(APP_EVENT_BASE, APP_EVENT_TICK, &onTick, nullptr, &tickInstance);
  eventLoop.registerHandler(APP_EVENT_BASE, APP_EVENT_MESSAGE, &onMessage);
}

void loop()
{
  const unsigned long now = millis();
  if (now - lastPost >= 1000)
  {
    lastPost = now;
    eventLoop.post(APP_EVENT_BASE, APP_EVENT_TICK);

    MessageEvent msg{};
    msg.counter = ++messageCount;
    snprintf(msg.text, sizeof(msg.text), "uptime %lus", now / 1000UL);
    eventLoop.post(APP_EVENT_BASE, APP_EVENT_MESSAGE, &msg, sizeof(msg));
  }
}
