#include <WiFi.h>
#include <EspHelperHttpServer.h>

#if __has_include("arduino_secrets.h")
#include "arduino_secrets.h"
#else
#define WIFI_SSID "YourSSID"     // Enter your Wi-Fi SSID here / Wi-FiのSSIDを入力
#define WIFI_PASS "YourPassword" // Enter your Wi-Fi password here / Wi-Fiのパスワードを入力
#endif

EspHelper::HttpServer server;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.print("Ready at http://");
  Serial.println(WiFi.localIP());

  server.onGet("/", [](httpd_req_t *req)
               {
    const char *html = "<html><body><h1>EspHelper</h1><p>Hello from esp_http_server!</p></body></html>";
    httpd_resp_set_type(req, "text/html");
    return httpd_resp_send(req, html, HTTPD_RESP_USE_STRLEN); });

  server.onPost("/echo", [](httpd_req_t *req)
                {
    char buf[256];
    int received = httpd_req_recv(req, buf, sizeof(buf));
    if (received <= 0)
    {
      return httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "No body");
    }
    buf[received] = '\0';
    httpd_resp_set_type(req, "text/plain");
    return httpd_resp_send(req, buf, received); });

  if (!server.start())
  {
    Serial.println("Failed to start HTTP server");
  }
}

void loop()
{
}
