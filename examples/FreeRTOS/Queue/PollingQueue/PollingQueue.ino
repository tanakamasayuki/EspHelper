#include <EspHelperQueue.h>
#include <EspHelperTask.h>

EspHelper::Queue<int> queue;
EspHelper::Task producer;
EspHelper::Task pollingConsumer;

void setup()
{
  Serial.begin(115200);
  queue.create(5);

  producer.start("PollProducer",
                 []
                 {
                   int value = 100;
                   while (true)
                   {
                     queue.send(value++);
                     delay(700);
                   }
                 });

  pollingConsumer.start("PollConsumer",
                        []
                        {
                          int received;
                          while (true)
                          {
                            if (queue.receive(received, 0))
                            {
                              Serial.printf("[poll] got %d\n", received);
                            }
                            else
                            {
                              Serial.println("[poll] no data, doing other work...");
                              delay(200);
                            }
                          }
                        });
}

void loop()
{
}
