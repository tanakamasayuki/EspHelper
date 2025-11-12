#include <EspHelperDsp.h>

constexpr size_t kSamples = 32;

// Simple 7-tap moving-average window
const float kAverageTaps[] = {
    0.142857f, 0.142857f, 0.142857f, 0.142857f, 0.142857f, 0.142857f, 0.142857f,
};

EspHelper::FirFilter fir;
float noisy[kSamples];
float filtered[kSamples];

void fillNoisyRamp()
{
  for (size_t i = 0; i < kSamples; ++i)
  {
    float ramp = static_cast<float>(i) / static_cast<float>(kSamples);
    float noise = static_cast<float>(random(-100, 101)) / 500.0f;  // +/-0.2
    noisy[i] = ramp + noise;
  }
}

void printSamples(const float *src)
{
  for (size_t i = 0; i < 10 && i < kSamples; ++i)
  {
    Serial.printf("%0.3f ", src[i]);
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  randomSeed(esp_random());

  if (!fir.begin(kAverageTaps, sizeof(kAverageTaps) / sizeof(kAverageTaps[0])))
  {
    Serial.println(F("Failed to init FIR filter"));
    while (true)
    {
      delay(1000);
    }
  }
}

void loop()
{
  fillNoisyRamp();
  if (fir.process(noisy, filtered, kSamples))
  {
    Serial.println(F("raw:"));
    printSamples(noisy);
    Serial.println(F("filtered:"));
    printSamples(filtered);
  }
  else
  {
    Serial.println(F("FIR processing failed"));
  }
  delay(1500);
}
