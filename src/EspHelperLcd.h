#pragma once

#include <Arduino.h>

extern "C" {
#include <driver/gpio.h>
#include <driver/i2c.h>
#include <driver/spi_master.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_ssd1306.h>
#include <esp_lcd_panel_st7789.h>
}

#include <vector>

namespace EspHelper {

class LcdPanel {
 public:
  enum class Model
  {
    None,
    ST7789,
    SSD1306,
  };

  struct St7789Config {
    spi_host_device_t spi_host = SPI2_HOST;
    int mosi_pin = -1;
    int sclk_pin = -1;
    int dc_pin = -1;
    int cs_pin = -1;
    int rst_pin = -1;
    int bl_pin = -1;
    bool backlight_on_level = true;
    uint32_t max_transfer_bytes = 0;
    uint32_t pclk_hz = 40 * 1000 * 1000;
    int width = 240;
    int height = 240;
    int x_offset = 0;
    int y_offset = 0;
    bool mirror_x = false;
    bool mirror_y = false;
    bool swap_xy = false;
    bool invert_color = false;
  };

  struct Ssd1306Config {
    i2c_port_t i2c_port = I2C_NUM_0;
    int sda_pin = -1;
    int scl_pin = -1;
    int rst_pin = -1;
    uint8_t address = 0x3C;
    uint32_t clk_speed_hz = 400000;
    int width = 128;
    int height = 64;
  };

  LcdPanel() = default;
  ~LcdPanel() { end(); }

  bool begin(const St7789Config &config)
  {
    end();
    return initSt7789(config);
  }

  bool begin(const Ssd1306Config &config)
  {
    end();
    return initSsd1306(config);
  }

  void end()
  {
    if (panel_handle_)
    {
      esp_lcd_panel_del(panel_handle_);
      panel_handle_ = nullptr;
    }
    if (io_handle_)
    {
      esp_lcd_panel_io_del(io_handle_);
      io_handle_ = nullptr;
    }
    if (owns_spi_bus_)
    {
      spi_bus_free(spi_host_);
      owns_spi_bus_ = false;
    }
    if (owns_i2c_driver_)
    {
      i2c_driver_delete(i2c_port_);
      owns_i2c_driver_ = false;
    }
    if (backlight_pin_ >= 0)
    {
      gpio_reset_pin((gpio_num_t)backlight_pin_);
    }
    pixel_format_ = PixelFormat::Unknown;
    width_ = height_ = 0;
    backlight_pin_ = -1;
    model_ = Model::None;
    rgb565_line_.clear();
    mono_line_.clear();
  }

  bool drawBitmap(int x, int y, int width, int height, const void *pixels)
  {
    if (!panel_handle_ || !pixels)
    {
      return false;
    }
    return esp_lcd_panel_draw_bitmap(panel_handle_, x, y, x + width, y + height, pixels) == ESP_OK;
  }

  bool drawPixel(int x, int y, uint16_t color)
  {
    if (!panel_handle_)
    {
      return false;
    }
    if (pixel_format_ == PixelFormat::Mono1Bpp)
    {
      uint8_t pixel = color ? 0xFF : 0x00;
      return esp_lcd_panel_draw_bitmap(panel_handle_, x, y, x + 1, y + 1, &pixel) == ESP_OK;
    }
    uint16_t pixel = color;
    return esp_lcd_panel_draw_bitmap(panel_handle_, x, y, x + 1, y + 1, &pixel) == ESP_OK;
  }

  bool fillScreen(uint16_t color)
  {
    if (!panel_handle_ || width_ <= 0 || height_ <= 0)
    {
      return false;
    }
    if (pixel_format_ == PixelFormat::Mono1Bpp)
    {
      const size_t bytes_per_row = (width_ + 7) / 8;
      if (mono_line_.size() != bytes_per_row)
      {
        mono_line_.assign(bytes_per_row, 0);
      }
      std::fill(mono_line_.begin(), mono_line_.end(), color ? 0xFF : 0x00);
      for (int row = 0; row < height_; ++row)
      {
        if (esp_lcd_panel_draw_bitmap(panel_handle_, 0, row, width_, row + 1, mono_line_.data()) != ESP_OK)
        {
          return false;
        }
      }
      return true;
    }

    if ((int)rgb565_line_.size() != width_)
    {
      rgb565_line_.assign(width_, 0);
    }
    std::fill(rgb565_line_.begin(), rgb565_line_.end(), color);
    for (int row = 0; row < height_; ++row)
    {
      if (esp_lcd_panel_draw_bitmap(panel_handle_, 0, row, width_, row + 1, rgb565_line_.data()) != ESP_OK)
      {
        return false;
      }
    }
    return true;
  }

  void setBacklight(bool on)
  {
    if (backlight_pin_ < 0)
    {
      return;
    }
    const int level = on ? (backlight_on_level_ ? 1 : 0) : (backlight_on_level_ ? 0 : 1);
    gpio_set_level((gpio_num_t)backlight_pin_, level);
  }

  int width() const { return width_; }
  int height() const { return height_; }
  Model model() const { return model_; }

 private:
  enum class PixelFormat
  {
    Unknown,
    Rgb565,
    Mono1Bpp,
  };

  bool initSt7789(const St7789Config &cfg)
  {
    if (cfg.mosi_pin < 0 || cfg.sclk_pin < 0 || cfg.dc_pin < 0)
    {
      return false;
    }
    St7789Config local = cfg;
    if (!local.max_transfer_bytes)
    {
      local.max_transfer_bytes = local.width * local.height * sizeof(uint16_t);
    }

    spi_bus_config_t buscfg = {};
    buscfg.mosi_io_num = local.mosi_pin;
    buscfg.miso_io_num = -1;
    buscfg.sclk_io_num = local.sclk_pin;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.data4_io_num = -1;
    buscfg.data5_io_num = -1;
    buscfg.data6_io_num = -1;
    buscfg.data7_io_num = -1;
    buscfg.data_io_default_level = false;
    buscfg.max_transfer_sz = static_cast<int>(local.max_transfer_bytes);
    buscfg.flags = SPICOMMON_BUSFLAG_MASTER;
    buscfg.isr_cpu_id = ESP_INTR_CPU_AFFINITY_AUTO;
    buscfg.intr_flags = 0;
    esp_err_t err = spi_bus_initialize(local.spi_host, &buscfg, SPI_DMA_CH_AUTO);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
    {
      return false;
    }
    owns_spi_bus_ = (err == ESP_OK);
    spi_host_ = local.spi_host;

    esp_lcd_panel_io_spi_config_t io_config = {};
    io_config.cs_gpio_num = local.cs_pin;
    io_config.dc_gpio_num = local.dc_pin;
    io_config.spi_mode = 0;
    io_config.pclk_hz = static_cast<int>(local.pclk_hz);
    io_config.trans_queue_depth = 10;
    io_config.on_color_trans_done = nullptr;
    io_config.user_ctx = nullptr;
    io_config.lcd_cmd_bits = 8;
    io_config.lcd_param_bits = 8;
    io_config.cs_ena_pretrans = 0;
    io_config.cs_ena_posttrans = 0;
    io_config.flags.cs_high_active = 0;

    if (esp_lcd_new_panel_io_spi(local.spi_host, &io_config, &io_handle_) != ESP_OK)
    {
      end();
      return false;
    }

    esp_lcd_panel_dev_config_t panel_config = {};
    panel_config.reset_gpio_num = local.rst_pin;
    panel_config.color_space = ESP_LCD_COLOR_SPACE_RGB;
    panel_config.data_endian = LCD_RGB_DATA_ENDIAN_BIG;
    panel_config.bits_per_pixel = 16;
    panel_config.flags.reset_active_high = 0;

    if (esp_lcd_new_panel_st7789(io_handle_, &panel_config, &panel_handle_) != ESP_OK)
    {
      end();
      return false;
    }

    if (local.rst_pin >= 0)
    {
      esp_lcd_panel_reset(panel_handle_);
    }
    if (esp_lcd_panel_init(panel_handle_) != ESP_OK)
    {
      end();
      return false;
    }

    esp_err_t gap_err = esp_lcd_panel_set_gap(panel_handle_, local.x_offset, local.y_offset);
    if (gap_err != ESP_OK && gap_err != ESP_ERR_NOT_SUPPORTED)
    {
      end();
      return false;
    }

    esp_lcd_panel_invert_color(panel_handle_, local.invert_color);
    esp_lcd_panel_mirror(panel_handle_, local.mirror_x, local.mirror_y);
    if (local.swap_xy)
    {
      esp_lcd_panel_swap_xy(panel_handle_, true);
    }

    if (local.bl_pin >= 0)
    {
      gpio_config_t io_conf = {
          .pin_bit_mask = 1ULL << local.bl_pin,
          .mode = GPIO_MODE_OUTPUT,
          .pull_up_en = GPIO_PULLUP_DISABLE,
          .pull_down_en = GPIO_PULLDOWN_DISABLE,
          .intr_type = GPIO_INTR_DISABLE,
      };
      gpio_config(&io_conf);
      backlight_pin_ = local.bl_pin;
      backlight_on_level_ = local.backlight_on_level;
      setBacklight(true);
    }

    width_ = local.width;
    height_ = local.height;
    pixel_format_ = PixelFormat::Rgb565;
    model_ = Model::ST7789;
    return true;
  }

  bool initSsd1306(const Ssd1306Config &cfg)
  {
    if (cfg.sda_pin < 0 || cfg.scl_pin < 0)
    {
      return false;
    }

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = cfg.sda_pin,
        .scl_io_num = cfg.scl_pin,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master = {.clk_speed = cfg.clk_speed_hz},
        .clk_flags = 0,
    };
    i2c_param_config(cfg.i2c_port, &conf);
    esp_err_t err = i2c_driver_install(cfg.i2c_port, I2C_MODE_MASTER, 0, 0, 0);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
    {
      return false;
    }
    owns_i2c_driver_ = (err == ESP_OK);
    i2c_port_ = cfg.i2c_port;

    esp_lcd_panel_io_i2c_config_t io_config = {
        .dev_addr = cfg.address,
        .on_color_trans_done = nullptr,
        .user_ctx = nullptr,
        .control_phase_bytes = 1,
        .dc_bit_offset = 0,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .flags = {
            .dc_low_on_data = 0,
            .disable_control_phase = 0,
        },
        .scl_speed_hz = cfg.clk_speed_hz,
    };

    if (esp_lcd_new_panel_io_i2c(cfg.i2c_port, &io_config, &io_handle_) != ESP_OK)
    {
      end();
      return false;
    }

    esp_lcd_panel_ssd1306_config_t vendor_config = {
        .height = static_cast<uint8_t>(cfg.height),
    };

    esp_lcd_panel_dev_config_t panel_config = {};
    panel_config.reset_gpio_num = cfg.rst_pin;
    panel_config.color_space = ESP_LCD_COLOR_SPACE_MONOCHROME;
    panel_config.data_endian = LCD_RGB_DATA_ENDIAN_BIG;
    panel_config.bits_per_pixel = 1;
    panel_config.flags.reset_active_high = 0;
    panel_config.vendor_config = &vendor_config;

    if (esp_lcd_new_panel_ssd1306(io_handle_, &panel_config, &panel_handle_) != ESP_OK)
    {
      end();
      return false;
    }

    if (cfg.rst_pin >= 0)
    {
      esp_lcd_panel_reset(panel_handle_);
    }
    if (esp_lcd_panel_init(panel_handle_) != ESP_OK)
    {
      end();
      return false;
    }

    width_ = cfg.width;
    height_ = cfg.height;
    pixel_format_ = PixelFormat::Mono1Bpp;
    model_ = Model::SSD1306;
    return true;
  }

  spi_host_device_t spi_host_ = SPI2_HOST;
  bool owns_spi_bus_ = false;
  bool owns_i2c_driver_ = false;
  i2c_port_t i2c_port_ = I2C_NUM_0;
  esp_lcd_panel_io_handle_t io_handle_ = nullptr;
  esp_lcd_panel_handle_t panel_handle_ = nullptr;
  PixelFormat pixel_format_ = PixelFormat::Unknown;
  int width_ = 0;
  int height_ = 0;
  int backlight_pin_ = -1;
  bool backlight_on_level_ = true;
  Model model_ = Model::None;
  std::vector<uint16_t> rgb565_line_;
  std::vector<uint8_t> mono_line_;
};

}  // namespace EspHelper
