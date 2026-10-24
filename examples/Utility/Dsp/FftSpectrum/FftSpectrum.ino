// en: Compute a spectrum from a synthetic sampled signal
// ja: 模擬サンプル信号からSpectrumを計算する
#include <EspHelperDsp.h>

constexpr size_t kFftSize = 256;

EspHelper::RealFft fft;
float timeDomain[kFftSize];
float spectrum[kFftSize / 2];

void fillTestWave()
{
  for (size_t i = 0; i < kFftSize; ++i)
  {
    const float t = static_cast<float>(i) / static_cast<float>(kFftSize);
    // Two tones at 4 and 9 bins plus a bit of DC offset
    timeDomain[i] = 0.6f * sinf(2.0f * PI * 4.0f * t) + 0.3f * sinf(2.0f * PI * 9.0f * t) + 0.05f;
  }
}

void printStrongestBins(size_t count)
{
  Serial.println(F("bin	magnitude"));
  for (size_t i = 0; i < count && i < fft.spectrumSize(); ++i)
  {
    Serial.printf("%3u\t%0.4f\n", static_cast<unsigned>(i), spectrum[i]);
  }
}

void setup()
{
  Serial.begin(115200);
  fillTestWave();

  // en: Initialize this component after its prerequisites; inspect the returned status where provided.
  // ja: 前提となる機器を準備してから初期化し、結果を返すAPIでは成否を確認します。
  if (!fft.begin(kFftSize, EspHelper::RealFft::WindowType::Hann))
  {
    Serial.println(F("Failed to init RealFft (check esp_dsp support)."));
    while (true)
    {
      delay(1000);
    }
  }

  // en: Supply the configured number and format of samples before reading the transformed result.
  // ja: 設定した数と形式のサンプルを渡してから変換結果を読みます。
  if (fft.compute(timeDomain, spectrum, fft.spectrumSize()))
  {
    printStrongestBins(16);
  }
  else
  {
    Serial.println(F("FFT computation failed"));
  }
}

void loop()
{
}
