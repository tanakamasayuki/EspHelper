#pragma once

#include <Arduino.h>

namespace EspHelper
{

  class Task
  {
  public:
    using TaskFunc = std::function<void()>;

    Task() = default;

    Task(Task &&other) noexcept { moveFrom(other); }
    Task &operator=(Task &&other) noexcept
    {
      if (this != &other)
      {
        destroy();
        moveFrom(other);
      }
      return *this;
    }

    ~Task() { destroy(); }

    bool start(const char *name, TaskFunc func, uint32_t stackSize = 4096, UBaseType_t priority = 1, BaseType_t core = tskNO_AFFINITY)
    {
      if (!func)
      {
        return false;
      }
      destroy();
      func_ = std::move(func);
      BaseType_t ok = xTaskCreatePinnedToCore(&Task::dispatch, name ? name : "EspHelperTask", stackSize, this, priority, &handle_, core);
      return ok == pdPASS;
    }

    void stop()
    {
      destroy();
    }

    bool running() const { return handle_ != nullptr; }

  private:
    static void dispatch(void *arg)
    {
      Task *self = static_cast<Task *>(arg);
      if (!self)
      {
        vTaskDelete(nullptr);
        return;
      }
      self->func_();
      self->handle_ = nullptr;
      vTaskDelete(nullptr);
    }

    void destroy()
    {
      if (handle_)
      {
        vTaskDelete(handle_);
        handle_ = nullptr;
      }
      func_ = nullptr;
    }

    void moveFrom(Task &other)
    {
      handle_ = other.handle_;
      func_ = std::move(other.func_);
      other.handle_ = nullptr;
    }

    TaskFunc func_{};
    TaskHandle_t handle_ = nullptr;
  };

} // namespace EspHelper
