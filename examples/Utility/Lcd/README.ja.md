# Lcd サンプル

[English README](README.md)

`EspHelperLcd.h` は `esp_lcd` の提供する ST7789 (SPI) と SSD1306 (I2C) をArduino風に初期化・描画できるラッパーです。バス設定やパネル生成をまとめ、`drawBitmap` や `fillScreen` などの操作を提供します。

## API概要 (St7789Panel)
- `begin(cfg)` – SPIピン、解像度、オフセット、バックライトGPIOなどを指定して初期化。
- `end()` – パネル/IO/SPIバスを解放。
- `drawBitmap(x, y, width, height, pixels)` – RGB565ピクセルを描画。
- `drawPixel(x, y, color)` – 単一ピクセル描画。
- `fillScreen(color)` – 内部バッファを使って画面全体を塗りつぶし。
- `setBacklight(on)` – バックライトGPIOを制御（設定されている場合）。

## 収録スケッチ
- `SimpleGradient/SimpleGradient.ino` – ST7789を初期化し、1ラインずつグラデーションを描画する最小例。
- `Ssd1306Checker/Ssd1306Checker.ino` – SSD1306をI2Cで初期化し、チェッカー模様を描画する例。
