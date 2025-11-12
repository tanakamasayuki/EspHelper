# Sodium Examples

[日本語はこちら](README.ja.md)

`EspHelperSodium.h` wraps a few common libsodium building blocks so you can tap into secure randomness, symmetric encryption (`crypto_secretbox`), and Ed25519 signatures without juggling global state.

## API Reference
- `EspHelper::Sodium::init()` – one-time `sodium_init()` wrapper (called implicitly by helpers).
- `randomBytes(buf, len)` / `randomHex(byteLen)` / `toHex(buf, len)` – utility helpers for random material and hex strings.
- `EspHelper::SecretBox`
  - `generateKey()` / `setKey(key)`
  - `encrypt(plain, plainLen, cipher, nonce)` – writes `plainLen + crypto_secretbox_MACBYTES` bytes to `cipher` and fills the provided `nonce`.
  - `decrypt(cipher, cipherLen, nonce, plain)` – inverse of `encrypt`.
- `EspHelper::Signer`
  - `generateKeyPair()` / `setKeyPair(pub, sec)`
  - `sign(message, len, signature)` / `verify(message, len, signature)` for Ed25519.

Usage notes:
- All helpers call `Sodium::init()` internally, but you can check the return value at startup to handle missing libsodium support.
- `SecretBox` expects buffers sized exactly like the libsodium primitives (nonce = 24 bytes, cipher = plain + 16 bytes). Keep them on the stack for short messages or in `std::vector` for larger blobs.
- `Signer` works with detached signatures (`crypto_sign_detached`). Keep secret keys secure—consider storing them in NVS/secure elements for production.

## Example overview
- `RandomHex/RandomHex.ino` – prints random 16-byte values as hexadecimal strings.
- `SecretBox/SecretBox.ino` – generates a key, encrypts a message with `crypto_secretbox_easy`, then decrypts it back.
