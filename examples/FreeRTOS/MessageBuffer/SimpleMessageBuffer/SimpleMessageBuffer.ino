#include <EspHelperMessageBuffer.h>
#include <EspHelperTask.h>

constexpr size_t kMessageBufferBytes = 128;

EspHelper::MessageBuffer messageBuffer;
EspHelper::Task senderTask;
EspHelper::Task receiverTask;

void setup()
{
  Serial.begin(115200);
  messageBuffer.create(kMessageBufferBytes);

  senderTask.start("MsgSender",
                   []
                   {
                     uint32_t counter = 0;
                     while (true)
                     {
                       char payload[32];
                       snprintf(payload, sizeof(payload), "event:%lu", ++counter);
                       messageBuffer.send(payload, strlen(payload) + 1);
                       Serial.printf("[sender] queued %s (free %u bytes)\n", payload,
                                     static_cast<unsigned>(messageBuffer.spaceAvailable()));
                       delay(700);
                     }
                   });

  receiverTask.start("MsgReceiver",
                     []
                     {
                       char buffer[32];
                       while (true)
                       {
                         size_t received = messageBuffer.receive(buffer, sizeof(buffer), 1000);
                         if (received > 0)
                         {
                           Serial.printf("[receiver] got %s (%u bytes, next message %u bytes)\n", buffer,
                                         static_cast<unsigned>(received),
                                         static_cast<unsigned>(messageBuffer.nextMessageSize()));
                         }
                       }
                     });
}

void loop()
{
}
