#include <EspHelperQueue.h>
#include <EspHelperTask.h>

EspHelper::Queue<const char *> queue;
EspHelper::Task producer;
EspHelper::Task timeoutConsumer;

void setup()
{
  Serial.begin(115200);
  queue.create(3);

  producer.start("SlowProducer",
                 []
                 {
                   const char *messages[] = {"one", "two", "three"};
                   size_t index = 0;
                   while (true)
                   {
                     queue.send(messages[index]);
                     index = (index + 1) % 3;
                     delay(1500); // intentionally slow so the consumer times out sometimes
                   }
                 });

  timeoutConsumer.start("TimeoutConsumer",
                        []
                        {
                          const TickType_t waitTicks = 750; // milliseconds in Arduino builds
                          const uint32_t waitMs = 750;
                          const char *msg = nullptr;
                          while (true)
                          {
                            if (queue.receive(msg, waitTicks))
                            {
                              Serial.printf("[timeout] received: %s\n", msg);
                            }
                            else
                            {
                              Serial.printf("[timeout] waited %lu ms, no message\n", waitMs);
                            }
                          }
                        });
}

void loop()
{
}
