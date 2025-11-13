#pragma once

#include <Arduino.h>
#include <freertos/message_buffer.h>

namespace EspHelper {

class MessageBuffer {
 public:
  MessageBuffer() = default;
  ~MessageBuffer() { destroy(); }

  bool create(size_t capacity)
  {
    destroy();
    handle_ = xMessageBufferCreate(capacity);
    return handle_ != nullptr;
  }

  bool createStatic(size_t capacity, uint8_t *storage, StaticMessageBuffer_t *control)
  {
    if (!storage || !control)
    {
      return false;
    }
    destroy();
    handle_ = xMessageBufferCreateStatic(capacity, storage, control);
    static_buffer_ = storage;
    static_control_ = control;
    return handle_ != nullptr;
  }

  size_t send(const void *data, size_t length, TickType_t ticks = portMAX_DELAY)
  {
    if (!handle_ || !data || length == 0)
    {
      return 0;
    }
    return xMessageBufferSend(handle_, data, length, ticks);
  }

  size_t sendFromISR(const void *data, size_t length, BaseType_t *hpTaskWoken = nullptr)
  {
    if (!handle_ || !data || length == 0)
    {
      return 0;
    }
    BaseType_t taskWoken = pdFALSE;
    size_t written = xMessageBufferSendFromISR(handle_, data, length, &taskWoken);
    if (hpTaskWoken)
    {
      *hpTaskWoken = taskWoken;
    }
    return written;
  }

  size_t receive(void *data, size_t maxLength, TickType_t ticks = portMAX_DELAY)
  {
    if (!handle_ || !data || maxLength == 0)
    {
      return 0;
    }
    return xMessageBufferReceive(handle_, data, maxLength, ticks);
  }

  size_t receiveFromISR(void *data, size_t maxLength, BaseType_t *hpTaskWoken = nullptr)
  {
    if (!handle_ || !data || maxLength == 0)
    {
      return 0;
    }
    BaseType_t taskWoken = pdFALSE;
    size_t read = xMessageBufferReceiveFromISR(handle_, data, maxLength, &taskWoken);
    if (hpTaskWoken)
    {
      *hpTaskWoken = taskWoken;
    }
    return read;
  }

  size_t nextMessageSize() const
  {
    if (!handle_)
    {
      return 0;
    }
    return xMessageBufferNextLengthBytes(handle_);
  }

  size_t spaceAvailable() const
  {
    if (!handle_)
    {
      return 0;
    }
    return xMessageBufferSpacesAvailable(handle_);
  }

  bool reset()
  {
    if (!handle_)
    {
      return false;
    }
    return xMessageBufferReset(handle_) == pdPASS;
  }

  MessageBufferHandle_t raw() const { return handle_; }

 private:
  void destroy()
  {
    if (handle_)
    {
      vMessageBufferDelete(handle_);
      handle_ = nullptr;
    }
    static_buffer_ = nullptr;
    static_control_ = nullptr;
  }

  MessageBufferHandle_t handle_ = nullptr;
  uint8_t *static_buffer_ = nullptr;
  StaticMessageBuffer_t *static_control_ = nullptr;
};

}  // namespace EspHelper
