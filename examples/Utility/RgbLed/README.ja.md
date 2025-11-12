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
| Black | `EspHelper::RgbColor::Black` | `0x000000` | <span style="display:inline-block;width:32px;height:12px;background:#000000;border:1px solid #ddd;"></span> | 消灯 |
| White | `EspHelper::RgbColor::White` | `0xFFFFFF` | <span style="display:inline-block;width:32px;height:12px;background:#FFFFFF;border:1px solid #ddd;"></span> | 白 |
| Red | `EspHelper::RgbColor::Red` | `0xFF0000` | <span style="display:inline-block;width:32px;height:12px;background:#FF0000;border:1px solid #ddd;"></span> | 赤 |
| Green | `EspHelper::RgbColor::Green` | `0x00FF00` | <span style="display:inline-block;width:32px;height:12px;background:#00FF00;border:1px solid #ddd;"></span> | 緑 |
| Blue | `EspHelper::RgbColor::Blue` | `0x0000FF` | <span style="display:inline-block;width:32px;height:12px;background:#0000FF;border:1px solid #ddd;"></span> | 青 |
| Cyan | `EspHelper::RgbColor::Cyan` | `0x00FFFF` | <span style="display:inline-block;width:32px;height:12px;background:#00FFFF;border:1px solid #ddd;"></span> | シアン |
| Magenta | `EspHelper::RgbColor::Magenta` | `0xFF00FF` | <span style="display:inline-block;width:32px;height:12px;background:#FF00FF;border:1px solid #ddd;"></span> | マゼンタ |
| Yellow | `EspHelper::RgbColor::Yellow` | `0xFFFF00` | <span style="display:inline-block;width:32px;height:12px;background:#FFFF00;border:1px solid #ddd;"></span> | 黄 |
| Orange | `EspHelper::RgbColor::Orange` | `0xFF7F00` | <span style="display:inline-block;width:32px;height:12px;background:#FF7F00;border:1px solid #ddd;"></span> | オレンジ |
| Purple | `EspHelper::RgbColor::Purple` | `0x8000FF` | <span style="display:inline-block;width:32px;height:12px;background:#8000FF;border:1px solid #ddd;"></span> | 紫 |
| Pink | `EspHelper::RgbColor::Pink` | `0xFF1493` | <span style="display:inline-block;width:32px;height:12px;background:#FF1493;border:1px solid #ddd;"></span> | ピンク |
| Lime | `EspHelper::RgbColor::Lime` | `0x32CD32` | <span style="display:inline-block;width:32px;height:12px;background:#32CD32;border:1px solid #ddd;"></span> | ライム |
| Teal | `EspHelper::RgbColor::Teal` | `0x008080` | <span style="display:inline-block;width:32px;height:12px;background:#008080;border:1px solid #ddd;"></span> | ティール |
| Navy | `EspHelper::RgbColor::Navy` | `0x000080` | <span style="display:inline-block;width:32px;height:12px;background:#000080;border:1px solid #ddd;"></span> | ネイビー |
| Maroon | `EspHelper::RgbColor::Maroon` | `0x800000` | <span style="display:inline-block;width:32px;height:12px;background:#800000;border:1px solid #ddd;"></span> | マルーン |
| Olive | `EspHelper::RgbColor::Olive` | `0x808000` | <span style="display:inline-block;width:32px;height:12px;background:#808000;border:1px solid #ddd;"></span> | オリーブ |
| Gold | `EspHelper::RgbColor::Gold` | `0xFFD700` | <span style="display:inline-block;width:32px;height:12px;background:#FFD700;border:1px solid #ddd;"></span> | ゴールド |
| Silver | `EspHelper::RgbColor::Silver` | `0xC0C0C0` | <span style="display:inline-block;width:32px;height:12px;background:#C0C0C0;border:1px solid #ddd;"></span> | シルバー |

## 収録スケッチ
- `SimpleStrip/SimpleStrip.ino` – ピン2に接続した単体LEDをカラーサイクル。
- `MultiStrip/MultiStrip.ino` – ピン2と4の2本のストリップでカラーWipe/フィルを実演。
