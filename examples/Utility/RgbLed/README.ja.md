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
| 名前 | 定数 | Hex値 | 説明 |
|------|------|-------|------|
| Black | `EspHelper::RgbColor::Black` | `0x000000` | 消灯 |
| White | `EspHelper::RgbColor::White` | `0xFFFFFF` | 白 |
| Red | `EspHelper::RgbColor::Red` | `0xFF0000` | 赤 |
| Green | `EspHelper::RgbColor::Green` | `0x00FF00` | 緑 |
| Blue | `EspHelper::RgbColor::Blue` | `0x0000FF` | 青 |
| Cyan | `EspHelper::RgbColor::Cyan` | `0x00FFFF` | シアン |
| Magenta | `EspHelper::RgbColor::Magenta` | `0xFF00FF` | マゼンタ |
| Yellow | `EspHelper::RgbColor::Yellow` | `0xFFFF00` | 黄 |
| Orange | `EspHelper::RgbColor::Orange` | `0xFF7F00` | オレンジ |
| Purple | `EspHelper::RgbColor::Purple` | `0x8000FF` | 紫 |
| Pink | `EspHelper::RgbColor::Pink` | `0xFF1493` | ピンク |
| Lime | `EspHelper::RgbColor::Lime` | `0x32CD32` | ライム |
| Teal | `EspHelper::RgbColor::Teal` | `0x008080` | ティール |
| Navy | `EspHelper::RgbColor::Navy` | `0x000080` | ネイビー |
| Maroon | `EspHelper::RgbColor::Maroon` | `0x800000` | マルーン |
| Olive | `EspHelper::RgbColor::Olive` | `0x808000` | オリーブ |
| Gold | `EspHelper::RgbColor::Gold` | `0xFFD700` | ゴールド |
| Silver | `EspHelper::RgbColor::Silver` | `0xC0C0C0` | シルバー |

## 収録スケッチ
- `SimpleStrip/SimpleStrip.ino` – ピン2に接続した単体LEDをカラーサイクル。
- `MultiStrip/MultiStrip.ino` – ピン2と4の2本のストリップでカラーWipe/フィルを実演。
