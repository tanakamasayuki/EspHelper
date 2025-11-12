#pragma once

#include <Arduino.h>
extern "C" {
#include <esp_http_server.h>
}

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace EspHelper {

class HttpServer {
 public:
  using Handler = std::function<esp_err_t(httpd_req_t *)>;

  explicit HttpServer(const httpd_config_t &config = HTTPD_DEFAULT_CONFIG()) : config_(config) {}

  ~HttpServer() { stop(); }

  bool start()
  {
    if (server_)
    {
      return true;
    }
    if (httpd_start(&server_, &config_) != ESP_OK)
    {
      server_ = nullptr;
      return false;
    }
    for (auto &entry : handlers_)
    {
      httpd_register_uri_handler(server_, &entry->uriDef);
    }
    return true;
  }

  void stop()
  {
    if (server_)
    {
      httpd_stop(server_);
      server_ = nullptr;
    }
  }

  bool started() const { return server_ != nullptr; }

  bool on(const char *uri, httpd_method_t method, Handler handler)
  {
    if (!uri || !handler)
    {
      return false;
    }
    auto entry = std::make_unique<HandlerEntry>();
    entry->uri = uri;
    entry->method = method;
    entry->handler = std::move(handler);
    entry->uriDef.uri = entry->uri.c_str();
    entry->uriDef.method = method;
    entry->uriDef.handler = &HttpServer::dispatch;
    entry->uriDef.user_ctx = entry.get();
    entry->uriDef.is_websocket = 0;

    if (server_)
    {
      esp_err_t err = httpd_register_uri_handler(server_, &entry->uriDef);
      if (err != ESP_OK)
      {
        return false;
      }
    }

    handlers_.push_back(std::move(entry));
    return true;
  }

  bool onGet(const char *uri, Handler handler) { return on(uri, HTTP_GET, std::move(handler)); }
  bool onPost(const char *uri, Handler handler) { return on(uri, HTTP_POST, std::move(handler)); }
  bool onPut(const char *uri, Handler handler) { return on(uri, HTTP_PUT, std::move(handler)); }
  bool onDelete(const char *uri, Handler handler) { return on(uri, HTTP_DELETE, std::move(handler)); }

  httpd_handle_t raw() const { return server_; }

  static esp_err_t sendText(httpd_req_t *req, const char *text, const char *type = "text/plain")
  {
    httpd_resp_set_type(req, type);
    return httpd_resp_send(req, text, HTTPD_RESP_USE_STRLEN);
  }

  static esp_err_t sendJson(httpd_req_t *req, const char *json)
  {
    httpd_resp_set_type(req, "application/json");
    return httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN);
  }

  static esp_err_t sendChunk(httpd_req_t *req, const char *chunk)
  {
    return httpd_resp_send_chunk(req, chunk, HTTPD_RESP_USE_STRLEN);
  }

  static esp_err_t sendEmpty(httpd_req_t *req, httpd_resp_status_t status = HTTPD_200)
  {
    httpd_resp_set_status(req, status);
    return httpd_resp_send(req, nullptr, 0);
  }

 private:
  struct HandlerEntry {
    std::string uri;
    httpd_method_t method = HTTP_GET;
    httpd_uri_t uriDef{};
    Handler handler;
  };

  static esp_err_t dispatch(httpd_req_t *req)
  {
    auto *entry = static_cast<HandlerEntry *>(req->user_ctx);
    if (!entry || !entry->handler)
    {
      return ESP_FAIL;
    }
    return entry->handler(req);
  }

  httpd_handle_t server_ = nullptr;
  httpd_config_t config_;
  std::vector<std::unique_ptr<HandlerEntry>> handlers_;
};

}  // namespace EspHelper

