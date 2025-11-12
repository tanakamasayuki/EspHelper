# Dsp Examples

[日本語はこちら](README.ja.md)

`EspHelperDsp.h` builds on the ESP-IDF `esp_dsp` component to expose common signal-processing helpers that feel at home in Arduino sketches.

## API Reference
### `EspHelper::RealFft`
- `bool begin(size_t fftSize, WindowType window = WindowType::None)` – prepares working buffers (power-of-two sizes only) and optionally precomputes a Hann window.
- `void end()` – releases the FFT tables so a new size can be configured.
- `bool compute(const float *input, float *magnitudeOut, size_t magnitudeLength)` – copies `fftSize` real samples, runs the complex FFT, and writes the half-spectrum magnitudes.
- `size_t fftSize() const` / `size_t spectrumSize() const`
- `void setScale(float scale)` – adjust the post-FFT magnitude multiplier (defaults to `2/N`).

Usage tips:
- `esp_dsp` keeps FFT coefficient tables in global memory. Only one `RealFft` instance should be active at a time—call `end()` before starting another size.
- Supply a destination buffer of at least `fftSize/2` floats for magnitudes. The helper zeroes the imaginary part for you.

### `EspHelper::FirFilter`
- `bool begin(const float *coeffs, size_t tapCount)` / `bool begin(std::initializer_list<float>)`
- `bool process(const float *input, float *output, size_t length)` – runs `dsps_fir_f32` across the provided block.
- `void reset()` – clears the delay line.
- `size_t taps() const` / `bool ready() const`

Usage tips:
- Coefficients are copied internally, so temporary arrays are fine. The delay line is sized to `tapCount + 4`, matching esp-dsp requirements.
- Keep `length` reasonably small if you run the filter in the Arduino loop; long blocks should be offloaded to a task.

## Example overview
- `FftSpectrum/FftSpectrum.ino` – Synthesizes two tones, runs a Hann-windowed FFT, and prints the first 16 bins.
- `FirSmoothing/FirSmoothing.ino` – Applies a 7-tap moving-average FIR to a noisy ramp to show how repeated calls reuse the same state.
