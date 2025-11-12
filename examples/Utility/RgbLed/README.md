# RgbLed Examples

[日本語はこちら](README.ja.md)

`EspHelper::RgbStrip` offers a blocking, minimal wrapper over the built-in `rgbLedWrite(pin, r, g, b)` helper in the Arduino-ESP32 core. Provide the single data pin and LED count in the constructor; the class stores per-pixel colors, applies a global brightness, and sequentially invokes `rgbLedWrite()` with a short pause, giving you a tiny Adafruit_NeoPixel-style API without DMA or background tasks.

## Key points
- Pass the data pin and LED count in the constructor; the class stores per-pixel colors and writes them sequentially with a configurable inter-pixel delay (default ~50 µs).
- `setPixelColor()` buffers colors, `show()` pushes every pin (blocking until finished). Use `fill()`/`clear()` for bulk updates.
- Global brightness and per-show timing are adjustable; no tasks or interrupts are involved, so behavior is deterministic.

## Examples
- `SimpleStrip/SimpleStrip.ino` – single RGB LED cycling through red/green/blue on pin 2.
- `MultiStrip/MultiStrip.ino` – three discrete RGB LEDs connected to pins 2/4/5 with color wipe and fill effects.
