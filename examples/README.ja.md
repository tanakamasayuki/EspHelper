# EspHelper サンプル

> English: [README.md](README.md)

## 実行ガイドと個別README

最初に[サンプル入門ガイド](../docs/GUIDE_EXAMPLES.ja.md)を読み、目的に合う例へ進んでください。

最初の候補は[Info/BoardSettings](Info/BoardSettings/README.ja.md)です。必要な機器を確認し、対象が異なる場合は下の一覧から選び直してください。

| 例 | 学ぶこと |
|---|---|
| [Display/Lcd/SimpleGradient](Display/Lcd/SimpleGradient/README.ja.md) | 設定したLCDラッパーでグラデーションを描く |
| [Display/Lcd/Ssd1306Checker](Display/Lcd/Ssd1306Checker/README.ja.md) | SSD1306へ市松模様を描く |
| [Display/RgbStrip/MultiStrip](Display/RgbStrip/MultiStrip/README.ja.md) | 別々に設定した2本のRGB Stripを更新する |
| [Display/RgbStrip/SimpleStrip](Display/RgbStrip/SimpleStrip/README.ja.md) | RGB Stripの色を設定して実機へ転送する |
| [FreeRTOS/MessageBuffer/SimpleMessageBuffer](FreeRTOS/MessageBuffer/SimpleMessageBuffer/README.ja.md) | MessageBufferでメッセージ単位のデータを渡す |
| [FreeRTOS/Mutex/BlockingMutex](FreeRTOS/Mutex/BlockingMutex/README.ja.md) | 共有資源を排他的に使うためLockを待つ |
| [FreeRTOS/Mutex/SimpleMutex](FreeRTOS/Mutex/SimpleMutex/README.ja.md) | Mutexで共有領域への書き込みを直列化する |
| [FreeRTOS/Mutex/TryLock](FreeRTOS/Mutex/TryLock/README.ja.md) | 待たないMutex取得の成功と失敗を扱う |
| [FreeRTOS/Queue/BlockingQueue](FreeRTOS/Queue/BlockingQueue/README.ja.md) | Queueの要素が届くまで待つ |
| [FreeRTOS/Queue/PollingQueue](FreeRTOS/Queue/PollingQueue/README.ja.md) | Queueを待機せずに確認する |
| [FreeRTOS/Queue/SimpleQueue](FreeRTOS/Queue/SimpleQueue/README.ja.md) | 生成側と受信側で値をコピーして受け渡す |
| [FreeRTOS/Queue/TimeoutQueue](FreeRTOS/Queue/TimeoutQueue/README.ja.md) | Receiveの時間切れを検出し、古い値を使わない |
| [FreeRTOS/Ringbuf/ByteBuffer](FreeRTOS/Ringbuf/ByteBuffer/README.ja.md) | Ringbufferのバイト列を寿命付きviewで受け取る |
| [FreeRTOS/Ringbuf/FixedStruct](FreeRTOS/Ringbuf/FixedStruct/README.ja.md) | 分割しないRingbufferで固定構造体を渡す |
| [FreeRTOS/Semaphore/Binary](FreeRTOS/Semaphore/Binary/README.ja.md) | 最大1件の保留信号でタスクを同期する |
| [FreeRTOS/Semaphore/Counting](FreeRTOS/Semaphore/Counting/README.ja.md) | Counting Semaphoreで利用可能な枠を管理する |
| [FreeRTOS/Semaphore/IsrSignal](FreeRTOS/Semaphore/IsrSignal/README.ja.md) | Hardware Timer割り込みからタスクへ合図する |
| [FreeRTOS/StreamBuffer/SimpleStreamBuffer](FreeRTOS/StreamBuffer/SimpleStreamBuffer/README.ja.md) | StreamBufferでバイト列を受け渡す |
| [FreeRTOS/Task/AdvancedParams](FreeRTOS/Task/AdvancedParams/README.ja.md) | タスクの設定とラムダの入口を指定する |
| [FreeRTOS/Task/SimpleTask](FreeRTOS/Task/SimpleTask/README.ja.md) | 単純なWorkerタスクを開始する |
| [Info/BoardSettings](Info/BoardSettings/README.ja.md) | 選択したボードの設定を表示する |
| [JSON/CJson/BuildAndParse](JSON/CJson/BuildAndParse/README.ja.md) | JSON Objectを作って項目を解析する |
| [JSON/Cbor/DecodeStatus](JSON/Cbor/DecodeStatus/README.ja.md) | CBORの状態Mapから項目を読み出す |
| [JSON/Cbor/EncodeStatus](JSON/Cbor/EncodeStatus/README.ja.md) | 容量付きバッファへ状態をCBORで書き込む |
| [JSON/JsonGenerator/AllFunctions](JSON/JsonGenerator/AllFunctions/README.ja.md) | JSONのObject・Array・Stream出力を試す |
| [JSON/JsonGenerator/StaticJsonBuffer](JSON/JsonGenerator/StaticJsonBuffer/README.ja.md) | 自分で用意した固定領域へJSONを生成する |
| [JSON/JsonGenerator/StreamingToSerial](JSON/JsonGenerator/StreamingToSerial/README.ja.md) | 生成するJSONをSerialへ直接出力する |
| [JSON/JsonParser/BasicParse](JSON/JsonParser/BasicParse/README.ja.md) | JSONのObjectとArrayへ移動して値を読む |
| [Network/HttpServer/SimpleServer](Network/HttpServer/SimpleServer/README.ja.md) | HTTPラッパーでGETとPOSTを処理する |
| [Network/Mqtt/BasicPublish](Network/Mqtt/BasicPublish/README.ja.md) | MQTT Brokerへ接続して値をPublishする |
| [Network/Mqtt/SubscribeEcho](Network/Mqtt/SubscribeEcho/README.ja.md) | MQTTを購読し受信イベントから応答する |
| [Utility/Dsp/FftSpectrum](Utility/Dsp/FftSpectrum/README.ja.md) | 模擬サンプル信号からSpectrumを計算する |
| [Utility/Dsp/FirSmoothing](Utility/Dsp/FirSmoothing/README.ja.md) | FIR Filterでサンプル列を平滑化する |
| [Utility/Event/CustomLoop](Utility/Event/CustomLoop/README.ja.md) | 別に作ったEvent Loopへデータを送る |
| [Utility/Event/DefaultLoop](Utility/Event/DefaultLoop/README.ja.md) | 既定Event LoopへHandler登録とPostを行う |
| [Utility/QrCode/AsciiConsole](Utility/QrCode/AsciiConsole/README.ja.md) | QRを符号化してConsoleの文字で表示する |
| [Utility/QrCode/M5Display](Utility/QrCode/M5Display/README.ja.md) | 生成したQRモジュールをM5画面へ描く |
| [Utility/Sodium/RandomHex](Utility/Sodium/RandomHex/README.ja.md) | 乱数のバイト列を生成し16進数で表示する |
| [Utility/Sodium/SecretBox](Utility/Sodium/SecretBox/README.ja.md) | SecretBoxでメッセージを暗号化・認証する |
