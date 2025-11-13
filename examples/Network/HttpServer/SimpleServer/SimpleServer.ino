#include <WiFi.h>
#include <EspHelperHttpServer.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

EspHelper::HttpServer server;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
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
