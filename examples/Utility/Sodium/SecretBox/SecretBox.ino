#include <EspHelperSodium.h>

EspHelper::SecretBox secretBox;
uint8_t ciphertext[128];
uint8_t decrypted[128];
uint8_t nonce[crypto_secretbox_NONCEBYTES];

void printHex(const char *label, const uint8_t *data, size_t length)
{
  Serial.print(label);
  for (size_t i = 0; i < length; ++i)
  {
    if (i % 32 == 0)
    {
      Serial.println();
    }
    Serial.printf("%02x", data[i]);
  }
  Serial.println();
}

void setup()
{
  Serial.begin(115200);
  if (!EspHelper::Sodium::init())
  {
    Serial.println(F("libsodium init failed"));
    while (true)
    {
      delay(1000);
    }
  }

  if (!secretBox.generateKey())
  {
    Serial.println(F("Failed to generate key"));
    return;
  }

  const char *message = "hello from EspHelper secretbox";
  const size_t plainLen = strlen(message);
  const size_t cipherLen = plainLen + crypto_secretbox_MACBYTES;

  if (!secretBox.encrypt(reinterpret_cast<const uint8_t *>(message), plainLen, ciphertext, nonce))
  {
    Serial.println(F("Encryption failed"));
    return;
  }

  printHex("Nonce:", nonce, crypto_secretbox_NONCEBYTES);
  printHex("Ciphertext:", ciphertext, cipherLen);

  if (secretBox.decrypt(ciphertext, cipherLen, nonce, decrypted))
  {
    decrypted[plainLen] = '\0';
    Serial.print(F("Decrypted: "));
    Serial.println(reinterpret_cast<char *>(decrypted));
  }
  else
  {
    Serial.println(F("Decryption failed"));
  }
}

void loop()
{
}
