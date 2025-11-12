# Dsp サンプル

[English README](README.md)

`EspHelperDsp.h` は ESP-IDF コンポーネント`esp_dsp`をArduinoライクなAPIにまとめ、FFTとFIRフィルタをスケッチから扱いやすくします。

## APIリファレンス
### `EspHelper::RealFft`
- `begin(fftSize, window)` – FFTサイズ（2のべき乗）とウィンドウ種別（`None`/`Hann`）を指定して作業バッファと係数を初期化。
- `end()` – FFTテーブルを解放。別サイズへ切り替える前に呼び出します。
- `compute(input, magnitudeOut, magnitudeLength)` – 実数サンプルを取り込み、複素FFT→ビットリバース→`dsps_cplx2reC`まで実行し、半分のバンドの振幅を出力。
- `fftSize()` / `spectrumSize()` / `setScale(scale)` – 現在の設定値やスケーリング係数を参照/変更。

使いどころメモ:
- `esp_dsp`のFFT係数テーブルはグローバル共有なので、同時に複数の`RealFft`を動かさず、別サイズに切り替える際は`end()`で明示的に解放してください。
- `magnitudeOut` には最低でも `fftSize/2` 要素のバッファを渡します。虚部は内部でゼロクリアされます。

### `EspHelper::FirFilter`
- `begin(coeffs, tapCount)` / `begin({ ... })` – 係数をコピーして内部の遅延線を確保。
- `process(input, output, length)` – `dsps_fir_f32`を呼び出し、ブロック単位で畳み込みを実行。
- `reset()` – 遅延線をゼロクリア。
- `taps()` / `ready()` – フィルタ長や初期化状態の確認。

使いどころメモ:
- 係数配列は内部コピーされるため、スタック上の一時配列でも安全です。
- Arduinoの`loop()`で使う場合は適度なブロック長に分割し、長時間ブロックはFreeRTOSタスクへ任せると負荷をコントロールできます。

## 収録スケッチ
- `FftSpectrum/FftSpectrum.ino` – 2つの正弦波を合成し、Hannウィンドウ付きFFTで最初の16ビンをシリアルに出力。
- `FirSmoothing/FirSmoothing.ino` – ノイズを含むランプ波に7タップ移動平均FIRを適用し、平滑化の効果を表示。
