#pragma once

#include <Arduino.h>

namespace EspHelper
{

  class BinarySemaphore
  {
  public:
    BinarySemaphore() = default;
    ~BinarySemaphore()
    {
      destroy();
    }

    bool create()
    {
      destroy();
      handle_ = xSemaphoreCreateBinary();
      return handle_ != nullptr;
    }

    bool give()
    {
      return handle_ && xSemaphoreGive(handle_) == pdTRUE;
    }

    bool take(TickType_t ticks = portMAX_DELAY)
    {
      return handle_ && xSemaphoreTake(handle_, ticks) == pdTRUE;
    }

    SemaphoreHandle_t raw() const { return handle_; }

  private:
    void destroy()
    {
      if (handle_)
      {
        vSemaphoreDelete(handle_);
        handle_ = nullptr;
      }
    }

    SemaphoreHandle_t handle_ = nullptr;
  };

  class CountingSemaphore
  {
  public:
    CountingSemaphore() = default;
    ~CountingSemaphore()
    {
      destroy();
    }

    bool create(UBaseType_t maxCount, UBaseType_t initialCount)
    {
      destroy();
      handle_ = xSemaphoreCreateCounting(maxCount, initialCount);
      return handle_ != nullptr;
    }

    bool give()
    {
      return handle_ && xSemaphoreGive(handle_) == pdTRUE;
    }

    bool take(TickType_t ticks = portMAX_DELAY)
    {
      return handle_ && xSemaphoreTake(handle_, ticks) == pdTRUE;
    }

    SemaphoreHandle_t raw() const { return handle_; }

  private:
    void destroy()
    {
      if (handle_)
      {
        vSemaphoreDelete(handle_);
        handle_ = nullptr;
      }
    }

    SemaphoreHandle_t handle_ = nullptr;
  };

} // namespace EspHelper
