# QrCode サンプル

[English README](README.md)

`EspHelperQrCode.h`はESP-IDFコンポーネント`espressif/qrcode`を包み、生成したQRコードをASCIIや各種ディスプレイへ簡単に描画できるようにします。

- `toAscii()`でシリアルコンソールにQRコードを表示。
- `forEachModule()`でモジュール状態を走査し、任意のディスプレイへ描画（M5Unifiedなど）。

## 収録スケッチ
- `AsciiConsole/AsciiConsole.ino` – URLをエンコードし、ASCIIブロックでシリアル出力。
- `M5Display/M5Display.ino` – Wi-Fi情報をQR化し、M5Unifiedディスプレイへ描画。

> **補足**: M5表示例をビルドするには [M5Unified](https://github.com/m5stack/M5Unified) ライブラリを事前にインストールしてください。
