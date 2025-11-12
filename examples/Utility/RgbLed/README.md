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
| Name | Constant | Hex | Swatch | Description |
|------|----------|-----|--------|-------------|
| Black | `EspHelper::RgbColor::Black` | `0x000000` | <span style="display:inline-block;width:32px;height:12px;background:#000000;border:1px solid #ddd;"></span> | Off |
| White | `EspHelper::RgbColor::White` | `0xFFFFFF` | <span style="display:inline-block;width:32px;height:12px;background:#FFFFFF;border:1px solid #ddd;"></span> | Full white |
| Red | `EspHelper::RgbColor::Red` | `0xFF0000` | <span style="display:inline-block;width:32px;height:12px;background:#FF0000;border:1px solid #ddd;"></span> | Pure red |
| Green | `EspHelper::RgbColor::Green` | `0x00FF00` | <span style="display:inline-block;width:32px;height:12px;background:#00FF00;border:1px solid #ddd;"></span> | Pure green |
| Blue | `EspHelper::RgbColor::Blue` | `0x0000FF` | <span style="display:inline-block;width:32px;height:12px;background:#0000FF;border:1px solid #ddd;"></span> | Pure blue |
| Cyan | `EspHelper::RgbColor::Cyan` | `0x00FFFF` | <span style="display:inline-block;width:32px;height:12px;background:#00FFFF;border:1px solid #ddd;"></span> | Cyan |
| Magenta | `EspHelper::RgbColor::Magenta` | `0xFF00FF` | <span style="display:inline-block;width:32px;height:12px;background:#FF00FF;border:1px solid #ddd;"></span> | Magenta |
| Yellow | `EspHelper::RgbColor::Yellow` | `0xFFFF00` | <span style="display:inline-block;width:32px;height:12px;background:#FFFF00;border:1px solid #ddd;"></span> | Yellow |
| Orange | `EspHelper::RgbColor::Orange` | `0xFF7F00` | <span style="display:inline-block;width:32px;height:12px;background:#FF7F00;border:1px solid #ddd;"></span> | Orange |
| Purple | `EspHelper::RgbColor::Purple` | `0x8000FF` | <span style="display:inline-block;width:32px;height:12px;background:#8000FF;border:1px solid #ddd;"></span> | Purple |
| Pink | `EspHelper::RgbColor::Pink` | `0xFF1493` | <span style="display:inline-block;width:32px;height:12px;background:#FF1493;border:1px solid #ddd;"></span> | Pink |
| Lime | `EspHelper::RgbColor::Lime` | `0x32CD32` | <span style="display:inline-block;width:32px;height:12px;background:#32CD32;border:1px solid #ddd;"></span> | Lime |
| Teal | `EspHelper::RgbColor::Teal` | `0x008080` | <span style="display:inline-block;width:32px;height:12px;background:#008080;border:1px solid #ddd;"></span> | Teal |
| Navy | `EspHelper::RgbColor::Navy` | `0x000080` | <span style="display:inline-block;width:32px;height:12px;background:#000080;border:1px solid #ddd;"></span> | Navy |
| Maroon | `EspHelper::RgbColor::Maroon` | `0x800000` | <span style="display:inline-block;width:32px;height:12px;background:#800000;border:1px solid #ddd;"></span> | Maroon |
| Olive | `EspHelper::RgbColor::Olive` | `0x808000` | <span style="display:inline-block;width:32px;height:12px;background:#808000;border:1px solid #ddd;"></span> | Olive |
| Gold | `EspHelper::RgbColor::Gold` | `0xFFD700` | <span style="display:inline-block;width:32px;height:12px;background:#FFD700;border:1px solid #ddd;"></span> | Gold |
| Silver | `EspHelper::RgbColor::Silver` | `0xC0C0C0` | <span style="display:inline-block;width:32px;height:12px;background:#C0C0C0;border:1px solid #ddd;"></span> | Silver |

## Examples
- `SimpleStrip/SimpleStrip.ino` – single RGB LED cycling through red/green/blue on pin 2.
- `MultiStrip/MultiStrip.ino` – two different strips (pins 2 and 4) demonstrating color wipes and fill effects.
