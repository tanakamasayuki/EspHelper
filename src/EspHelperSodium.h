#pragma once

#include <Arduino.h>
#include <array>
#include <vector>

extern "C" {
#include <sodium.h>
}

namespace EspHelper {

class Sodium {
 public:
  static bool init()
  {
    if (initialized_)
    {
      return true;
    }
    if (sodium_init() < 0)
    {
      return false;
    }
    initialized_ = true;
    return true;
  }

  static void randomBytes(uint8_t *buffer, size_t length)
  {
    if (!buffer || length == 0)
    {
      return;
    }
    init();
    randombytes_buf(buffer, length);
  }

  static String toHex(const uint8_t *buffer, size_t length)
  {
    if (!buffer || length == 0)
    {
      return String();
    }
    String hex;
    hex.reserve(length * 2);
    static const char *kDigits = "0123456789abcdef";
    for (size_t i = 0; i < length; ++i)
    {
      uint8_t v = buffer[i];
      hex += kDigits[v >> 4];
      hex += kDigits[v & 0x0F];
    }
    return hex;
  }

  static String randomHex(size_t byteLength)
  {
    if (byteLength == 0)
    {
      return String();
    }
    std::vector<uint8_t> tmp(byteLength, 0);
    randomBytes(tmp.data(), tmp.size());
    return toHex(tmp.data(), tmp.size());
  }

 private:
  static inline bool initialized_ = false;
};

class SecretBox {
 public:
  SecretBox() = default;

  bool generateKey()
  {
    if (!Sodium::init())
    {
      return false;
    }
    randombytes_buf(key_.data(), key_.size());
    has_key_ = true;
    return true;
  }

  bool setKey(const uint8_t key[crypto_secretbox_KEYBYTES])
  {
    if (!key)
    {
      return false;
    }
    memcpy(key_.data(), key, key_.size());
    has_key_ = true;
    return true;
  }

  bool encrypt(const uint8_t *plain,
               size_t plainLength,
               uint8_t *cipher,
               uint8_t nonce[crypto_secretbox_NONCEBYTES]) const
  {
    if (!has_key_ || !plain || !cipher || plainLength == 0 || !nonce)
    {
      return false;
    }
    randombytes_buf(nonce, crypto_secretbox_NONCEBYTES);
    return crypto_secretbox_easy(cipher, plain, plainLength, nonce, key_.data()) == 0;
  }

  bool decrypt(const uint8_t *cipher,
               size_t cipherLength,
               const uint8_t nonce[crypto_secretbox_NONCEBYTES],
               uint8_t *plain) const
  {
    if (!has_key_ || !cipher || !plain || cipherLength < crypto_secretbox_MACBYTES || !nonce)
    {
      return false;
    }
    return crypto_secretbox_open_easy(plain, cipher, cipherLength, nonce, key_.data()) == 0;
  }

  const uint8_t *key() const { return has_key_ ? key_.data() : nullptr; }
  bool hasKey() const { return has_key_; }

 private:
  std::array<uint8_t, crypto_secretbox_KEYBYTES> key_{};
  bool has_key_ = false;
};

class Signer {
 public:
  Signer() = default;

  bool generateKeyPair()
  {
    if (!Sodium::init())
    {
      return false;
    }
    if (crypto_sign_keypair(public_key_.data(), secret_key_.data()) != 0)
    {
      return false;
    }
    has_keys_ = true;
    return true;
  }

  bool setKeyPair(const uint8_t publicKey[crypto_sign_PUBLICKEYBYTES],
                  const uint8_t secretKey[crypto_sign_SECRETKEYBYTES])
  {
    if (!publicKey || !secretKey)
    {
      return false;
    }
    memcpy(public_key_.data(), publicKey, crypto_sign_PUBLICKEYBYTES);
    memcpy(secret_key_.data(), secretKey, crypto_sign_SECRETKEYBYTES);
    has_keys_ = true;
    return true;
  }

  bool sign(const uint8_t *message,
            size_t messageLength,
            uint8_t signature[crypto_sign_BYTES]) const
  {
    if (!has_keys_ || !message || messageLength == 0 || !signature)
    {
      return false;
    }
    unsigned long long sig_len = 0;
    return crypto_sign_detached(signature, &sig_len, message, messageLength, secret_key_.data()) == 0;
  }

  bool verify(const uint8_t *message,
              size_t messageLength,
              const uint8_t signature[crypto_sign_BYTES]) const
  {
    if (!has_keys_ || !message || !signature || messageLength == 0)
    {
      return false;
    }
    return crypto_sign_verify_detached(signature, message, messageLength, public_key_.data()) == 0;
  }

  const uint8_t *publicKey() const { return has_keys_ ? public_key_.data() : nullptr; }
  const uint8_t *secretKey() const { return has_keys_ ? secret_key_.data() : nullptr; }

 private:
  std::array<uint8_t, crypto_sign_PUBLICKEYBYTES> public_key_{};
  std::array<uint8_t, crypto_sign_SECRETKEYBYTES> secret_key_{};
  bool has_keys_ = false;
};

}  // namespace EspHelper
