#pragma once

#include <Arduino.h>
#include <json_generator.h>

#include <cstring>
#include <memory>

namespace EspHelper
{

  /**
   * @brief Header-only wrapper over esp-idf json_generator that works in both static-buffer
   * and streaming scenarios. Supply either a buffer pointer/capacity or a Print reference.
   */
  class JsonGenerator
  {
  public:
    JsonGenerator(char *buffer, size_t capacity, json_gen_flush_cb_t flush = nullptr, void *priv = nullptr)
        : buffer_(buffer), capacity_(capacity), flush_cb_(flush), flush_priv_(priv)
    {
      start();
    }

    template <size_t BufferSize>
    explicit JsonGenerator(char (&buffer)[BufferSize], json_gen_flush_cb_t flush = nullptr, void *priv = nullptr)
        : JsonGenerator(static_cast<char *>(buffer), BufferSize, flush, priv) {}

    explicit JsonGenerator(Print &out, size_t chunkSize = 128)
        : owned_buffer_(new char[chunkSize]),
          buffer_(owned_buffer_.get()),
          capacity_(chunkSize),
          flush_cb_(&JsonGenerator::streamFlushThunk),
          flush_priv_(this),
          stream_(&out)
    {
      start();
    }

    void reset() { start(); }

    void reset(json_gen_flush_cb_t flush, void *priv = nullptr)
    {
      if (!stream_)
      {
        flush_cb_ = flush;
        flush_priv_ = priv;
      }
      start();
    }

    void reset(char *buffer, size_t capacity, json_gen_flush_cb_t flush = nullptr, void *priv = nullptr)
    {
      if (stream_)
      {
        return;
      }
      buffer_ = buffer;
      capacity_ = capacity;
      flush_cb_ = flush;
      flush_priv_ = priv;
      start();
    }

    template <size_t BufferSize>
    void reset(char (&buffer)[BufferSize], json_gen_flush_cb_t flush = nullptr, void *priv = nullptr)
    {
      reset(static_cast<char *>(buffer), BufferSize, flush, priv);
    }

    int finish()
    {
      if (!finished_ && buffer_)
      {
        length_ = json_gen_str_end(&jstr_);
        finished_ = true;
      }
      return length_;
    }

    ~JsonGenerator() { finish(); }

    JsonGenerator(const JsonGenerator &) = delete;
    JsonGenerator &operator=(const JsonGenerator &) = delete;

    JsonGenerator(JsonGenerator &&) = delete;
    JsonGenerator &operator=(JsonGenerator &&) = delete;

    bool valid() const { return buffer_ && capacity_ > 0; }

    char *data() { return buffer_; }
    const char *c_str() const { return buffer_; }
    size_t capacity() const { return capacity_; }
    size_t length() const
    {
      if (!buffer_)
      {
        return 0;
      }
      if (finished_ && length_ > 0)
      {
        return static_cast<size_t>(length_ - 1);
      }
      return std::strlen(buffer_);
    }

    json_gen_str_t *raw() { return &jstr_; }

    int startObject() { return json_gen_start_object(&jstr_); }
    int endObject() { return json_gen_end_object(&jstr_); }
    int pushObject(const char *name) { return json_gen_push_object(&jstr_, name); }
    int popObject() { return json_gen_pop_object(&jstr_); }

    int startArray() { return json_gen_start_array(&jstr_); }
    int endArray() { return json_gen_end_array(&jstr_); }
    int pushArray(const char *name) { return json_gen_push_array(&jstr_, name); }
    int popArray() { return json_gen_pop_array(&jstr_); }

    int setBool(const char *name, bool value) { return json_gen_obj_set_bool(&jstr_, name, value); }
    int setInt(const char *name, int value) { return json_gen_obj_set_int(&jstr_, name, value); }
    int setFloat(const char *name, float value) { return json_gen_obj_set_float(&jstr_, name, value); }
    int setString(const char *name, const char *value) { return json_gen_obj_set_string(&jstr_, name, value); }
    int setString(const char *name, const String &value) { return json_gen_obj_set_string(&jstr_, name, value.c_str()); }
    int setNull(const char *name) { return json_gen_obj_set_null(&jstr_, name); }

    int arrayAddBool(bool value) { return json_gen_arr_set_bool(&jstr_, value); }
    int arrayAddInt(int value) { return json_gen_arr_set_int(&jstr_, value); }
    int arrayAddFloat(float value) { return json_gen_arr_set_float(&jstr_, value); }
    int arrayAddString(const char *value) { return json_gen_arr_set_string(&jstr_, value); }
    int arrayAddString(const String &value) { return json_gen_arr_set_string(&jstr_, value.c_str()); }
    int arrayAddNull() { return json_gen_arr_set_null(&jstr_); }

  private:
    void start()
    {
      finished_ = false;
      length_ = 0;
      if (!buffer_ || capacity_ == 0)
      {
        return;
      }
      buffer_[0] = '\0';
      json_gen_str_start(&jstr_, buffer_, static_cast<int>(capacity_), flush_cb_, flush_priv_);
    }

    static void streamFlushThunk(char *buf, void *priv)
    {
      if (!priv || !buf)
      {
        return;
      }
      auto self = static_cast<JsonGenerator *>(priv);
      if (!self->stream_)
      {
        return;
      }
      self->stream_->print(buf);
      buf[0] = '\0';
    }

    json_gen_str_t jstr_{};
    std::unique_ptr<char[]> owned_buffer_;
    char *buffer_ = nullptr;
    size_t capacity_ = 0;
    bool finished_ = false;
    int length_ = 0;
    json_gen_flush_cb_t flush_cb_ = nullptr;
    void *flush_priv_ = nullptr;
    Print *stream_ = nullptr;
  };

} // namespace EspHelper
