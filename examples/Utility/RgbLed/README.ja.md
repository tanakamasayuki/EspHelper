# RgbLed サンプル

[English README](README.md)

`EspHelper::RgbStrip` は Arduino-ESP32 コアの `rgbLedWrite(pin, r, g, b)` を順次呼び出して、1本のデータピンに直列接続されたストリップLEDを制御する簡易ラッパーです。

## APIリファレンス
- `RgbStrip(pin, ledCount, brightness=255, interPixelDelayUs=50)`
- `size()`
- `setBrightness()`
- `setInterPixelDelay()`
- `setPixelColor(index, r, g, b)` / `setPixelColor(index, packed)`
- `fill(r, g, b)` / `fill(packed)`
- `clear()`
- `show()`

### `EspHelper::RgbColor` の定義
| 名前 | 定数 | Hex値 | 色サンプル | 説明 |
|------|------|-------|----------|------|
| Black | `EspHelper::RgbColor::Black` | `0x000000` | ![Black](assets/black.png) | 消灯 |
| White | `EspHelper::RgbColor::White` | `0xFFFFFF` | ![White](assets/white.png) | 白 |
| Red | `EspHelper::RgbColor::Red` | `0xFF0000` | ![Red](assets/red.png) | 赤 |
| Green | `EspHelper::RgbColor::Green` | `0x00FF00` | ![Green](assets/green.png) | 緑 |
| Blue | `EspHelper::RgbColor::Blue` | `0x0000FF` | ![Blue](assets/blue.png) | 青 |
| Cyan | `EspHelper::RgbColor::Cyan` | `0x00FFFF` | ![Cyan](assets/cyan.png) | シアン |
| Magenta | `EspHelper::RgbColor::Magenta` | `0xFF00FF` | ![Magenta](assets/magenta.png) | マゼンタ |
| Yellow | `EspHelper::RgbColor::Yellow` | `0xFFFF00` | ![Yellow](assets/yellow.png) | 黄 |
| Orange | `EspHelper::RgbColor::Orange` | `0xFF7F00` | ![Orange](assets/orange.png) | オレンジ |
| Purple | `EspHelper::RgbColor::Purple` | `0x8000FF` | ![Purple](assets/purple.png) | 紫 |
| Pink | `EspHelper::RgbColor::Pink` | `0xFF1493` | ![Pink](assets/pink.png) | ピンク |
| Lime | `EspHelper::RgbColor::Lime` | `0x32CD32` | ![Lime](assets/lime.png) | ライム |
| Teal | `EspHelper::RgbColor::Teal` | `0x008080` | ![Teal](assets/teal.png) | ティール |
| Navy | `EspHelper::RgbColor::Navy` | `0x000080` | ![Navy](assets/navy.png) | ネイビー |
| Maroon | `EspHelper::RgbColor::Maroon` | `0x800000` | ![Maroon](assets/maroon.png) | マルーン |
| Olive | `EspHelper::RgbColor::Olive` | `0x808000` | ![Olive](assets/olive.png) | オリーブ |
| Gold | `EspHelper::RgbColor::Gold` | `0xFFD700` | ![Gold](assets/gold.png) | ゴールド |
| Silver | `EspHelper::RgbColor::Silver` | `0xC0C0C0` | ![Silver](assets/silver.png) | シルバー |

## 収録スケッチ
- `SimpleStrip/SimpleStrip.ino` – ピン2に接続した単体LEDをカラーサイクル。
- `MultiStrip/MultiStrip.ino` – ピン2と4の2本のストリップでカラーWipe/フィルを実演。
