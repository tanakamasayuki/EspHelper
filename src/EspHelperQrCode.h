#pragma once

#include <Arduino.h>
extern "C"
{
#include <qrcode.h>
}

#include <algorithm>
#include <vector>

namespace EspHelper
{

  class QrCodeBitmap
  {
  public:
    bool generate(const char *text, int maxVersion = 10, int eccLevel = ESP_QRCODE_ECC_MED)
    {
      ready_ = false;
      modules_.clear();
      if (!text)
      {
        return false;
      }
      esp_qrcode_config_t cfg = ESP_QRCODE_CONFIG_DEFAULT();
      cfg.max_qrcode_version = std::max(2, std::min(maxVersion, 40));
      cfg.qrcode_ecc_level = std::max((int)ESP_QRCODE_ECC_LOW, std::min(eccLevel, (int)ESP_QRCODE_ECC_HIGH));
      cfg.display_func = &QrCodeBitmap::captureCallback;

      active_instance_ = this;
      esp_err_t err = esp_qrcode_generate(&cfg, text);
      active_instance_ = nullptr;
      return (err == ESP_OK) && ready_;
    }

    bool generate(const String &text, int maxVersion = 10, int eccLevel = ESP_QRCODE_ECC_MED)
    {
      return generate(text.c_str(), maxVersion, eccLevel);
    }

    bool ready() const { return ready_; }
    int size() const { return ready_ ? size_ : 0; }

    bool module(int x, int y) const
    {
      if (!ready_ || x < 0 || y < 0 || x >= size_ || y >= size_)
      {
        return false;
      }
      return modules_[y * size_ + x] != 0;
    }

    template <typename Fn>
    void forEachModule(Fn fn) const
    {
      if (!ready_)
      {
        return;
      }
      for (int y = 0; y < size_; ++y)
      {
        for (int x = 0; x < size_; ++x)
        {
          fn(x, y, modules_[y * size_ + x] != 0);
        }
      }
    }

    String toAscii(const char *dark = "██", const char *light = "  ", int border = 2) const
    {
      if (!ready_)
      {
        return String();
      }
      String out;
      const char *white = light;
      const char *black = dark;
      const int total = size_ + border * 2;
      for (int y = 0; y < total; ++y)
      {
        for (int x = 0; x < total; ++x)
        {
          bool on = false;
          int mx = x - border;
          int my = y - border;
          if (mx >= 0 && my >= 0 && mx < size_ && my < size_)
          {
            on = module(mx, my);
          }
          out += on ? black : white;
        }
        out += '\n';
      }
      return out;
    }

  private:
    static void captureCallback(esp_qrcode_handle_t qrcode)
    {
      if (active_instance_)
      {
        active_instance_->capture(qrcode);
      }
    }

    void capture(esp_qrcode_handle_t qrcode)
    {
      size_ = esp_qrcode_get_size(qrcode);
      modules_.assign(size_ * size_, 0);
      for (int y = 0; y < size_; ++y)
      {
        for (int x = 0; x < size_; ++x)
        {
          modules_[y * size_ + x] = esp_qrcode_get_module(qrcode, x, y) ? 1 : 0;
        }
      }
      ready_ = true;
    }

    static QrCodeBitmap *active_instance_;

    std::vector<uint8_t> modules_;
    int size_ = 0;
    bool ready_ = false;
  };

  inline QrCodeBitmap *QrCodeBitmap::active_instance_ = nullptr;

} // namespace EspHelper
