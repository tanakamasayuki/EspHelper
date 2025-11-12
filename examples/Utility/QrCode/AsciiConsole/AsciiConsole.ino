#include <EspHelperQrCode.h>

EspHelper::QrCodeBitmap qr;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  const char *text = "https://github.com/tanakamasayuki/EspHelper";
  if (!qr.generate(text, 6, ESP_QRCODE_ECC_MED))
  {
    Serial.println("Failed to generate QR code");
    return;
  }

  Serial.println("ASCII QR Code:\n");
  Serial.println(qr.toAscii());

  delay(5000);
}
