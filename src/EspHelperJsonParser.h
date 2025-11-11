#pragma once

#include <Arduino.h>
#include <json_parser.h>

#include <cstring>
#include <memory>

namespace EspHelper
{

  /**
   * @brief Thin Arduino-friendly wrapper around the ESP-IDF json_parser component.
   *
   * The class owns (or borrows) a token buffer that json_parser uses when walking a JSON string.
   * Use the helper methods to fetch primitive values or enter named objects/arrays.
   */
  class JsonParser
  {
  public:
    JsonParser(json_tok_t *tokens, size_t tokenCount)
        : tokens_(tokens), token_count_(tokenCount) {}

    template <size_t TokenCount>
    explicit JsonParser(json_tok_t (&tokens)[TokenCount])
        : JsonParser(static_cast<json_tok_t *>(tokens), TokenCount) {}

    explicit JsonParser(size_t tokenCount)
        : owned_tokens_(new json_tok_t[tokenCount]),
          tokens_(owned_tokens_.get()),
          token_count_(tokenCount) {}

    ~JsonParser() { end(); }

    JsonParser(const JsonParser &) = delete;
    JsonParser &operator=(const JsonParser &) = delete;
    JsonParser(JsonParser &&) = delete;
    JsonParser &operator=(JsonParser &&) = delete;

    bool parse(const char *json, size_t length = 0)
    {
      end();
      if (!json || !tokens_ || token_count_ == 0)
      {
        return false;
      }
      if (length == 0)
      {
        length = std::strlen(json);
      }
      int rc = json_parse_start_static(&ctx_, json, static_cast<int>(length), tokens_, static_cast<int>(token_count_));
      active_ = (rc == OS_SUCCESS);
      return active_;
    }

    bool parse(const String &json) { return parse(json.c_str(), json.length()); }

    void end()
    {
      if (active_)
      {
        json_parse_end_static(&ctx_);
        active_ = false;
      }
    }

    bool parsed() const { return active_; }

    jparse_ctx_t *raw() { return active_ ? &ctx_ : nullptr; }

    bool enterObject(const char *name) { return call(json_obj_get_object, name); }
    bool leaveObject() { return call(json_obj_leave_object); }

    bool enterArray(const char *name, int *numElements = nullptr)
    {
      int count = 0;
      if (json_obj_get_array(&ctx_, name, &count) != OS_SUCCESS)
      {
        return false;
      }
      if (numElements)
      {
        *numElements = count;
      }
      return true;
    }

    bool leaveArray() { return call(json_obj_leave_array); }

    bool arrayEnter(uint32_t index) { return call(json_arr_get_array, index); }
    bool arrayLeave() { return call(json_arr_leave_array); }
    bool arrayEnterObject(uint32_t index) { return call(json_arr_get_object, index); }
    bool arrayLeaveObject() { return call(json_arr_leave_object); }

    bool getBool(const char *name, bool &value) { return call(json_obj_get_bool, name, &value); }
    bool getInt(const char *name, int &value) { return call(json_obj_get_int, name, &value); }
    bool getInt64(const char *name, int64_t &value) { return call(json_obj_get_int64, name, &value); }
    bool getFloat(const char *name, float &value) { return call(json_obj_get_float, name, &value); }
    bool getString(const char *name, char *out, size_t size)
    {
      return json_obj_get_string(&ctx_, name, out, static_cast<int>(size)) == OS_SUCCESS;
    }
    bool getString(const char *name, String &out)
    {
      return fetchDynamicString(
          [name](jparse_ctx_t *ctx, int *len)
          { return json_obj_get_strlen(ctx, name, len); },
          [name](jparse_ctx_t *ctx, char *buf, int size)
          { return json_obj_get_string(ctx, name, buf, size); }, out);
    }

    bool arrayGetBool(uint32_t index, bool &value) { return call(json_arr_get_bool, index, &value); }
    bool arrayGetInt(uint32_t index, int &value) { return call(json_arr_get_int, index, &value); }
    bool arrayGetInt64(uint32_t index, int64_t &value) { return call(json_arr_get_int64, index, &value); }
    bool arrayGetFloat(uint32_t index, float &value) { return call(json_arr_get_float, index, &value); }
    bool arrayGetString(uint32_t index, char *out, size_t size)
    {
      return json_arr_get_string(&ctx_, index, out, static_cast<int>(size)) == OS_SUCCESS;
    }
    bool arrayGetString(uint32_t index, String &out)
    {
      return fetchDynamicString(
          [index](jparse_ctx_t *ctx, int *len)
          { return json_arr_get_strlen(ctx, index, len); },
          [index](jparse_ctx_t *ctx, char *buf, int size)
          { return json_arr_get_string(ctx, index, buf, size); }, out);
    }

  private:
    template <typename Fn, typename... Args>
    bool call(Fn fn, Args... args)
    {
      if (!active_)
      {
        return false;
      }
      return fn(&ctx_, args...) == OS_SUCCESS;
    }

    template <typename LengthFn, typename ValueFn>
    bool fetchDynamicString(LengthFn lengthFn, ValueFn valueFn, String &out)
    {
      if (!active_)
      {
        return false;
      }
      int len = 0;
      if (lengthFn(&ctx_, &len) != OS_SUCCESS || len < 0)
      {
        return false;
      }
      std::unique_ptr<char[]> temp(new char[len + 1]);
      if (!temp)
      {
        return false;
      }
      if (valueFn(&ctx_, temp.get(), len + 1) != OS_SUCCESS)
      {
        return false;
      }
      out = temp.get();
      return true;
    }

    jparse_ctx_t ctx_{};
    std::unique_ptr<json_tok_t[]> owned_tokens_;
    json_tok_t *tokens_ = nullptr;
    size_t token_count_ = 0;
    bool active_ = false;
  };

} // namespace EspHelper
