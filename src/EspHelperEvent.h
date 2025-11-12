#pragma once

#include <Arduino.h>
extern "C" {
#include <esp_event.h>
}

namespace EspHelper {

class EventLoop {
 public:
  EventLoop() = default;
  ~EventLoop() { end(); }

  bool createDefault()
  {
    end();
    esp_err_t err = esp_event_loop_create_default();
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE)
    {
      return false;
    }
    esp_event_loop_handle_t handle = nullptr;
    if (esp_event_loop_get_handle(&handle) != ESP_OK || handle == nullptr)
    {
      return false;
    }
    handle_ = handle;
    owns_loop_ = false;
    default_loop_ = true;
    created_default_ = (err == ESP_OK);
    return true;
  }

  bool createCustom(const esp_event_loop_args_t &args)
  {
    end();
    esp_event_loop_handle_t handle = nullptr;
    if (esp_event_loop_create(&args, &handle) != ESP_OK)
    {
      return false;
    }
    handle_ = handle;
    owns_loop_ = true;
    default_loop_ = false;
    created_default_ = false;
    return true;
  }

  void end()
  {
    if (handle_)
    {
      if (owns_loop_)
      {
        esp_event_loop_delete(handle_);
      }
      else if (default_loop_ && created_default_)
      {
        esp_event_loop_delete_default();
      }
    }
    handle_ = nullptr;
    owns_loop_ = false;
    default_loop_ = false;
    created_default_ = false;
  }

  bool valid() const { return handle_ != nullptr; }

  bool registerHandler(esp_event_base_t base,
                       int32_t id,
                       esp_event_handler_t handler,
                       void *arg = nullptr,
                       esp_event_handler_instance_t *out_instance = nullptr)
  {
    if (!handle_ || handler == nullptr)
    {
      return false;
    }
    return esp_event_handler_instance_register_with(handle_, base, id, handler, arg, out_instance) == ESP_OK;
  }

  bool unregisterHandler(esp_event_base_t base, int32_t id, esp_event_handler_instance_t instance)
  {
    if (!handle_ || instance == nullptr)
    {
      return false;
    }
    return esp_event_handler_instance_unregister_with(handle_, base, id, instance) == ESP_OK;
  }

  bool post(esp_event_base_t base,
            int32_t id,
            const void *event_data = nullptr,
            size_t event_data_size = 0,
            TickType_t ticks_to_wait = portMAX_DELAY)
  {
    if (!handle_)
    {
      return false;
    }
    return esp_event_post_to(handle_, base, id, event_data, event_data_size, ticks_to_wait) == ESP_OK;
  }

  esp_event_loop_handle_t raw() const { return handle_; }

 private:
  esp_event_loop_handle_t handle_ = nullptr;
  bool owns_loop_ = false;
  bool default_loop_ = false;
  bool created_default_ = false;
};

}  // namespace EspHelper

