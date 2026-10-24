# EspHelper examples

> 日本語版: [README.ja.md](README.ja.md)

## Workflow and individual READMEs

Start with the [example workflow](../docs/GUIDE_EXAMPLES.md), then choose the relevant sketch.

A useful starting point is [Info/BoardSettings](Info/BoardSettings/README.md). Check its required hardware and choose another entry below if it does not match your setup.

| Example | Learn |
|---|---|
| [Display/Lcd/SimpleGradient](Display/Lcd/SimpleGradient/README.md) | Draw a gradient through the configured LCD wrapper |
| [Display/Lcd/Ssd1306Checker](Display/Lcd/Ssd1306Checker/README.md) | Draw a checker pattern on an SSD1306 display |
| [Display/RgbStrip/MultiStrip](Display/RgbStrip/MultiStrip/README.md) | Update two separately configured RGB strips |
| [Display/RgbStrip/SimpleStrip](Display/RgbStrip/SimpleStrip/README.md) | Set pixel colors and transfer them to an RGB strip |
| [FreeRTOS/MessageBuffer/SimpleMessageBuffer](FreeRTOS/MessageBuffer/SimpleMessageBuffer/README.md) | Transfer whole messages through a message buffer |
| [FreeRTOS/Mutex/BlockingMutex](FreeRTOS/Mutex/BlockingMutex/README.md) | Wait for exclusive access to a shared resource |
| [FreeRTOS/Mutex/SimpleMutex](FreeRTOS/Mutex/SimpleMutex/README.md) | Serialize shared writes with a mutex |
| [FreeRTOS/Mutex/TryLock](FreeRTOS/Mutex/TryLock/README.md) | Handle immediate mutex acquisition or rejection |
| [FreeRTOS/Queue/BlockingQueue](FreeRTOS/Queue/BlockingQueue/README.md) | Wait until a queued item arrives |
| [FreeRTOS/Queue/PollingQueue](FreeRTOS/Queue/PollingQueue/README.md) | Check a queue without waiting |
| [FreeRTOS/Queue/SimpleQueue](FreeRTOS/Queue/SimpleQueue/README.md) | Copy values between a producer and consumer |
| [FreeRTOS/Queue/TimeoutQueue](FreeRTOS/Queue/TimeoutQueue/README.md) | Handle a receive timeout without using stale data |
| [FreeRTOS/Ringbuf/ByteBuffer](FreeRTOS/Ringbuf/ByteBuffer/README.md) | Receive a scoped view of ring-buffered bytes |
| [FreeRTOS/Ringbuf/FixedStruct](FreeRTOS/Ringbuf/FixedStruct/README.md) | Transfer a fixed structure using a no-split ring buffer |
| [FreeRTOS/Semaphore/Binary](FreeRTOS/Semaphore/Binary/README.md) | Coordinate tasks using a single pending signal |
| [FreeRTOS/Semaphore/Counting](FreeRTOS/Semaphore/Counting/README.md) | Limit available work slots with a counting semaphore |
| [FreeRTOS/Semaphore/IsrSignal](FreeRTOS/Semaphore/IsrSignal/README.md) | Signal a task from a hardware timer interrupt |
| [FreeRTOS/StreamBuffer/SimpleStreamBuffer](FreeRTOS/StreamBuffer/SimpleStreamBuffer/README.md) | Exchange byte chunks through a stream buffer |
| [FreeRTOS/Task/AdvancedParams](FreeRTOS/Task/AdvancedParams/README.md) | Configure task parameters and lambda entry points |
| [FreeRTOS/Task/SimpleTask](FreeRTOS/Task/SimpleTask/README.md) | Start a simple worker task |
| [Info/BoardSettings](Info/BoardSettings/README.md) | Print the selected board settings |
| [JSON/CJson/BuildAndParse](JSON/CJson/BuildAndParse/README.md) | Build a JSON object and parse its fields |
| [JSON/Cbor/DecodeStatus](JSON/Cbor/DecodeStatus/README.md) | Decode fields from a CBOR status map |
| [JSON/Cbor/EncodeStatus](JSON/Cbor/EncodeStatus/README.md) | Encode a status map into a bounded CBOR buffer |
| [JSON/JsonGenerator/AllFunctions](JSON/JsonGenerator/AllFunctions/README.md) | Exercise JSON object, array and streaming generation |
| [JSON/JsonGenerator/StaticJsonBuffer](JSON/JsonGenerator/StaticJsonBuffer/README.md) | Generate JSON into caller-owned fixed storage |
| [JSON/JsonGenerator/StreamingToSerial](JSON/JsonGenerator/StreamingToSerial/README.md) | Write generated JSON directly to Serial |
| [JSON/JsonParser/BasicParse](JSON/JsonParser/BasicParse/README.md) | Navigate and read JSON object and array values |
| [Network/HttpServer/SimpleServer](Network/HttpServer/SimpleServer/README.md) | Handle GET and POST through the HTTP wrapper |
| [Network/Mqtt/BasicPublish](Network/Mqtt/BasicPublish/README.md) | Publish a value after connecting to an MQTT broker |
| [Network/Mqtt/SubscribeEcho](Network/Mqtt/SubscribeEcho/README.md) | Subscribe and echo MQTT message events |
| [Utility/Dsp/FftSpectrum](Utility/Dsp/FftSpectrum/README.md) | Compute a spectrum from a synthetic sampled signal |
| [Utility/Dsp/FirSmoothing](Utility/Dsp/FirSmoothing/README.md) | Smooth a sample sequence with an FIR filter |
| [Utility/Event/CustomLoop](Utility/Event/CustomLoop/README.md) | Post data to a separately created event loop |
| [Utility/Event/DefaultLoop](Utility/Event/DefaultLoop/README.md) | Register and post on the default event loop |
| [Utility/QrCode/AsciiConsole](Utility/QrCode/AsciiConsole/README.md) | Encode a QR code and print it as console art |
| [Utility/QrCode/M5Display](Utility/QrCode/M5Display/README.md) | Render generated QR modules on an M5 display |
| [Utility/Sodium/RandomHex](Utility/Sodium/RandomHex/README.md) | Generate random bytes and print their hexadecimal form |
| [Utility/Sodium/SecretBox](Utility/Sodium/SecretBox/README.md) | Encrypt and authenticate a message with SecretBox |
