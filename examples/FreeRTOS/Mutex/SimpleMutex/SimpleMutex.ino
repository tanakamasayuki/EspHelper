// en: Serialize shared writes with a mutex
// ja: Mutexで共有領域への書き込みを直列化する
#include <EspHelperMutex.h>
#include <EspHelperTask.h>

EspHelper::Mutex mutex;
EspHelper::Task writerA;
EspHelper::Task writerB;
int sharedValue = 0;

void setup()
{
  Serial.begin(115200);
  // en: Allocate/create the resource before any task or callback relies on it; handle creation failure.
  // ja: タスクやコールバックが使う前に資源を作り、生成失敗にも対応します。
  mutex.create();

  // en: Start work using the configured entry point; the context and objects must remain valid while it runs.
  // ja: 設定した入口から処理を開始します。実行中はコンテキストとオブジェクトの寿命を保ちます。
  writerA.start("WriterA", []
                {
    while (true)
    {
      // en: Acquire exclusive ownership before shared access; respect this wrapper’s timeout unit.
      // ja: 共有領域を使う前に排他権を取得し、このラッパーの待ち時間単位に合わせます。
      if (mutex.lock(100))
      {
        ++sharedValue;
        Serial.printf("WriterA value=%d\n", sharedValue);
        mutex.unlock();
      }
      delay(200);
    } });

  writerB.start("WriterB", []
                {
    while (true)
    {
      if (mutex.lock(100))
      {
        sharedValue += 2;
        Serial.printf("WriterB value=%d\n", sharedValue);
        mutex.unlock();
      }
      delay(250);
    } });
}

void loop()
{
}
