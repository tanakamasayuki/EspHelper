#include <M5Unified.h>
#include <EspHelperQrCode.h>

EspHelper::QrCodeBitmap qr;

void drawQrOnDisplay()
{
  if (!qr.ready())
  {
    return;
  }
  int size = qr.size();
  int margin = 10;
  int usable = std::min(M5.Display.width(), M5.Display.height()) - margin * 2;
  int scale = std::max(2, usable / size);
  int offsetX = (M5.Display.width() - size * scale) / 2;
  int offsetY = (M5.Display.height() - size * scale) / 2;

  M5.Display.fillScreen(TFT_WHITE);
  M5.Display.setTextDatum(middle_center);
  M5.Display.setTextColor(TFT_BLACK);
  M5.Display.drawString("Scan me!", M5.Display.width() / 2, offsetY - 16);

  qr.forEachModule([&](int x, int y, bool on)
                   {
    uint16_t color = on ? TFT_BLACK : TFT_WHITE;
    M5.Display.fillRect(offsetX + x * scale, offsetY + y * scale, scale, scale, color); });
}

void setup()
{
  auto cfg = M5.config();
  M5.begin(cfg);
  M5.Display.setRotation(1);

  const char *wifiPayload = "WIFI:T:WPA;S:ESPHelperDemo;P:12345678;;";
  if (!qr.generate(wifiPayload, 8, ESP_QRCODE_ECC_QUART))
  {
    M5.Display.println("Failed to create QR");
    return;
  }

  drawQrOnDisplay();
}

void loop()
{
  M5.delay(16);
}
