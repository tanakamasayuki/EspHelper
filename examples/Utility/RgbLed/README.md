# RgbLed Examples

[日本語はこちら](README.ja.md)

`EspHelper::RgbStrip` offers a blocking, minimal wrapper over the built-in `rgbLedWrite(pin, r, g, b)` helper in the Arduino-ESP32 core. Provide the single data pin and LED count in the constructor; the class stores per-pixel colors, applies a global brightness, and sequentially invokes `rgbLedWrite()` with a short pause, giving you a tiny Adafruit_NeoPixel-style API without DMA or background tasks.

## API Reference
- `RgbStrip(uint8_t pin, size_t ledCount, uint8_t brightness = 255, uint32_t interPixelDelayUs = 50)`
- `size_t size() const`
- `void setBrightness(uint8_t value)`
- `void setInterPixelDelay(uint32_t micros)`
- `void setPixelColor(size_t index, uint8_t r, uint8_t g, uint8_t b)` / `setPixelColor(size_t index, uint32_t packed)`
- `void fill(uint8_t r, uint8_t g, uint8_t b)` / `fill(uint32_t packed)`
- `void clear()`
- `void show()`

### Named Colors (`EspHelper::RgbColor`)
| Name | Constant | Hex | Description |
|------|----------|-----|-------------|
| Black | `EspHelper::RgbColor::Black` | `0x000000` | Off |
| White | `EspHelper::RgbColor::White` | `0xFFFFFF` | Full white |
| Red | `EspHelper::RgbColor::Red` | `0xFF0000` | Pure red |
| Green | `EspHelper::RgbColor::Green` | `0x00FF00` | Pure green |
| Blue | `EspHelper::RgbColor::Blue` | `0x0000FF` | Pure blue |
| Cyan | `EspHelper::RgbColor::Cyan` | `0x00FFFF` | Cyan |
| Magenta | `EspHelper::RgbColor::Magenta` | `0xFF00FF` | Magenta |
| Yellow | `EspHelper::RgbColor::Yellow` | `0xFFFF00` | Yellow |
| Orange | `EspHelper::RgbColor::Orange` | `0xFF7F00` | Orange |
| Purple | `EspHelper::RgbColor::Purple` | `0x8000FF` | Purple |
| Pink | `EspHelper::RgbColor::Pink` | `0xFF1493` | Pink |
| Lime | `EspHelper::RgbColor::Lime` | `0x32CD32` | Lime |
| Teal | `EspHelper::RgbColor::Teal` | `0x008080` | Teal |
| Navy | `EspHelper::RgbColor::Navy` | `0x000080` | Navy |
| Maroon | `EspHelper::RgbColor::Maroon` | `0x800000` | Maroon |
| Olive | `EspHelper::RgbColor::Olive` | `0x808000` | Olive |
| Gold | `EspHelper::RgbColor::Gold` | `0xFFD700` | Gold |
| Silver | `EspHelper::RgbColor::Silver` | `0xC0C0C0` | Silver |

## Examples
- `SimpleStrip/SimpleStrip.ino` – single RGB LED cycling through red/green/blue on pin 2.
- `MultiStrip/MultiStrip.ino` – two different strips (pins 2 and 4) demonstrating color wipes and fill effects.
