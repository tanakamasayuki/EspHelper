#pragma once

#include <Arduino.h>
extern "C" {
#include <esp_dsp.h>
}

#include <algorithm>
#include <climits>
#include <initializer_list>
#include <math.h>
#include <vector>

namespace EspHelper {

class RealFft {
 public:
  enum class WindowType
  {
    None,
    Hann,
  };

  RealFft() = default;
  ~RealFft() { end(); }

  bool begin(size_t fftSize, WindowType window = WindowType::None)
  {
    if (!isPowerOfTwo(fftSize) || fftSize > static_cast<size_t>(INT_MAX))
    {
      return false;
    }
    end();
    fft_size_ = fftSize;
    data_.assign(fft_size_ * 2, 0.0f);
    if (window == WindowType::Hann)
    {
      window_.assign(fft_size_, 0.0f);
      dsps_wind_hann_f32(window_.data(), static_cast<int>(fft_size_));
    }
    else
    {
      window_.clear();
    }
    if (dsps_fft2r_init_fc32(nullptr, static_cast<int>(fft_size_)) != ESP_OK)
    {
      data_.clear();
      window_.clear();
      fft_size_ = 0;
      return false;
    }
    scale_ = 2.0f / static_cast<float>(fft_size_);
    initialized_ = true;
    return true;
  }

  void end()
  {
    if (initialized_)
    {
      dsps_fft2r_deinit_fc32();
      initialized_ = false;
    }
    data_.clear();
    window_.clear();
    fft_size_ = 0;
  }

  bool compute(const float *input, float *magnitudeOut, size_t magnitudeLength)
  {
    if (!initialized_ || !input || !magnitudeOut)
    {
      return false;
    }
    const size_t bins = fft_size_ / 2;
    if (magnitudeLength < bins)
    {
      return false;
    }
    for (size_t i = 0; i < fft_size_; ++i)
    {
      float sample = input[i];
      if (!window_.empty())
      {
        sample *= window_[i];
      }
      data_[2 * i] = sample;
      data_[2 * i + 1] = 0.0f;
    }
    if (dsps_fft2r_fc32(data_.data(), static_cast<int>(fft_size_)) != ESP_OK)
    {
      return false;
    }
    if (dsps_bit_rev_fc32(data_.data(), static_cast<int>(fft_size_)) != ESP_OK)
    {
      return false;
    }
    if (dsps_cplx2reC_fc32(data_.data(), static_cast<int>(fft_size_)) != ESP_OK)
    {
      return false;
    }
    for (size_t i = 0; i < bins; ++i)
    {
      const float real = data_[2 * i];
      const float imag = data_[2 * i + 1];
      magnitudeOut[i] = sqrtf(real * real + imag * imag) * scale_;
    }
    return true;
  }

  size_t fftSize() const { return fft_size_; }
  size_t spectrumSize() const { return fft_size_ / 2; }
  void setScale(float scale) { scale_ = scale; }

 private:
  static bool isPowerOfTwo(size_t value)
  {
    return value >= 2 && (value & (value - 1)) == 0;
  }

  size_t fft_size_ = 0;
  std::vector<float> data_;
  std::vector<float> window_;
  float scale_ = 1.0f;
  bool initialized_ = false;
};

class FirFilter {
 public:
  FirFilter() = default;

  bool begin(const float *coeffs, size_t tapCount)
  {
    if (!coeffs || tapCount == 0 || tapCount > static_cast<size_t>(INT_MAX))
    {
      return false;
    }
    coeffs_.assign(coeffs, coeffs + tapCount);
    return initFilter();
  }

  bool begin(std::initializer_list<float> coeffs)
  {
    if (coeffs.size() == 0)
    {
      return false;
    }
    coeffs_.assign(coeffs.begin(), coeffs.end());
    return initFilter();
  }

  bool process(const float *input, float *output, size_t length)
  {
    if (!ready_ || !input || !output || length == 0 || length > static_cast<size_t>(INT_MAX))
    {
      return false;
    }
    return dsps_fir_f32(&fir_, input, output, static_cast<int>(length)) == ESP_OK;
  }

  void reset()
  {
    if (!ready_)
    {
      return;
    }
    std::fill(delay_.begin(), delay_.end(), 0.0f);
    fir_.pos = 0;
  }

  size_t taps() const { return coeffs_.size(); }
  bool ready() const { return ready_; }

 private:
  bool initFilter()
  {
    delay_.assign(coeffs_.size() + 4, 0.0f);
    fir_ = {};
    if (dsps_fir_init_f32(&fir_, coeffs_.data(), delay_.data(), static_cast<int>(coeffs_.size())) != ESP_OK)
    {
      coeffs_.clear();
      delay_.clear();
      ready_ = false;
      return false;
    }
    ready_ = true;
    return true;
  }

  fir_f32_t fir_{};
  std::vector<float> coeffs_;
  std::vector<float> delay_;
  bool ready_ = false;
};

}  // namespace EspHelper
