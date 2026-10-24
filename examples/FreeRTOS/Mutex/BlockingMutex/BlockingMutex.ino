// en: Wait for exclusive access to a shared resource
// ja: 共有資源を排他的に使うためLockを待つ
#include <EspHelperMutex.h>
#include <EspHelperTask.h>

EspHelper::Mutex mutex;
EspHelper::Task loggerTask;
EspHelper::Task sensorTask;
char lastMessage[64] = {0};

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  mutex.create();

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  sensorTask.start("SensorTask",
                   []
                   {
                     uint32_t counter = 0;
                     while (true)
                     {
                       // en: Acquire exclusive ownership before shared access; respect this wrapper’s timeout unit.
                       // ja: 共有領域を使う前に排他権を取得し、このラッパーの待ち時間単位に合わせます。
                       if (mutex.lock(portMAX_DELAY))
                       {
                         snprintf(lastMessage, sizeof(lastMessage), "sensor reading %lu", ++counter);
                         delay(300); // pretend measurement time
                         mutex.unlock();
                       }
                       delay(100);
                     }
                   });

  loggerTask.start("LoggerTask",
                   []
                   {
                     while (true)
                     {
                       if (mutex.lock(portMAX_DELAY))
                       {
                         Serial.printf("[logger] %s\n", lastMessage);
                         delay(150);
                         mutex.unlock();
                       }
                       delay(200);
                     }
                   });
}

void loop()
{
}
