# Sodium サンプル

[English README](README.md)

`EspHelperSodium.h` は libsodium の主要API（乱数、`crypto_secretbox`、Ed25519署名など）をArduinoで扱いやすい形にまとめたヘッダです。

## APIリファレンス
- `EspHelper::Sodium::init()` – `sodium_init()` をラップ（内部でも自動的に呼ばれます）。
- `randomBytes(buf, len)` / `randomHex(byteLen)` / `toHex(buf, len)` – 乱数生成と16進文字列化ユーティリティ。
- `EspHelper::SecretBox`
  - `generateKey()` / `setKey(key)`
  - `encrypt(plain, plainLen, cipher, nonce)` – `nonce`を自動生成し、`plainLen + crypto_secretbox_MACBYTES` バイトの暗号文を出力。
  - `decrypt(cipher, cipherLen, nonce, plain)` – 復号処理。
- `EspHelper::Signer`
  - `generateKeyPair()` / `setKeyPair(pub, sec)`
  - `sign(message, len, signature)` / `verify(message, len, signature)` – Ed25519による署名/検証。

使いどころメモ
- 初期化に失敗した場合（libsodium非対応環境など）に備えて、`init()`の戻り値をチェックしてください。
- `SecretBox` のバッファサイズは libsodium の定数（`crypto_secretbox_NONCEBYTES`/`MACBYTES`）に合わせる必要があります。例では固定長配列を使用しています。
- `Signer` は切り離し署名（detached）を扱います。秘密鍵はNVSや安全なストレージに保管してください。

## 収録スケッチ
- `RandomHex/RandomHex.ino` – 16バイト乱数を16進文字列でシリアル出力。
- `SecretBox/SecretBox.ino` – ランダム鍵でメッセージを暗号化/復号し、結果を表示。
