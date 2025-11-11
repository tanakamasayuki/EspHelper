#pragma once

#include <Arduino.h>
#include <freertos/ringbuf.h>

#include <esp_err.h>

namespace EspHelper
{

  class RingbufferItem
  {
  public:
    RingbufferItem() = default;
    RingbufferItem(RingbufHandle_t handle, void *data, size_t size)
        : handle_(handle), data_(static_cast<uint8_t *>(data)), size_(size) {}
    RingbufferItem(const RingbufferItem &) = delete;
    RingbufferItem &operator=(const RingbufferItem &) = delete;
    RingbufferItem(RingbufferItem &&other) noexcept { moveFrom(other); }
    RingbufferItem &operator=(RingbufferItem &&other) noexcept
    {
      if (this != &other)
      {
        release();
        moveFrom(other);
      }
      return *this;
    }
    ~RingbufferItem() { release(); }

    bool valid() const { return data_ != nullptr; }
    uint8_t *data() { return data_; }
    const uint8_t *data() const { return data_; }
    size_t size() const { return size_; }

    void release()
    {
      if (handle_ && data_)
      {
        vRingbufferReturnItem(handle_, data_);
        data_ = nullptr;
        size_ = 0;
      }
    }

  private:
    void moveFrom(RingbufferItem &other)
    {
      handle_ = other.handle_;
      data_ = other.data_;
      size_ = other.size_;
      other.handle_ = nullptr;
      other.data_ = nullptr;
      other.size_ = 0;
    }

    RingbufHandle_t handle_ = nullptr;
    uint8_t *data_ = nullptr;
    size_t size_ = 0;
  };

  class Ringbuffer
  {
  public:
    Ringbuffer() = default;
    Ringbuffer(size_t bytes, RingbufferType_t type = RINGBUF_TYPE_NOSPLIT)
    {
      init(xRingbufferCreate(bytes, type), true);
    }

    static Ringbuffer NoSplit(size_t itemSize, size_t maxItems)
    {
      Ringbuffer rb;
      rb.init(xRingbufferCreateNoSplit(itemSize, maxItems), true);
      return rb;
    }

    Ringbuffer(uint8_t *storage, size_t bytes, StaticRingbuffer_t &control, RingbufferType_t type = RINGBUF_TYPE_NOSPLIT)
    {
      init(xRingbufferCreateStatic(bytes, type, storage, &control), false);
      owns_handle_ = false;
    }

    explicit Ringbuffer(RingbufHandle_t existing, bool takeOwnership = false) { init(existing, takeOwnership); }

    ~Ringbuffer() { resetHandle(); }

    Ringbuffer(const Ringbuffer &) = delete;
    Ringbuffer &operator=(const Ringbuffer &) = delete;
    Ringbuffer(Ringbuffer &&other) noexcept { moveFrom(other); }
    Ringbuffer &operator=(Ringbuffer &&other) noexcept
    {
      if (this != &other)
      {
        resetHandle();
        moveFrom(other);
      }
      return *this;
    }

    bool valid() const { return handle_ != nullptr; }
    RingbufHandle_t raw() const { return handle_; }

    bool send(const void *data, size_t size, TickType_t ticksToWait = portMAX_DELAY) const
    {
      if (!handle_)
      {
        return false;
      }
      return xRingbufferSend(handle_, data, size, ticksToWait) == pdTRUE;
    }

    bool sendFromISR(const void *data, size_t size, BaseType_t *higherPriorityTaskWoken = nullptr) const
    {
      if (!handle_)
      {
        return false;
      }
      return xRingbufferSendFromISR(handle_, data, size, higherPriorityTaskWoken) == pdTRUE;
    }

    RingbufferItem receive(TickType_t ticksToWait = portMAX_DELAY) const
    {
      if (!handle_)
      {
        return {};
      }
      size_t size = 0;
      void *ptr = xRingbufferReceive(handle_, &size, ticksToWait);
      return RingbufferItem(handle_, ptr, size);
    }

    RingbufferItem receiveFromISR() const
    {
      if (!handle_)
      {
        return {};
      }
      size_t size = 0;
      void *ptr = xRingbufferReceiveFromISR(handle_, &size);
      return RingbufferItem(handle_, ptr, size);
    }

    void adopt(RingbufHandle_t handle, bool takeOwnership)
    {
      resetHandle();
      init(handle, takeOwnership);
    }

  private:
    void init(RingbufHandle_t handle, bool takeOwnership)
    {
      handle_ = handle;
      owns_handle_ = takeOwnership;
    }

    void resetHandle()
    {
      if (handle_ && owns_handle_)
      {
        vRingbufferDelete(handle_);
      }
      handle_ = nullptr;
      owns_handle_ = false;
    }

    void moveFrom(Ringbuffer &other)
    {
      handle_ = other.handle_;
      owns_handle_ = other.owns_handle_;
      other.handle_ = nullptr;
      other.owns_handle_ = false;
    }

    RingbufHandle_t handle_ = nullptr;
    bool owns_handle_ = false;
  };

} // namespace EspHelper
