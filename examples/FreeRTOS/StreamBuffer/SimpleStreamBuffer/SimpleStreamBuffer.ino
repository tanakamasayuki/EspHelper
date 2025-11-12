#include <EspHelperStreamBuffer.h>
#include <EspHelperTask.h>

constexpr size_t kStreamCapacity = 64;

EspHelper::StreamBuffer streamBuffer;
EspHelper::Task producerTask;
EspHelper::Task consumerTask;

void setup()
{
  Serial.begin(115200);
  streamBuffer.create(kStreamCapacity);

  producerTask.start("StreamWriter",
                     []
                     {
                       const char *chunk = "temp=24.8C;";
                       while (true)
                       {
                         streamBuffer.send(chunk, strlen(chunk));
                         Serial.println("[writer] chunk queued");
                         delay(300);
                       }
                     });

  consumerTask.start("StreamReader",
                     []
                     {
                       char buffer[32];
                       while (true)
                       {
                         size_t received = streamBuffer.receive(buffer, sizeof(buffer) - 1, 1000);
                         if (received > 0)
                         {
                           buffer[received] = '\0';
                           Serial.printf("[reader] %s (pending %u bytes)\n", buffer,
                                         static_cast<unsigned>(streamBuffer.bytesAvailable()));
                         }
                       }
                     });
}

void loop()
{
}
