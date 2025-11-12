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

  if (!fft.begin(kFftSize, EspHelper::RealFft::WindowType::Hann))
  {
    Serial.println(F("Failed to init RealFft (check esp_dsp support)."));
    while (true)
    {
      delay(1000);
    }
  }

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
