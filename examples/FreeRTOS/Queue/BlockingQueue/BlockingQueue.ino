#include <EspHelperQueue.h>
#include <EspHelperTask.h>

EspHelper::Queue<int> queue;
EspHelper::Task producer;
EspHelper::Task blockingConsumer;

void setup()
{
  Serial.begin(115200);
  queue.create(1);  // keep it small so the producer also blocks when the consumer is slow

  producer.start("BlockingProducer",
                 []
                 {
                   int value = 0;
                   while (true)
                   {
                     queue.send(++value, portMAX_DELAY);
                     Serial.printf("[blocking] sent %d\n", value);
                     delay(1200);
                   }
                 });

  blockingConsumer.start("BlockingConsumer",
                          []
                          {
                            int received;
                            while (true)
                            {
                              queue.receive(received, portMAX_DELAY);
                              Serial.printf("[blocking] received %d\n", received);
                              delay(2000);  // deliberately slower than producer to show blocking behavior
                            }
                          });
}

void loop()
{
}
