#include <EspHelperQueue.h>

EspHelper::Queue<int> queue;
EspHelper::Task producer;
EspHelper::Task consumer;

void setup()
{
  Serial.begin(115200);
  queue.create(5);

  producer.start("Producer", [] {
    int value = 0;
    while (true)
    {
      queue.send(++value);
      Serial.printf("Produced %d\n", value);
      delay(500);
    }
  });

  consumer.start("Consumer", [] {
    int received;
    while (true)
    {
      if (queue.receive(received, 1000))
      {
        Serial.printf("Consumed %d\n", received);
      }
    }
  });
}

void loop()
{
}
