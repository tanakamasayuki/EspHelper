#pragma once

#include <Arduino.h>
extern "C"
{
#include <cJSON.h>
}

#include <utility>

namespace EspHelper
{

  /**
   * @brief RAII wrapper around cJSON nodes with Arduino-friendly helpers.
   */
  class CJsonDocument
  {
  public:
    CJsonDocument() = default;
    explicit CJsonDocument(cJSON *root) : root_(root) {}

    static CJsonDocument NewObject() { return CJsonDocument(cJSON_CreateObject()); }
    static CJsonDocument NewArray() { return CJsonDocument(cJSON_CreateArray()); }

    static CJsonDocument Parse(const char *json) { return CJsonDocument(json ? cJSON_Parse(json) : nullptr); }
    static CJsonDocument Parse(const String &json) { return Parse(json.c_str()); }

    CJsonDocument(const CJsonDocument &) = delete;
    CJsonDocument &operator=(const CJsonDocument &) = delete;

    CJsonDocument(CJsonDocument &&other) noexcept { moveFrom(other); }
    CJsonDocument &operator=(CJsonDocument &&other) noexcept
    {
      if (this != &other)
      {
        reset();
        moveFrom(other);
      }
      return *this;
    }

    ~CJsonDocument() { reset(); }

    bool valid() const { return root_ != nullptr; }
    bool isObject() const { return cJSON_IsObject(root_); }
    bool isArray() const { return cJSON_IsArray(root_); }

    cJSON *root() { return root_; }
    const cJSON *root() const { return root_; }

    void reset(cJSON *replacement = nullptr)
    {
      if (root_)
      {
        cJSON_Delete(root_);
      }
      root_ = replacement;
    }

    cJSON *release()
    {
      cJSON *tmp = root_;
      root_ = nullptr;
      return tmp;
    }

    String toString(bool pretty = false) const
    {
      if (!root_)
      {
        return String();
      }
      char *raw = pretty ? cJSON_Print(root_) : cJSON_PrintUnformatted(root_);
      String out = raw ? String(raw) : String();
      if (raw)
      {
        cJSON_free(raw);
      }
      return out;
    }

    bool addString(const char *name, const char *value) { return addItem(name, cJSON_CreateString(value)); }
    bool addNumber(const char *name, double value) { return addItem(name, cJSON_CreateNumber(value)); }
    bool addBool(const char *name, bool value) { return addItem(name, cJSON_CreateBool(value)); }
    bool addNull(const char *name) { return addItem(name, cJSON_CreateNull()); }
    bool addObject(const char *name, CJsonDocument &&doc) { return addTransferredItem(name, std::move(doc)); }
    bool addArray(const char *name, CJsonDocument &&doc) { return addTransferredItem(name, std::move(doc)); }

    bool arrayAddNumber(double value) { return appendToArray(cJSON_CreateNumber(value)); }
    bool arrayAddString(const char *value) { return appendToArray(cJSON_CreateString(value)); }
    bool arrayAddBool(bool value) { return appendToArray(cJSON_CreateBool(value)); }
    bool arrayAddNull() { return appendToArray(cJSON_CreateNull()); }
    bool arrayAdd(CJsonDocument &&doc) { return appendTransferredToArray(std::move(doc)); }

    bool getString(const char *name, String &out) const
    {
      const cJSON *node = getObjectItem(name);
      if (!cJSON_IsString(node) || !node->valuestring)
      {
        return false;
      }
      out = node->valuestring;
      return true;
    }

    bool getNumber(const char *name, double &out) const
    {
      const cJSON *node = getObjectItem(name);
      if (!cJSON_IsNumber(node))
      {
        return false;
      }
      out = node->valuedouble;
      return true;
    }

    bool getBool(const char *name, bool &out) const
    {
      const cJSON *node = getObjectItem(name);
      if (!cJSON_IsBool(node))
      {
        return false;
      }
      out = cJSON_IsTrue(node);
      return true;
    }

    size_t arraySize() const { return cJSON_IsArray(root_) ? cJSON_GetArraySize(root_) : 0; }
    const cJSON *arrayItem(int index) const { return cJSON_IsArray(root_) ? cJSON_GetArrayItem(root_, index) : nullptr; }

  private:
    bool addItem(const char *name, cJSON *item)
    {
      if (!root_ || !cJSON_IsObject(root_))
      {
        if (item)
          cJSON_Delete(item);
        return false;
      }
      if (!item)
      {
        return false;
      }
      cJSON_AddItemToObject(root_, name, item);
      return true;
    }

    bool addTransferredItem(const char *name, CJsonDocument &&doc)
    {
      if (!root_ || !cJSON_IsObject(root_) || !doc.root_)
      {
        return false;
      }
      cJSON_AddItemToObject(root_, name, doc.release());
      return true;
    }

    bool appendToArray(cJSON *item)
    {
      if (!root_ || !cJSON_IsArray(root_) || !item)
      {
        if (item)
          cJSON_Delete(item);
        return false;
      }
      cJSON_AddItemToArray(root_, item);
      return true;
    }

    bool appendTransferredToArray(CJsonDocument &&doc)
    {
      if (!root_ || !cJSON_IsArray(root_) || !doc.root_)
      {
        return false;
      }
      cJSON_AddItemToArray(root_, doc.release());
      return true;
    }

    const cJSON *getObjectItem(const char *name) const
    {
      if (!root_ || !cJSON_IsObject(root_))
      {
        return nullptr;
      }
      return cJSON_GetObjectItemCaseSensitive(root_, name);
    }

    void moveFrom(CJsonDocument &other)
    {
      root_ = other.root_;
      other.root_ = nullptr;
    }

    cJSON *root_ = nullptr;
  };

} // namespace EspHelper
