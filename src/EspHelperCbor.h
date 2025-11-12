#pragma once

#include <Arduino.h>
#include <vector>

extern "C" {
#include <cbor.h>
#include <cborjson.h>
}

namespace EspHelper {

class CborWriter {
 public:
  bool begin(uint8_t *buffer, size_t length)
  {
    if (!buffer || length == 0)
    {
      return false;
    }
    buffer_ = buffer;
    capacity_ = length;
    stack_.clear();
    stack_.emplace_back();
    cbor_encoder_init(&stack_[0], buffer_, length, 0);
    started_ = true;
    finished_ = false;
    return true;
  }

  bool startMap(size_t length = CborIndefiniteLength) { return startContainer(true, length); }
  bool startArray(size_t length = CborIndefiniteLength) { return startContainer(false, length); }

  bool endContainer()
  {
    if (!started_ || stack_.size() <= 1)
    {
      return false;
    }
    CborEncoder child = stack_.back();
    stack_.pop_back();
    CborEncoder &parent = stack_.back();
    CborError err = cbor_encoder_close_container_checked(&parent, &child);
    if (stack_.size() == 1)
    {
      finished_ = true;
    }
    return err == CborNoError;
  }

  bool add(const char *value) { return encodeText(value); }
  bool add(const String &value) { return encodeText(value.c_str()); }

  bool add(int64_t value)
  {
    if (!readyForValue())
    {
      return false;
    }
    return cbor_encode_int(current(), value) == CborNoError;
  }

  bool add(uint64_t value)
  {
    if (!readyForValue())
    {
      return false;
    }
    return cbor_encode_uint(current(), value) == CborNoError;
  }

  bool add(bool value)
  {
    if (!readyForValue())
    {
      return false;
    }
    return cbor_encode_boolean(current(), value) == CborNoError;
  }

  bool addNull()
  {
    if (!readyForValue())
    {
      return false;
    }
    return cbor_encode_null(current()) == CborNoError;
  }

  bool addBytes(const uint8_t *data, size_t length)
  {
    if (!readyForValue() || (!data && length > 0))
    {
      return false;
    }
    return cbor_encode_byte_string(current(), data, length) == CborNoError;
  }

  bool addKeyValue(const char *key, const char *value)
  {
    return addKey(key) && add(value);
  }

  bool addKeyValue(const char *key, const String &value)
  {
    return addKey(key) && add(value);
  }

  bool addKeyValue(const char *key, int64_t value)
  {
    return addKey(key) && add(value);
  }

  bool addKeyValue(const char *key, uint64_t value)
  {
    return addKey(key) && add(value);
  }

  bool addKeyValue(const char *key, bool value)
  {
    return addKey(key) && add(value);
  }

  bool finish()
  {
    while (stack_.size() > 1)
    {
      if (!endContainer())
      {
        return false;
      }
    }
    finished_ = true;
    return true;
  }

  size_t bytesWritten() const
  {
    if (!started_ || stack_.empty())
    {
      return 0;
    }
    return cbor_encoder_get_buffer_size(&stack_.front(), buffer_);
  }

 private:
  bool startContainer(bool isMap, size_t length)
  {
    if (!started_ || stack_.empty())
    {
      return false;
    }
    CborEncoder child{};
    CborError err = isMap ? cbor_encoder_create_map(current(), &child, length)
                          : cbor_encoder_create_array(current(), &child, length);
    if (err != CborNoError)
    {
      return false;
    }
    stack_.push_back(child);
    finished_ = false;
    return true;
  }

  bool addKey(const char *key)
  {
    if (!readyForValue() || !key)
    {
      return false;
    }
    return cbor_encode_text_stringz(current(), key) == CborNoError;
  }

  bool encodeText(const char *value)
  {
    if (!readyForValue() || !value)
    {
      return false;
    }
    return cbor_encode_text_stringz(current(), value) == CborNoError;
  }

  bool readyForValue() const
  {
    return started_ && !stack_.empty();
  }

  CborEncoder *current()
  {
    return stack_.empty() ? nullptr : &stack_.back();
  }

  std::vector<CborEncoder> stack_;
  uint8_t *buffer_ = nullptr;
  size_t capacity_ = 0;
  bool started_ = false;
  bool finished_ = false;
};

class CborReader {
 public:
  bool begin(const uint8_t *buffer, size_t length)
  {
    if (!buffer || length == 0)
    {
      return false;
    }
    CborError err = cbor_parser_init(buffer, length, 0, &parser_, &root_);
    parsed_ = (err == CborNoError);
    return parsed_;
  }

  bool isMap() const { return parsed_ && cbor_value_is_map(&root_); }

  bool getString(const char *key, String &out) const
  {
    CborValue value;
    if (!locateKey(key, value) || !cbor_value_is_text_string(&value))
    {
      return false;
    }
    size_t length = 0;
    if (cbor_value_calculate_string_length(&value, &length) != CborNoError)
    {
      return false;
    }
    std::vector<char> buffer(length + 1, 0);
    if (cbor_value_copy_text_string(&value, buffer.data(), &length, nullptr) != CborNoError)
    {
      return false;
    }
    out = buffer.data();
    return true;
  }

  bool getInt(const char *key, int64_t &out) const
  {
    CborValue value;
    if (!locateKey(key, value))
    {
      return false;
    }
    if (cbor_value_is_unsigned_integer(&value))
    {
      uint64_t tmp = 0;
      if (cbor_value_get_uint64(&value, &tmp) != CborNoError)
      {
        return false;
      }
      out = static_cast<int64_t>(tmp);
      return true;
    }
    if (cbor_value_is_integer(&value))
    {
      return cbor_value_get_int64(&value, &out) == CborNoError;
    }
    return false;
  }

  bool getBool(const char *key, bool &out) const
  {
    CborValue value;
    if (!locateKey(key, value) || !cbor_value_is_boolean(&value))
    {
      return false;
    }
    return cbor_value_get_boolean(&value, &out) == CborNoError;
  }

 private:
  bool locateKey(const char *key, CborValue &out) const
  {
    if (!parsed_ || !key || !cbor_value_is_map(&root_))
    {
      return false;
    }
    CborValue map;
    if (cbor_value_enter_container(&root_, &map) != CborNoError)
    {
      return false;
    }
    while (!cbor_value_at_end(&map))
    {
      CborValue keyValue = map;
      size_t keyLen = 0;
      if (cbor_value_calculate_string_length(&keyValue, &keyLen) != CborNoError)
      {
        return false;
      }
      std::vector<char> tmp(keyLen + 1, 0);
      if (cbor_value_copy_text_string(&map, tmp.data(), &keyLen, &map) != CborNoError)
      {
        return false;
      }
      if (strcmp(tmp.data(), key) == 0)
      {
        out = map;
        return true;
      }
      if (cbor_value_advance_fixed(&map) != CborNoError)
      {
        return false;
      }
    }
    return false;
  }

  mutable CborParser parser_{};
  mutable CborValue root_{};
  bool parsed_ = false;
};

}  // namespace EspHelper

