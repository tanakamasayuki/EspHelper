// en: Handle immediate mutex acquisition or rejection
// ja: 待たないMutex取得の成功と失敗を扱う
#include <EspHelperMutex.h>
#include <EspHelperTask.h>

EspHelper::Mutex mutex;
EspHelper::Task fastTask;
EspHelper::Task slowTask;
int sharedValue = 0;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  mutex.create();

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  slowTask.start("SlowTask",
                 []
                 {
                   while (true)
                   {
                     // en: Acquire exclusive ownership before shared access; respect this wrapper’s timeout unit.
                     // ja: 共有領域を使う前に排他権を取得し、このラッパーの待ち時間単位に合わせます。
                     if (mutex.lock(portMAX_DELAY))
                     {
                       Serial.println("SlowTask entered critical section");
                       delay(600);
                       ++sharedValue;
                       Serial.printf("SlowTask value=%d\n", sharedValue);
                       mutex.unlock();
                     }
                     delay(100);
                   }
                 });

  fastTask.start("FastTask",
                 []
                 {
                   while (true)
                   {
                     if (mutex.lock(0))
                     {
                       --sharedValue;
                       Serial.printf("FastTask value=%d\n", sharedValue);
                       delay(50);
                       mutex.unlock();
                     }
                     else
                     {
                       Serial.println("FastTask skipping work (mutex busy)");
                     }
                     delay(100);
                   }
                 });
}

void loop()
{
}
