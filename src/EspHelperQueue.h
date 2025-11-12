#pragma once

#include <Arduino.h>

namespace EspHelper {

template <typename T>
class Queue {
 public:
  Queue() = default;

  explicit Queue(UBaseType_t length)
  {
    create(length);
  }

  ~Queue()
  {
    destroy();
  }

  bool create(UBaseType_t length)
  {
    destroy();
    handle_ = xQueueCreate(length, sizeof(T));
    return handle_ != nullptr;
  }

  bool send(const T &item, TickType_t ticks = portMAX_DELAY)
  {
    if (!handle_)
    {
      return false;
    }
    return xQueueSend(handle_, &item, ticks) == pdTRUE;
  }

  bool receive(T &out, TickType_t ticks = portMAX_DELAY)
  {
    if (!handle_)
    {
      return false;
    }
    return xQueueReceive(handle_, &out, ticks) == pdTRUE;
  }

  bool reset()
  {
    if (!handle_)
    {
      return false;
    }
    return xQueueReset(handle_) == pdPASS;
  }

  QueueHandle_t raw() const { return handle_; }

 private:
  void destroy()
  {
    if (handle_)
    {
      vQueueDelete(handle_);
      handle_ = nullptr;
    }
  }

  QueueHandle_t handle_ = nullptr;
};

}  // namespace EspHelper

