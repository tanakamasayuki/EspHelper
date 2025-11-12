#include <EspHelperRingbuf.h>

EspHelper::Ringbuffer ringbuf(256, RINGBUF_TYPE_BYTEBUF);
uint32_t counter = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Ringbuffer byte-buffer example");
}

void loop()
{
  char message[64];
  size_t len = snprintf(message, sizeof(message), "msg=%lu millis=%lu", static_cast<unsigned long>(counter++),
                        static_cast<unsigned long>(millis()));
  ringbuf.send(message, len);

  while (true)
  {
    auto item = ringbuf.receive(0);
    if (!item.valid())
    {
      break;
    }
    Serial.print("Received size=");
    Serial.print(item.size());
    Serial.print(" data=");
    Serial.write(item.data(), item.size());
    Serial.println();
    // item destructor returns buffer automatically
  }

  delay(500);
}
