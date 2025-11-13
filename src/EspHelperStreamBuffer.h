#pragma once

#include <Arduino.h>
#include <freertos/stream_buffer.h>

namespace EspHelper
{

  class StreamBuffer
  {
  public:
    StreamBuffer() = default;
    ~StreamBuffer() { destroy(); }

    bool create(size_t capacity, size_t triggerLevel = 1)
    {
      destroy();
      handle_ = xStreamBufferCreate(capacity, triggerLevel);
      return handle_ != nullptr;
    }

    bool createStatic(size_t capacity,
                      uint8_t *storage,
                      StaticStreamBuffer_t *control,
                      size_t triggerLevel = 1)
    {
      if (!storage || !control)
      {
        return false;
      }
      destroy();
      handle_ = xStreamBufferCreateStatic(capacity, triggerLevel, storage, control);
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
      return xStreamBufferSend(handle_, data, length, ticks);
    }

    size_t sendFromISR(const void *data, size_t length, BaseType_t *hpTaskWoken = nullptr)
    {
      if (!handle_ || !data || length == 0)
      {
        return 0;
      }
      BaseType_t taskWoken = pdFALSE;
      size_t written = xStreamBufferSendFromISR(handle_, data, length, &taskWoken);
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
      return xStreamBufferReceive(handle_, data, maxLength, ticks);
    }

    size_t receiveFromISR(void *data, size_t maxLength, BaseType_t *hpTaskWoken = nullptr)
    {
      if (!handle_ || !data || maxLength == 0)
      {
        return 0;
      }
      BaseType_t taskWoken = pdFALSE;
      size_t read = xStreamBufferReceiveFromISR(handle_, data, maxLength, &taskWoken);
      if (hpTaskWoken)
      {
        *hpTaskWoken = taskWoken;
      }
      return read;
    }

    size_t bytesAvailable() const
    {
      return handle_ ? xStreamBufferBytesAvailable(handle_) : 0;
    }

    size_t spacesAvailable() const
    {
      return handle_ ? xStreamBufferSpacesAvailable(handle_) : 0;
    }

    bool reset()
    {
      if (!handle_)
      {
        return false;
      }
      return xStreamBufferReset(handle_) == pdPASS;
    }

    StreamBufferHandle_t raw() const { return handle_; }

  private:
    void destroy()
    {
      if (handle_)
      {
        vStreamBufferDelete(handle_);
        handle_ = nullptr;
      }
      static_buffer_ = nullptr;
      static_control_ = nullptr;
    }

    StreamBufferHandle_t handle_ = nullptr;
    uint8_t *static_buffer_ = nullptr;
    StaticStreamBuffer_t *static_control_ = nullptr;
  };

} // namespace EspHelper
