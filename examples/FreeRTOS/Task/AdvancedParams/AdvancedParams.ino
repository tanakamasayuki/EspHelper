// en: Configure task parameters and lambda entry points
// ja: タスクの設定とラムダの入口を指定する
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

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  pinnedTask.start("PinnedFunc",
                   pinnedFunction,
                   4096,         // stack size in bytes
                   3,            // priority
                   PRO_CPU_NUM); // run on core 0

  lambdaTask.start("LambdaTask", []
                   {
                     uint32_t counter = 0;
                     while (true)
                     {
                       Serial.printf("Lambda count=%lu\n", counter++);
                       delay(500);
                     } },
                   6144,         // larger stack for this lambda
                   2,            // priority
                   APP_CPU_NUM); // run on core 1
}

void loop()
{
}
