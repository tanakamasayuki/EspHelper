#include <EspHelperTask.h>

EspHelper::Task pinnedTask;
EspHelper::Task lambdaTask;

void pinnedFunction()
{
  while (true)
  {
    Serial.printf("Pinned task running on core %d\n", xPortGetCoreID());
    delay(1000);
  }
}

void setup()
{
  Serial.begin(115200);

  pinnedTask.start("PinnedFunc",
                   pinnedFunction,
                   4096, // stack size in bytes
                   3,    // priority
                   PRO_CPU_NUM);   // run on core 0

  lambdaTask.start("LambdaTask", []
                   {
                     uint32_t counter = 0;
                     while (true)
                     {
                       Serial.printf("Lambda count=%lu\n", counter++);
                       delay(500);
                     } },
                   6144, // larger stack for this lambda
                   2,    // priority
                   APP_CPU_NUM);   // run on core 1
}

void loop()
{
}
