# Utility Examples

[日本語はこちら](README.ja.md)

Utility examples collect helpers that do not fall into JSON, FreeRTOS, networking, or display buckets. Currently this includes QR code rendering via the ESP-IDF `espressif/qrcode` component, DSP helpers powered by `esp_dsp`, the generic `esp_event` wrapper, and libsodium utilities.

- **QrCode (`EspHelperQrCode.h`)** – generate QR codes once and reuse the captured bitmap for ASCII output, serial printing, or custom displays such as M5Unified. ([Docs](QrCode/README.md))
- **Dsp (`EspHelperDsp.h`)** – real-valued FFT and FIR filters that wrap `esp_dsp` with Arduino-friendly buffers. ([Docs](Dsp/README.md))
- **Event (`EspHelperEvent.h`)** – manage `esp_event` loops, handlers, and postings with a minimal RAII wrapper. ([Docs](Event/README.md))
- **Sodium (`EspHelperSodium.h`)** – thin wrappers over libsodium for randomness, `crypto_secretbox`, and Ed25519 signatures. ([Docs](Sodium/README.md))

See `QrCode/`, `Dsp/`, `Event/`, and `Sodium/` for concrete sketches.
