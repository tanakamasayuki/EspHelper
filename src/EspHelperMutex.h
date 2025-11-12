#pragma once

#include <Arduino.h>

namespace EspHelper {

class Mutex {
 public:
  Mutex() = default;
  ~Mutex()
  {
    destroy();
  }

  bool create()
  {
    destroy();
    handle_ = xSemaphoreCreateMutex();
    return handle_ != nullptr;
  }

  bool lock(TickType_t ticks = portMAX_DELAY)
  {
    return handle_ && xSemaphoreTake(handle_, ticks) == pdTRUE;
  }

  bool unlock()
  {
    return handle_ && xSemaphoreGive(handle_) == pdTRUE;
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

}  // namespace EspHelper

