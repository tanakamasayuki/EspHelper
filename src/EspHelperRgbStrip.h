#pragma once

#include <Arduino.h>

#include <vector>

namespace EspHelper {

/**
 * @brief Blocking rgbLedWrite()-based helper that mimics a simple strip API.
 * Multiple RGB LEDs are chained behind a single pin; show() walks through all stored colors sequentially.
 */
class RgbStrip {
 public:
  RgbStrip(uint8_t pin, size_t ledCount, uint8_t brightness = 255, uint32_t interPixelDelayUs = 50)
      : pin_(pin), pixels_(ledCount), brightness_(brightness), delay_us_(interPixelDelayUs) {}

  size_t size() const { return pixels_.size(); }

  void setBrightness(uint8_t value) { brightness_ = value; }
  void setInterPixelDelay(uint32_t micros) { delay_us_ = micros; }

  void setPixelColor(size_t index, uint8_t r, uint8_t g, uint8_t b)
  {
    if (index >= pixels_.size())
    {
      return;
    }
    pixels_[index] = {r, g, b};
  }

  void setPixelColor(size_t index, uint32_t packed)
  {
    setPixelColor(index, (packed >> 16) & 0xFF, (packed >> 8) & 0xFF, packed & 0xFF);
  }

  void fill(uint8_t r, uint8_t g, uint8_t b)
  {
    for (auto &p : pixels_)
    {
      p = {r, g, b};
    }
  }

  void fill(uint32_t packed)
  {
    fill((packed >> 16) & 0xFF, (packed >> 8) & 0xFF, packed & 0xFF);
  }

  void clear()
  {
    fill(0, 0, 0);
  }

  void show()
  {
    for (size_t i = 0; i < pixels_.size(); ++i)
    {
      auto scaled = scaleColor(pixels_[i]);
      rgbLedWrite(pin_, scaled.r, scaled.g, scaled.b);
      if (delay_us_ > 0)
      {
        delayMicroseconds(delay_us_);
      }
    }
  }

 private:
  struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
  };

  Color scaleColor(const Color &c) const
  {
    if (brightness_ >= 255)
    {
      return c;
    }
    Color out;
    out.r = static_cast<uint8_t>((static_cast<uint16_t>(c.r) * brightness_) / 255);
    out.g = static_cast<uint8_t>((static_cast<uint16_t>(c.g) * brightness_) / 255);
    out.b = static_cast<uint8_t>((static_cast<uint16_t>(c.b) * brightness_) / 255);
    return out;
  }

  std::vector<Color> pixels_;
  uint8_t pin_ = 0;
  uint8_t brightness_ = 255;
  uint32_t delay_us_ = 50;
};

namespace RgbColor {
static constexpr uint32_t Black = 0x000000;
static constexpr uint32_t White = 0xFFFFFF;
static constexpr uint32_t Red = 0xFF0000;
static constexpr uint32_t Green = 0x00FF00;
static constexpr uint32_t Blue = 0x0000FF;
static constexpr uint32_t Cyan = 0x00FFFF;
static constexpr uint32_t Magenta = 0xFF00FF;
static constexpr uint32_t Yellow = 0xFFFF00;
static constexpr uint32_t Orange = 0xFF7F00;
static constexpr uint32_t Purple = 0x8000FF;
static constexpr uint32_t Pink = 0xFF1493;
static constexpr uint32_t Lime = 0x32CD32;
static constexpr uint32_t Teal = 0x008080;
static constexpr uint32_t Navy = 0x000080;
static constexpr uint32_t Maroon = 0x800000;
static constexpr uint32_t Olive = 0x808000;
static constexpr uint32_t Gold = 0xFFD700;
static constexpr uint32_t Silver = 0xC0C0C0;
}  // namespace RgbColor

}  // namespace EspHelper
